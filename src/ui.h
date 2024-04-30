#ifndef UI_H
#define UI_H

#include "defs.h"

typedef enum {
    NONE,
    VISIBLE,
} box_state;

typedef enum {
    MB_NONE         = 0,
    MB_LEFT_CLICK   = 1,
    MB_RIGHT_CLICK  = 2,
    MB_MIDDLE_CLICK = 3,
} mouse_button_t;

typedef enum {
    M_PRESSED = 1,
    M_MOVED,
} mouse_state;

typedef struct {
    vec2f       pos;
    mouse_button_t button;
    mouse_state    state;
} Mouse;

typedef struct {
    u32 id;
//    char *text;
    SDL_FRect rect;
    SDL_Color color;
} Box;

Box  *new_box(f32 x, f32 y, f32 width, f32 height, u32 flags);
void  update_box();
void  render_box(SDL_Renderer *renderer);
int   check_box_mouse_collision(Mouse mouse);
int   mouse_input(SDL_Event event, Mouse *mouse);
void  mouse_info(Mouse mouse);
void  box_info();

#endif // UI_H
