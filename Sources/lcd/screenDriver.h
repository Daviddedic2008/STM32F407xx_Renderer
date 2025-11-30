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

void LCD_INIT();
void clearLCD();
void changeBackdrop(const uint16_t c);

extern uint8_t underline;
extern char screenBuf[30][40];

#define maxTriangles 1
#define fov 1.0f

typedef struct{
	float x, y, z;
}vec3;

typedef struct{
	vec3 p1, p2, p3;
	uint16_t color; // 16 bit 565 color
	uint8_t raytracedStrength; // 0-255. 0 is no raytracing, 255 is max.
}triangle;

extern vec3 cameraPos;
extern triangle triangles[maxTriangles];

void projectTriangle(const uint32_t idx);
void renderTriangles();
void addTriangle(const triangle t);

#endif /* SOURCES_SCREENDRIVER_H_ */

