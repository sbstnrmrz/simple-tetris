#include "game.h"
#include "SDL3/SDL_render.h"
#include "defs.h"
#include <stdint.h>

const float level[30] = {800.0f,      // LEVEL 0  FRAMES 48 
                         716.666666f, // LEVEL 1  FRAMES 43
                         633.333333f, // LEVEL 2  FRAMES 38
                         550.0f,      // LEVEL 3  FRAMES 33
                         466.666666f, // LEVEL 4  FRAMES 28
                         383.333333f, // LEVEL 5  FRAMES 23
                         300.0f,      // LEVEL 6  FRAMES 18
                         216.666666f, // LEVEL 7  FRAMES 13
                         133.333333f, // LEVEL 8  FRAMES 8
                         100.0f,      // LEVEL 9  FRAMES 6
                         83.333333f,  // LEVEL 10 FRAMES 5
                         83.333333f,  // LEVEL 11 FRAMES 5
                         83.333333f,  // LEVEL 12 FRAMES 5
                         66.666666f,  // LEVEL 13 FRAMES 4
                         66.666666f,  // LEVEL 14 FRAMES 4
                         66.666666f,  // LEVEL 15 FRAMES 4
                         50.0f,       // LEVEL 16 FRAMES 3
                         50.0f,       // LEVEL 17 FRAMES 3
                         50.0f,       // LEVEL 18 FRAMES 3
                         33.333333f,  // LEVEL 19 FRAMES 2
                         33.333333f,  // LEVEL 20 FRAMES 2
                         33.333333f,  // LEVEL 21 FRAMES 2
                         33.333333f,  // LEVEL 22 FRAMES 2
                         33.333333f,  // LEVEL 23 FRAMES 2
                         33.333333f,  // LEVEL 24 FRAMES 2
                         33.333333f,  // LEVEL 25 FRAMES 2
                         33.333333f,  // LEVEL 26 FRAMES 2
                         33.333333f,  // LEVEL 27 FRAMES 2
                         33.333333f,  // LEVEL 28 FRAMES 2
                         16.666666f}; // LEVEL 29 FRAMES 1

/*
const Tetromino shapes[7] = {{{ {0,1}, {1,1}, {2,1}, {3,1} }, {0,0}, I, CYAN},
                              {1,1, 2,1, 1,2, 2,2, 0,0, O, YELLOW},
                              {1,0, 0,1, 1,1, 2,1, 0,0, T, PURPLE},
                              {1,0, 2,0, 0,1, 1,1, 0,0, S, GREEN},
                              {0,0, 1,0, 1,1, 2,1, 0,0, Z, RED},
                              {1,0, 1,1, 0,2, 1,2, 0,0, J, BLUE},
                              {0,0, 0,1, 0,2, 1,2, 0,0, L, ORANGE}};
*/

const Tetromino shapes[7] = {{{ {0,1}, {1,1}, {2,1}, {3,1} }, {0,0}, I, CYAN},
                              {1,1, 2,1, 1,2, 2,2, 0,0, O, YELLOW},
                              {1,0, 0,1, 1,1, 2,1, 0,0, T, PURPLE},
                              {1,0, 2,0, 0,1, 1,1, 0,0, S, GREEN},
                              {0,0, 1,0, 1,1, 2,1, 0,0, Z, RED},
                              {0,1, 0,2, 1,2, 2,2, 0,0, J, BLUE},
                              {2,1, 0,2, 1,2, 2,2, 0,0, L, ORANGE}};

char      char_board[ROWS][COLS] = {0};
u8        int_board[ROWS][COLS] = {0};
Tetromino mino = {0};
u8        bag[7] = {0};
size_t    bag_pos = 0;
bool mino_exist = false;
bool bag_empty = true;
bool pause = false;

SDL_FRect board = {
    .x = (f32)WIN_WIDTH/2 - (f32)(BOARD_WIDTH)/2,               
    .y = (f32)WIN_HEIGHT/2 - (f32)(BOARD_HEIGHT)/2,
    .w = BOARD_WIDTH,
    .h = BOARD_HEIGHT};

SDL_FRect mino_prev = {
    .x = (f32)WIN_WIDTH / 2 + (f32)WIN_WIDTH / 8,               
    .y = (f32)WIN_HEIGHT / 2 - (f32)(BOARD_HEIGHT) / 2,
    .w = CELL_SIZE * 4,
    .h = CELL_SIZE * 4};

int init_game() {
    reset_board();

    return 0;
}

void reset_board() {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
//            charBoard[i][j] = '.';
            int_board[i][j] = 0;
        }
    }

}

Tetromino gen_mino() {
    if (bag_empty) {
        size_t cnt = 0;

        while (cnt < 7) {
            bool repeat = false; 
            bag[cnt] = rand() % 7;
            for (size_t i = 0; i < cnt; i++) {
                if (bag[cnt] == bag[i] && i != cnt) {
                    repeat = true;
                }
            } 
            if (repeat) {
                continue;
            } else {
                cnt++;
            }
        }
        bag_empty = false;
    }

    return shapes[bag[bag_pos]];
}

