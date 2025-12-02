/*
 * screenDriver.h
 *
 *  Created on: Sep 8, 2025
 *      Author: david
 */

#ifndef SOURCES_SCREENDRIVER_H_
#define SOURCES_SCREENDRIVER_H_
#include "font.h"
#include <stdint.h>
// screen dependent do later

// macros to change render mode
// uncomment the one you wish to use

#define FLAT_SHADE
//#define FLAT_SHADE_SHADOWS



void LCD_INIT();
void clearLCD();
void clearLCD_FULL();
void changeBackdrop(const uint16_t c);

extern uint8_t underline;
extern char screenBuf[30][40];

#define maxTriangles 128
#define fov 75.0f
#define ambient 0.5f // ambient light strength

typedef struct{
	float x, y, z;
}vec3;

typedef struct{
	vec3 p1, p2, p3, normal;
	vec3 center, sub_p2p1, sub_p3p1;
	uint16_t color; // 16 bit 565 color
	uint8_t raytracedStrength; // 0-255. 0 is no raytracing, 255 is max.
	float dot2121, dot3131, dot2131, disc2;
}triangle;

extern triangle triangles[maxTriangles];
extern uint32_t trianglesDefined;

void projectTriangle(const uint32_t idx);
void projectAllTriangles();
void renderTriangles();
void addTriangle(const triangle t);
void setCameraPos(const float x, const float y, const float z);
void setLightPos(const float x, const float y, const float z);



#endif /* SOURCES_SCREENDRIVER_H_ */

