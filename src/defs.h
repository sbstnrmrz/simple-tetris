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
#define WIN_W 1280
#define WIN_H 720

#define COLOR_RED    (SDL_Color) {255, 0, 0, 255}
#define COLOR_GREEN  (SDL_Color) {0, 255, 0, 255}
#define COLOR_BLUE   (SDL_Color) {0, 0, 255, 255}
#define COLOR_CYAN   (SDL_Color) {0, 255, 255, 255}
#define COLOR_YELLOW (SDL_Color) {255, 255, 0, 255}
#define COLOR_ORANGE (SDL_Color) {255, 80, 0, 255}
#define COLOR_PURPLE (SDL_Color) {255, 0, 255, 255}
#define COLOR_WHITE  (SDL_Color) {255, 255, 255, 255}
#define COLOR_BLACK  (SDL_Color) {0, 0, 0, 255}

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
} vec2;

typedef struct {
    f32 x;
    f32 y;
} vec2f;

#endif // DEFS_h
