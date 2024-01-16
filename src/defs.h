#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <SDL3/SDL.h>

#define CELL_SIZE 32
#define WIN_WIDTH  10 * CELL_SIZE
#define WIN_HEIGHT 20 * CELL_SIZE

#define PI atan2f(1, 1) * 4

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;

#endif // DEFS_h
