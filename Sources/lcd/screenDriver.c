#include "screenDriver.h"
#include "../general/mcuHeader.h"
#include "../general/fixed.h"
#include "font.h"

unsigned char row = 0; unsigned char col = 0; unsigned char pr = 0; unsigned char pc = 0;
// row 0-29 col 0-39

#define colToPx(col) (col*8)
#define rowToPy(row) (row*8)

#define dot3(v1, v2) (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)
#define solveMatrix2(v1, v2, v3, v4) (v1 * v4 - v2 * v3)

vec3 cameraPos = (vec3){120.0f, 160.0f, 0.0f};

vec3 cross(const vec3 v1, const vec3 v2){
	const vec3 ret = {solveMatrix2(v1.y, v1.z, v2.y, v2.z), -1.0f * solveMatrix2(v1.x, v1.z, v2.x, v2.z), solveMatrix2(v1.x, v1.y, v2.x, v2.y)};
	return ret;
}

#define pointInTriangle(bary) (bary.x > -0.01 && bary.y > -0.01 && bary.z > 0.01)

#define COMMAND 1
#define DATA 0

// 1 is NOT enough, but it all depends how the lcd is feeling
// 2 is NOT enough for deterministic screen shenanigans :).
// 3 is BARELY enough, the clock speed and wr lock time barely lign up, slight artifacting
// 4 is def enough but just use 3 its fine
#define PULSE_DELAY() __asm__("nop") // guarantee 15ns pulse time to lock write signal(2 may be enough idk?)

// Pin Defs:
/*
 * GPIOB_1 register select(RS) selects is it command or data
 * GPIOB_0 write pulse(WR) pulse to lock data
 * GPIOC_5 chip select(CS) enables data read when low
 * GPIOC_4 reset pin(RST) resets
 * GPIOA is data bus(8bit)
 */

static inline float fmin3(const float f1, const float f2, const float f3){
	// branching fairly inexpensive less pipeline stalls
	const float m = f1 < f2 ? f1 : f2;
	return m < f3 ? m : f3;
}

static inline float fmax3(const float f1, const float f2, const float f3){
	// branching fairly inexpensive less pipeline stalls
	const float m = f1 > f2 ? f1 : f2;
	return m > f3 ? m : f3;
}

