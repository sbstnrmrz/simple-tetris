#ifndef GAME_H
#define GAME_H

#include "defs.h"

#define ROWS 20
#define COLS 10
#define BOARD_WIDTH (COLS * CELL_SIZE)
#define BOARD_HEIGHT (ROWS * CELL_SIZE)

typedef enum {
    I = 1,
    O = 2,
    T = 3,
    S = 4,
    Z = 5,
    J = 6,
    L = 7
} shape_t;

typedef struct {
    vec2d_t pos[4];
    vec2d_t off;
    shape_t shape;
    SDL_Color color;
} Tetromino;

int init_game();
void reset_board();
void game_input(SDL_Event event);
Tetromino gen_mino();
void fill_bag();
int check_mino_colission();
bool check_place_mino();
void place_mino();
int check_rotation();
int rotate_mino(u8 dir);
int clear_lines();
void update_board();
void update_tetromino(u64 frames);
void render_board(SDL_Renderer *renderer);
void render_bag_prev(SDL_Renderer *renderer);
void render_mino_prev(SDL_Renderer *renderer);
void render_tetromino(SDL_Renderer *renderer);
void board_info();
void mino_info();
void bag_info(); 
void swap(int *a, int *b);

#endif // GAME_H
