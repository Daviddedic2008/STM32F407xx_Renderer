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

vec3 cameraPos = (vec3){0.0f, 0.0f, 0.0f};
vec3 lightPos = (vec3){0.0f, -200.0f, -1000.0f};
vec3 lightDir = (vec3){-1, 0, 0};

void setCameraPos(const float x, const float y, const float z){
	cameraPos = (vec3){x, y, z};
}
void setLightPos(const float x, const float y, const float z){
	lightPos = (vec3){x, y, z};
}

vec3 cross(const vec3 v1, const vec3 v2){
	const vec3 ret = {solveMatrix2(v1.y, v1.z, v2.y, v2.z), solveMatrix2(v1.x, v1.z, v2.x, v2.z) * -1, solveMatrix2(v1.x, v1.y, v2.x, v2.y)};
	return ret;
}

#define pointInTriangle(bary) (bary.x > -0.01 && bary.y > -0.01 && bary.z > 0.01)

#define COMMAND 1
#define DATA 0

// 1 is NOT enough, but it all depends how the lcd is feeling
// 2 is NOT enough for deterministic screen shenanigans :).
// 3 is BARELY enough, the clock speed and wr lock time barely line up, slight artifacting
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

static inline vec3 addVec3(vec3 v1, const vec3 v2){
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

static inline vec3 scaleVec3(vec3 v1, const float scl){
	v1.x *= scl;
	v1.y *= scl;
	v1.z *= scl;
	return v1;
}

static inline float invsqrt(float f){
	// dumbass compiler strict alias must be avoided
	*(__attribute((may_alias)) uint32_t*)(&f) = 0x5f3759dfu - (*(__attribute((may_alias)) uint32_t*)(&f) >> 1);
	f = f * (1.5f - 0.5f * f * f * f);
	return f;
}

vec3 normalize(vec3 v){
	const float sq = invsqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x = v.x * sq; v.y = v.y * sq; v.z = v.z * sq;
	return v;
}

static inline float magnitude(vec3 v){
	return 1.0f/invsqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

typedef struct{
	vec3 origin, direction;
}ray;

uint16_t backdrop = 0;

typedef struct{
	float x, y;
}vec2;

static inline vec2 scaleVec2(vec2 v1, const float scl){
	v1.x *= scl;
	v1.y *= scl;
	return v1;
}

typedef struct{
	vec2 p1, p2, p3;
	vec2 min, max;
	float denom, y2_y3, x1_x3, x3_x2, y3_y1;
}triangle2;

uint32_t trianglesDefined = 0;
triangle triangles[maxTriangles];
triangle2 trianglesProjected[maxTriangles]; // more ram used, but dont recalc values unless triangle is moving

triangle2 trianglesProjectedLight[maxTriangles];

uint8_t curTile = 0; // 4 tile system



uint16_t colorTileBuf[120*120];

float zTileBuf[120*120];

#define tileBufIdx(x, y) ((x) + (y) * 120)

static inline void resetBufs(){
	for(uint16_t x = 0; x < 120*120; x++){
		zTileBuf[x] = 3e30f;
		colorTileBuf[x] = backdrop;
	}
}

static inline uint8_t hitTriangle(ray r, const uint32_t idx){
	float f = dot3(r.direction, triangles[idx].normal);
	if (f > -0.001 && f < 0.001) { // check if the plane and ray are paralell enough to be ignored
		return 0;
	}
	r.origin = addVec3(r.origin, scaleVec3(triangles[idx].normal, 0.05f));
	vec3 temp_sub = subVec3(triangles[idx].p1, r.origin);
	const float t = dot3(triangles[idx].normal, temp_sub) / f;
	if(t <= 0.01f){ return 0; }
	temp_sub = scaleVec3(r.direction, dot3(triangles[idx].normal, temp_sub) / f);// fast division since fastmath doesnt work on my system for some reason
	vec3 intersect = addVec3(temp_sub, r.origin);
	const vec3 v2 = subVec3(intersect, triangles[idx].p1);
	const float dot02 = dot3(triangles[idx].sub_p2p1, v2);
	const float dot12 = dot3(triangles[idx].sub_p3p1, v2);
	if (triangles[idx].disc2 == 0.0f) { return 0; }
	const float fdiv = 1.0f / triangles[idx].disc2;

	const float u = (triangles[idx].dot3131 * dot02 - triangles[idx].dot2131 * dot12) * fdiv;

	const float v = (triangles[idx].dot2121 * dot12 - triangles[idx].dot2131 * dot02) * fdiv;
	if ((u < 0) || (v < 0) || (u + v > 1)) { return 0; }
	return 1;
}

static inline uint8_t checkIfShadowRay(ray r, const uint32_t avoid){
	for(uint32_t t = 0; t < trianglesDefined; t++){
		if(hitTriangle(r, t)){
			return 1;
		}
	}

	return 0;
}

void addTriangle(const triangle t){
	triangles[trianglesDefined] = t;
	projectTriangle(trianglesDefined);
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
	WRITE_LCD_BUS(0, DATA);
	WRITE_LCD_BUS(240, DATA);

	WRITE_LCD_BUS(0x2c, COMMAND);
	for(unsigned int x = 0; x < 320; x++){
		for(unsigned char y = 0; y < 240; y++){
			WRITE_LCD_BUS(backdrop >> 8, DATA); WRITE_LCD_BUS(backdrop & 0xFF, DATA);
		}
	}
}

void clearLCD_FULL(){
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

static inline vec2 barycentricInterpolCorner(triangle2 t){
	// this is cursed
	t.min.x -= t.p3.x;
	t.min.y -= t.p3.y;
	return (vec2){(t.y2_y3 * t.min.x + t.x3_x2 * t.min.y), (t.y3_y1 * t.min.x + t.x1_x3 * t.min.y)};
}

static inline vec2 projectPoint(const vec3 p){
	// assume camera direction is {0, 0, 1}. doing anything else would be REALLY slow computationally
	vec3 v = subVec3(p, cameraPos);
	float invz = 1.0f / v.z;
	return (vec2){120 + v.x * invz * fov, 120 + v.y * invz * fov};
}

static inline vec3 unprojectPoint(const int16_t x, const int16_t y, const float z){
	// reverse projected point assuming camera dir is {0, 0, 1}
	const float t = z / fov;
	return addVec3((vec3){(x - 120) * t, (y - 120) * t, z}, cameraPos);
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
#ifdef FLAT_SHADE_SHADOWS
	triangles[idx].invZ = (vec3){1.0f/triangles[idx].p1.z, 1.0f/triangles[idx].p2.z, 1.0f/triangles[idx].p3.z};
	triangles[idx].sub_p2p1 = subVec3(triangles[idx].p2, triangles[idx].p1);
	triangles[idx].sub_p3p1 = subVec3(triangles[idx].p3, triangles[idx].p1);
	triangles[idx].dot2121 = dot3(triangles[idx].sub_p2p1, triangles[idx].sub_p2p1);
	triangles[idx].dot3131 = dot3(triangles[idx].sub_p3p1, triangles[idx].sub_p3p1);
	triangles[idx].dot2131 = dot3(triangles[idx].sub_p3p1, triangles[idx].sub_p2p1);
	triangles[idx].disc2 = triangles[idx].dot2121 * triangles[idx].dot3131 - triangles[idx].dot2131 * triangles[idx].dot2131;
	triangles[idx].center = scaleVec3(addVec3(addVec3(triangles[idx].p1, triangles[idx].p2), triangles[idx].p3), 1.0f/3);
#endif
	trianglesProjected[idx] = ret;
}

static inline uint16_t scaleColor(uint16_t clr, const float scl){
	uint16_t b = clr & 0b11111; // b
	uint16_t g = (clr & 0b11111100000) >> 5; // g
	uint16_t r = (clr & 0b1111100000000000) >> 11; // r
	b *= scl; g *= scl; r *= scl;
	return b + (g << 5) + (r << 11);
}

void computeNormal(const uint32_t idx){
	triangles[idx].normal = normalize(cross(subVec3(triangles[idx].p1, triangles[idx].p2), subVec3(triangles[idx].p1, triangles[idx].p3)));
}

static inline float flatShade(const uint32_t idx){
	//dt *= (dt < 0.0f) ? -1.0f : 1.0f;
	float trueBright = ambient + dot3(triangles[idx].normal, lightDir);
	trueBright = trueBright > 1.0f ? 1.0f : trueBright;
	trueBright = trueBright < ambient ? ambient : trueBright;
	return trueBright > 1.0f ? 1.0f : trueBright;
}

static inline float flatShadeShadows(const uint32_t idx, const int16_t x, const int16_t y, const float z, const float fsTrue){
	const vec3 pos = unprojectPoint(x, y, z);
	const ray r = (ray){pos, normalize(subVec3(lightPos, pos))};
	return checkIfShadowRay(r, idx) ? 0.1f : fsTrue;
}

static inline void renderTriangle(const uint32_t idx){

	// compiler prob optimizes fine just gotta make sure, otherwise this makes no sense
	register triangle2 t = trianglesProjected[idx];
	const float lightCoef = flatShade(idx);

	const uint16_t lox = (curTile % 2) ? 120 : 0;
	const uint16_t hix = (curTile % 2) ? 239 : 119;
	const uint16_t loy = (curTile < 2) ? 0 : 120;
	const uint16_t hiy = (curTile < 2) ? 120 : 240;

	int16_t maxx = (int16_t)(t.max.x);
	if(maxx < lox){return;}
	maxx = (maxx > hix) ? hix : maxx;
	int16_t maxy = (int16_t)(t.max.y);
	if(maxy < loy){return;}
	maxy = (maxy > hiy) ? hiy : maxy;
	int16_t minx = (int16_t)(t.min.x);
	if(minx > hix){return;}
	minx = (minx < lox) ? lox : minx;
	int16_t miny = (int16_t)(t.min.y);
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
			const uint16_t tidx = tileBufIdx(x - lox, y-loy);
			if(alpha > -0.01f && beta > -0.01f && gamma > -0.01f){
				// inside
				const float tmpz = 1/(alpha * triangles[idx].invZ.x + beta * triangles[idx].invZ.y + gamma * triangles[idx].invZ.z);

				if(tmpz <= zTileBuf[tidx]){
					#ifdef FLAT_SHADE_SHADOWS
					// flat shading w/ sharp shadows
					colorTileBuf[tidx] = scaleColor(triangles[idx].color, flatShadeShadows(idx, (int16_t)x, (int16_t)y, tmpz, lightCoef));
					#endif
					#ifdef FLAT_SHADE
					// simple flat shading
					colorTileBuf[tidx] = scaleColor(triangles[idx].color, lightCoef);
					#endif
					zTileBuf[tidx] = tmpz;
				}
			}

			WRITE_LCD_BUS(colorTileBuf[tidx] >> 8, DATA); WRITE_LCD_BUS(colorTileBuf[tidx] & 0xFF, DATA);
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

void projectAllTriangles(){
	for(uint32_t t = 0; t < trianglesDefined; t++){
		projectTriangle(t);
	}
}
