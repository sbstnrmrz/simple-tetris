#ifndef UI_H
#define UI_H

#include "defs.h"

typedef enum {
    NONE,
    VISIBLE,
} box_state;

typedef struct {
    u32 id;
//    char *text;
    SDL_FRect rect;
    SDL_Color color;
} Box;

Box *new_box(f32 x, f32 y, f32 width, f32 height, u32 flags);
void update_box();
void render_box(SDL_Renderer *renderer);

#endif // UI_H