int check_mino_colission() {
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            if ((mino.pos[i].x + mino.off.x)-1 < 0 || int_board[mino.pos[i].y+mino.off.y][(mino.pos[j].x + mino.off.x)-1] > 0) {
//                printf("collision: %d\n", 1);
                return 1;
            }
            if ((mino.pos[i].x + mino.off.x)+1 > COLS-1 || int_board[mino.pos[i].y+mino.off.y][(mino.pos[j].x + mino.off.x)+1] > 0) {
//                printf("collision: %d\n", 2);
                return 2;
            }
            if (int_board[mino.pos[i].y+mino.off.y][mino.pos[j].x+mino.off.x+1] > 0 && int_board[mino.pos[i].y + mino.off.y][mino.pos[j].x + mino.off.x-1] > 0) {
                return 3;
            }
        }
    }
    
    return 0;
}

bool check_place_mino() {
    for (size_t i = 0; i < 4; i++) {
        if (int_board[(mino.pos[i].y + mino.off.y)+1][mino.pos[i].x + mino.off.x] > 0 || (mino.pos[i].y + mino.off.y) >= ROWS-1) {
            return true;
        }
    }

    return false;
}

void place_mino() {
    for (size_t i = 0; i < 4; i++) {
        int_board[mino.pos[i].y+mino.off.y][mino.pos[i].x+mino.off.x] = mino.shape;
    }
    bag_pos++;
    mino_exist = false;
    
}

int rotate_mino(u8 dir) {
    u8 rows = 0;
    u8 cols = 0;

    if (mino.shape > 2) {
        rows = cols = 3;
    } else {
        rows = cols = 4;
    }

    int arr[rows][cols];
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }

    for (size_t i = 0; i < 4; i++) {
        arr[mino.pos[i].y][mino.pos[i].x] = 1;
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < i; j++) {
            swap(&arr[i][j], &arr[j][i]);
        }
    }
    for (size_t i = 0; i < rows-i; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (dir == 1) {
                swap(&arr[j][i], &arr[j][(cols-1)-i]);
            }
            if (dir == 2) {
                swap(&arr[i][j], &arr[(rows-1)-i][j]);
            }
        }
    }

    Tetromino temp_mino;
//    int check = 0;
    size_t cnt = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (arr[i][j] == 1) {
                temp_mino.pos[cnt].x = j;
                temp_mino.pos[cnt].y = i; 
                cnt++;
            }
        }
    }
    for (i32 i = 0; i < 4; i++) {
        if (int_board[temp_mino.pos[i].y + mino.off.y][temp_mino.pos[i].x + mino.off.x]) {
            return 1;
        }
    }
    for (i32 i = 0; i < 4; i++) {
        mino.pos[i].x = temp_mino.pos[i].x;
        mino.pos[i].y = temp_mino.pos[i].y;
    }

//  if (check == 1) {
//      size_t cnt = 0;
//      for (size_t i = 0; i < rows; i++) {
//          for (size_t j = 0; j < cols; j++) {
//              if (arr[i][j] == 1) {
//                  mino.pos[cnt].x = j;
//                  mino.pos[cnt].y = i; 
//                  cnt++;
//              }
//          }
//      }
//  }

    return 0;
}

int clear_lines() {
    i8 line = 0;

    for (i8 i = ROWS-1; i >= 0; i--) {
        for (i8 j = 0; j < COLS; j++) {
            if (int_board[i][j] < 1) {
                line = 0;
                break;
            } else {
                line++;
            }
        }
        if (line >= 10) {
            for (i8 k = 0; k < COLS; k++) {
                int_board[i][k] = 0;
            }
            for (i8 l = i; l > 0; l--) {
                for (i8 k = 0; k < COLS; k++) {
                    int_board[l][k] = int_board[l-1][k];
                }
            }
        }
    }

    return 0;
}

void game_input(SDL_Event event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (!pause) {
            if (event.key.keysym.sym == SDLK_z) {
                rotate_mino(2);
            }
            if (event.key.keysym.sym == SDLK_x || event.key.keysym.sym == SDLK_UP) {
                rotate_mino(1);
            }
            if (event.key.keysym.sym == SDLK_UP) {
                
            }
            if (event.key.keysym.sym == SDLK_DOWN) {

            }
            if (event.key.keysym.sym == SDLK_LEFT && (check_mino_colission() != 1 && check_mino_colission() != 3)) {
                mino.off.x--;
            }
            if (event.key.keysym.sym == SDLK_RIGHT && (check_mino_colission() != 2 && check_mino_colission() != 3)) {
                mino.off.x++;
            }
        }

        if (event.key.keysym.sym == SDLK_SPACE) {
            if (!pause) {
                pause = true;
            } else {
                pause = false;
            }
        }
    } else if(event.type == SDL_EVENT_KEY_UP) {

    }

}

void update_board() {
    clear_lines();
}

