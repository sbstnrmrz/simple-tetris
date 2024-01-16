#ifndef UI_H
#define UI_H

#include "defs.h"

typedef enum {
    NONE,


} box_state;

typedef struct {
    u32 id;
    char *text;
    SDL_FRect rect;

} box;


#endif // UI_H
