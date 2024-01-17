#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <SDL3/SDL.h>

#define PI atan2f(1, 1) * 4

#define CELL_SIZE 32
#define WIN_WIDTH  1280//10 * CELL_SIZE
#define WIN_HEIGHT 720//20 * CELL_SIZE

#define RED    (SDL_Color) {255, 0, 0, 255}
#define GREEN  (SDL_Color) {0, 255, 0, 255}
#define BLUE   (SDL_Color) {0, 0, 255, 255}
#define CYAN   (SDL_Color) {0, 255, 255, 255}
#define YELLOW (SDL_Color) {255, 255, 0, 255}
#define ORANGE (SDL_Color) {255, 80, 0, 255}
#define PURPLE (SDL_Color) {255, 0, 255, 255}
#define WHITE  (SDL_Color) {255, 255, 255, 255}
#define BLACK  (SDL_Color) {0, 0, 0, 255}

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

typedef struct {
    i32 x;
    i32 y;
} vec2d_t;

typedef struct {
    f32 x;
    f32 y;
} vecf2d_t;

#endif // DEFS_h
