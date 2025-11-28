/*
 * fixed.h
 *
 *  Created on: Nov 27, 2025
 *      Author: david
 */

#ifndef SOURCES_GENERAL_FIXED_H_
#define SOURCES_GENERAL_FIXED_H_
#include <stdint.h>

typedef int32_t fixed;
#define FIXED_SHIFT 20
#define FIXED_ONE (1 << FIXED_SHIFT)
#define TO_FIXED(flt) (fixed)(flt * FIXED_ONE)
#define TO_FLOAT(fx) ((float)fx / FIXED_ONE)
#define FIXED_MUL(a, b) (((int64_t)a * b) >> FIXED_SHIFT)
#define FIXED_DIV(a, b) (((int64_t)a << FIXED_SHIFT)/b)

#endif /* SOURCES_GENERAL_FIXED_H_ */