void render_board(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderRect(renderer, &board);
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            //TODO
            if (int_board[i][j] > 0) {
                for (size_t k = 0; k < 7; k++) {
                    if (int_board[i][j] == shapes[k].shape) {
                        SDL_SetRenderDrawColor(renderer, 
                                               shapes[k].color.r, 
                                               shapes[k].color.g, 
                                               shapes[k].color.b, 
                                               shapes[k].color.a);
                    }
                }
                SDL_FRect cell = {
                    .x = board.x + j * CELL_SIZE,              
                    .y = board.y + i * CELL_SIZE,
                    .w = CELL_SIZE,
                    .h = CELL_SIZE};

                SDL_RenderFillRect(renderer, &cell);
                SDL_RenderRect(renderer, &cell);
            }
        }
    }

}

void render_mino_prev(SDL_Renderer *renderer) {
//  i32 max_pos = 0;
//  i32 min_pos = INT8_MAX;

//  for (i32 i = 0; i < 4; i++) {
//      if (mino.pos[i].x+mino.off.x <= min_pos) {
//          min_pos = mino.pos[i].x + mino.off.x;
//      } 
//      if (mino.pos[i].x+mino.off.x >= max_pos) {
//          max_pos = mino.pos[i].x + mino.off.x;
//      } 
//  }
    i32 prev_off = ROWS;

    for (i32 i = 0; i < 4; i++) {
        while(mino.pos[i].y + prev_off > ROWS-1) {
            prev_off--;
        }
    }
    for (i32 i = 0; i < 4; i++) {
        if (int_board[mino.pos[i].y+prev_off][mino.pos[i].x+mino.off.x] > 0) {
            prev_off--;
        }
    }

    for (i32 i = 0; i < 4; i++) {
        SDL_FRect cell = {
            .x = board.x + (mino.off.x+mino.pos[i].x) * CELL_SIZE,
            .y = board.y + (mino.pos[i].y + prev_off) * CELL_SIZE,
            .w = CELL_SIZE,
            .h = CELL_SIZE,
        }; 
        SDL_SetRenderDrawColor(renderer, mino.color.r, mino.color.g, mino.color.b, mino.color.a);
        SDL_RenderRect(renderer, &cell);
        
    }
}

void render_bag_prev(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderRect(renderer, &mino_prev);

    for(size_t i = 0; i < 4; i++) {
        SDL_FRect cell = {
            .x = shapes[bag[bag_pos+1]].pos[i].x * CELL_SIZE + mino_prev.x,              
            .y = (shapes[bag[bag_pos+1]].pos[i].y) * CELL_SIZE + mino_prev.y,
            .w = CELL_SIZE,
            .h = CELL_SIZE};
        SDL_SetRenderDrawColor(renderer, 
                               shapes[bag[bag_pos+1]].color.r,
                               shapes[bag[bag_pos+1]].color.g,  
                               shapes[bag[bag_pos+1]].color.b,  
                               shapes[bag[bag_pos+1]].color.a);
        SDL_RenderFillRect(renderer, &cell);
        SDL_RenderRect(renderer, &cell);
    }

}

void update_tetromino(u64 frames) {
    if (!pause) {
        if (bag_pos >= 7) {
            bag_pos = 0;
            bag_empty = true;
        }

        if (!mino_exist) {
            mino = gen_mino();
            mino.off.x = 3;
            mino.off.y = 0;
            mino_exist = true;
        }
        
        if (frames % 12 == 0) {
            if (check_place_mino()) {
                place_mino();
            } else {
                mino.off.y++;
            }
        }
    }
        
}

void render_tetromino(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 
                           mino.color.r, 
                           mino.color.g, 
                           mino.color.b, 
                           mino.color.a);
    
    for (size_t i = 0; i < 4; i++) {
        SDL_FRect cell = {
            .x = (mino.pos[i].x + mino.off.x) * CELL_SIZE + board.x,
            .y = (mino.pos[i].y + mino.off.y) * CELL_SIZE + board.y,
            .w = CELL_SIZE,
            .h = CELL_SIZE};

        SDL_RenderFillRect(renderer, &cell);
        SDL_RenderRect(renderer, &cell);
    }

}

void debug_board() {
    printf("[BOARD INFO]\n\n");
    for (size_t i = 0; i < ROWS; i++) {
        printf("|");
        for (size_t j = 0; j < COLS; j++) {
            printf("%d|", int_board[i][j]);    
        }
/*
        printf("\t|");
        for (size_t k = 0; k < COLS; k++) {
            printf("%d|", intBoard[i][k]);
        }
*/
        printf("\n");
    }
    printf("\n");

}

void debug_mino() {
    printf("[TETROMINO INFO]\n\n"); 
    printf("Shape: %d\n", mino.shape);
    printf("X : Y\n");
    printf("%d, %d\toff\n", mino.off.x, mino.off.y);

    for (size_t i = 0; i < 4; i++) {
        printf("%d, %d\t%d, %d\n", mino.pos[i].x, mino.pos[i].y, mino.off.x, mino.off.y);
    }
    printf("\n");

}

void debug_bag() {
    printf("[BAG INFO]\n");

    for (size_t i = 0; i < 7; i++) {
        printf("BAG: %d\n", bag[i]);    
    }
    printf("BAGPOS: %zu\n\n", bag_pos);

}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

}