static inline vec3 subVec3(vec3 v1, const vec3 v2){
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

uint16_t backdrop = 0;

typedef struct{
	float x, y;
}vec2;

typedef struct{
	vec2 p1, p2, p3;
	vec2 min, max;
	float denom, y2_y3, x1_x3, x3_x2, y3_y1;
}triangle2;

uint32_t trianglesDefined = 0;
triangle triangles[maxTriangles];
triangle2 trianglesProjected[maxTriangles]; // more ram used, but dont recalc values unless triangle is moving
uint8_t curTile = 0; // 4 tile system

__attribute__((section(".tileBufs")))
volatile uint16_t colorTileBuf[120][120];
__attribute__((section(".tileBufs")))
volatile float zTileBuf[120][120];

static inline void resetBufs(){
	for(uint16_t x = 0; x < 120; x++){
		for(uint16_t y = 0; y < 120; y++){
			colorTileBuf[x][y] = backdrop;
			zTileBuf[x][y] = 3e30f;
		}
	}
}

void addTriangle(const triangle t){
	triangles[trianglesDefined] = t;
	trianglesDefined++;
}

static inline void WRITE_LCD_BUS(const unsigned char data, const unsigned char command){
	// LCD_RS bit set for command, clear for data
	if(command == COMMAND){
		CLEAR_PIN(GPIOB_ODR, 1);
	}
	else{
		SET_PIN(GPIOB_ODR, 1);
	}
	// write byte on GPIOC
	WRITE_BYTE_PORT_LO(GPIOA_ODR, data);
	// LCD_WR set and clear to send byte
	CLEAR_PIN(GPIOB_ODR, 0);
	//PULSE_DELAY();
	SET_PIN(GPIOB_ODR, 0);
}

void changeBackdrop(const uint16_t c){
	backdrop = c;
}

unsigned char getRow(){
	return row;
}

void LCD_INIT(){
	CLEAR_PIN(GPIOC_ODR, 4); // reset low
	delay_ms(10);
	SET_PIN(GPIOC_ODR, 4);
	delay_ms(120);
	CLEAR_PIN(GPIOC_ODR, 5); // chip select

	WRITE_LCD_BUS(0xEF, COMMAND);
	WRITE_LCD_BUS(0x03, DATA); WRITE_LCD_BUS(0x80, DATA); WRITE_LCD_BUS(0x02, DATA);

	WRITE_LCD_BUS(0xCF, COMMAND);
	WRITE_LCD_BUS(0x00, DATA); WRITE_LCD_BUS(0xC1, DATA); WRITE_LCD_BUS(0x30, DATA);

	WRITE_LCD_BUS(0xED, COMMAND);
	WRITE_LCD_BUS(0x64, DATA); WRITE_LCD_BUS(0x03, DATA); WRITE_LCD_BUS(0x12, DATA); WRITE_LCD_BUS(0x81, DATA);

	WRITE_LCD_BUS(0xCB, COMMAND);
	WRITE_LCD_BUS(0x39, DATA); WRITE_LCD_BUS(0x2C, DATA); WRITE_LCD_BUS(0x00, DATA);
	WRITE_LCD_BUS(0x34, DATA); WRITE_LCD_BUS(0x02, DATA);

	WRITE_LCD_BUS(0xF7, COMMAND);
	WRITE_LCD_BUS(0x20, DATA);

	WRITE_LCD_BUS(0xEA, COMMAND);
	WRITE_LCD_BUS(0x00, DATA); WRITE_LCD_BUS(0x00, DATA);

	WRITE_LCD_BUS(0xC0, COMMAND);
	WRITE_LCD_BUS(0x23, DATA);

	WRITE_LCD_BUS(0xC1, COMMAND);
	WRITE_LCD_BUS(0x10, DATA);

	WRITE_LCD_BUS(0xC5, COMMAND);
	WRITE_LCD_BUS(0x3E, DATA); WRITE_LCD_BUS(0x28, DATA);

	WRITE_LCD_BUS(0xC7, COMMAND);
	WRITE_LCD_BUS(0x86, DATA);

	WRITE_LCD_BUS(0x36, COMMAND);
	WRITE_LCD_BUS(0x48, DATA);  // MX, BGR

	WRITE_LCD_BUS(0x3A, COMMAND);
	WRITE_LCD_BUS(0x55, DATA);  // 16-bit/pixel

	WRITE_LCD_BUS(0xB1, COMMAND);
	WRITE_LCD_BUS(0x00, DATA); WRITE_LCD_BUS(0x18, DATA);

	WRITE_LCD_BUS(0xB6, COMMAND);
	WRITE_LCD_BUS(0x08, DATA); WRITE_LCD_BUS(0x82, DATA); WRITE_LCD_BUS(0x27, DATA);

	WRITE_LCD_BUS(0xF2, COMMAND);
	WRITE_LCD_BUS(0x00, DATA);

	WRITE_LCD_BUS(0x26, COMMAND);
	WRITE_LCD_BUS(0x01, DATA);

	WRITE_LCD_BUS(0xE0, COMMAND);
	uint8_t gamma_pos[] = {0x0F,0x31,0x2B,0x0C,0x0E,0x08,0x4E,0xF1,0x37,0x07,0x10,0x03,0x0E,0x09,0x00};
	for (int i = 0; i < 15; i++) WRITE_LCD_BUS(gamma_pos[i], DATA);

	WRITE_LCD_BUS(0xE1, COMMAND);
	uint8_t gamma_neg[] = {0x00,0x0E,0x14,0x03,0x11,0x07,0x31,0xC1,0x48,0x08,0x0F,0x0C,0x31,0x36,0x0F};
	for (int i = 0; i < 15; i++) WRITE_LCD_BUS(gamma_neg[i], DATA);

	WRITE_LCD_BUS(0x11, COMMAND);  // Sleep Out
	delay_ms(120);

	WRITE_LCD_BUS(0x29, COMMAND);  // Display ON
}

void clearLCD(){
	WRITE_LCD_BUS(0x2a, COMMAND);
	WRITE_LCD_BUS(0, DATA);
	WRITE_LCD_BUS(0, DATA);
	WRITE_LCD_BUS(0, DATA);
	WRITE_LCD_BUS(240, DATA);

	WRITE_LCD_BUS(0x2b, COMMAND);
	WRITE_LCD_BUS(0, DATA);
	WRITE_LCD_BUS(0, DATA);
	WRITE_LCD_BUS(1, DATA);
	WRITE_LCD_BUS(64, DATA);

	WRITE_LCD_BUS(0x2c, COMMAND);
	for(unsigned int x = 0; x < 320; x++){
		for(unsigned char y = 0; y < 240; y++){
			WRITE_LCD_BUS(backdrop >> 8, DATA); WRITE_LCD_BUS(backdrop & 0xFF, DATA);
		}
	}
}

static inline vec2 barycentricInterpolCorner(const triangle2 t){
	// this is cursed
	vec2 p = t.min;
	p.x -= t.p3.x;
	p.y -= t.p3.y;
	return (vec2){(t.y2_y3 * p.x + t.x3_x2 * p.y), (t.y3_y1 * p.x + t.x1_x3 * p.y)};
}

static inline float invsqrt(float f){
	// dumbass compiler strict alias must be avoided
	*(__attribute((may_alias)) uint32_t*)(&f) = 0x5f3759dfu - (*(__attribute((may_alias)) uint32_t*)(&f) >> 1);
	f = f * (1.5f - 0.5f * f * f * f);
	return f;
}

static inline vec3 normalize(vec3 v){
	const float sq = invsqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x = v.x * sq; v.y = v.y * sq; v.z = v.z * sq;
	return v;
}

static inline vec2 projectPoint(const vec3 p){
	// assume camera rotation is 0, 0, 1. doing anything else would be REALLY slow computationally
	vec3 v = subVec3(p, cameraPos);
	float invz = 1.0f / v.z;
	return (vec2){120 + v.x * invz * fov, 120 + v.y * invz * fov};
}

void projectTriangle(const uint32_t idx){
	triangle2 ret;
	ret.p1 = projectPoint(triangles[idx].p1); ret.p2 = projectPoint(triangles[idx].p2); ret.p3 = projectPoint(triangles[idx].p3);
	ret.min = (vec2){fmin3(ret.p1.x, ret.p2.x, ret.p3.x), fmin3(ret.p1.y, ret.p2.y, ret.p3.y)};
	ret.max = (vec2){fmax3(ret.p1.x, ret.p2.x, ret.p3.x), fmax3(ret.p1.y, ret.p2.y, ret.p3.y)};
	ret.denom = 1.0f/((ret.p2.y - ret.p3.y) * (ret.p1.x - ret.p3.x) + (ret.p3.x - ret.p2.x) * (ret.p1.y - ret.p3.y));
	ret.y2_y3 = (ret.p2.y - ret.p3.y) * ret.denom;
	ret.x1_x3 = (ret.p1.x - ret.p3.x) * ret.denom;
	ret.x3_x2 = (ret.p3.x - ret.p2.x) * ret.denom;
	ret.y3_y1 = (ret.p3.y - ret.p1.y) * ret.denom;
	trianglesProjected[idx] = ret;
}

static inline void renderTriangle(const uint32_t idx){

	// compiler prob optimizes fine just gotta make sure, otherwise this makes no sense
	register triangle2 t = trianglesProjected[idx];

	const uint16_t lox = (curTile % 2) ? 120 : 0;
	const uint16_t hix = (curTile % 2) ? 239 : 119;
	const uint16_t loy = (curTile < 2) ? 0 : 120;
	const uint16_t hiy = (curTile < 2) ? 120 : 240;

	uint16_t maxx = (uint16_t)(t.max.x);
	if(maxx < lox){return;}
	maxx = (maxx > hix) ? hix : maxx;
	uint16_t maxy = (uint16_t)(t.max.y);
	if(maxy < loy){return;}
	maxy = (maxy > hiy) ? hiy : maxy;
	uint16_t minx = (uint16_t)(t.min.x);
	if(minx > hix){return;}
	minx = (minx < lox) ? lox : minx;
	uint16_t miny = (uint16_t)(t.min.y);
	if(miny > hiy){return;}
	miny = (miny < loy) ? loy : miny;

	t.min.x = minx; t.min.y = miny;

	WRITE_LCD_BUS(0x2a, COMMAND);
	WRITE_LCD_BUS(minx >> 8, DATA);
	WRITE_LCD_BUS(minx & 0xFF, DATA);
	WRITE_LCD_BUS(maxx >> 8, DATA);
	WRITE_LCD_BUS(maxx & 0xFF, DATA);

	WRITE_LCD_BUS(0x2b, COMMAND);
	WRITE_LCD_BUS(miny >> 8, DATA);
	WRITE_LCD_BUS(miny & 0xFF, DATA);
	WRITE_LCD_BUS(maxy >> 8, DATA);
	WRITE_LCD_BUS(maxy & 0xFF, DATA);
	WRITE_LCD_BUS(0x2c, COMMAND);

	vec2 initialUV = barycentricInterpolCorner(t);
	// da(x) y2_y3
	// db(x) y3_y1
	// da(y) x3_x2
	// db(y) x1_x3
	for(uint32_t y = miny; y <= maxy; y++){
		float alpha = initialUV.x;
		float beta = initialUV.y;
		for(uint32_t x = minx; x <= maxx; x++){
			float gamma = 1.0f - alpha - beta; // last barycentric coord
			if(alpha > -0.01f && beta > -0.01f && gamma > -0.01f){
				// inside
				const float tmpz = alpha * triangles[idx].p1.z + beta * triangles[idx].p2.z + gamma * triangles[idx].p3.z;

				if(tmpz < zTileBuf[x-lox][y-loy]){
					colorTileBuf[x-lox][y-loy] = triangles[idx].color;
					zTileBuf[x-lox][y-loy] = tmpz;
				}
			}

			WRITE_LCD_BUS(colorTileBuf[x-lox][y-loy] >> 8, DATA); WRITE_LCD_BUS(colorTileBuf[x-lox][y-loy] & 0xFF, DATA);
			alpha += t.y2_y3;
			beta += t.y3_y1;
		}
		initialUV.x += t.x3_x2;
		initialUV.y += t.x1_x3;
	}
}

void renderTriangles(){
	for(curTile = 0; curTile < 4; curTile++){
		resetBufs();
		for(uint32_t t = 0; t < trianglesDefined; t++){
			renderTriangle(t);
		}
	}
}
