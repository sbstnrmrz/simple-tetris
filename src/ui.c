#include "ui.h"

Box box_array[10];
static size_t box_array_size = 0;

Box *new_box(f32 x, f32 y, f32 width, f32 height, u32 flags) {
    Box result = {
        .id = box_array_size,
        .rect = {
            .x = x,
            .y = y,
            .w = width,
            .h = height
        },
        .color = RED, 
    };
    box_array[box_array_size] = result;
    box_array_size++;

    return &box_array[box_array_size];
}

void update_box() {
    for (size_t i = 0; i < box_array_size; i++) {

    }    

}

void render_box(SDL_Renderer *renderer) {
    for (size_t i = 0; i < box_array_size; i++) {
        SDL_SetRenderDrawColor(
                renderer, 
                box_array[i].color.r, 
                box_array[i].color.g, 
                box_array[i].color.b, 
                box_array[i].color.a);
        SDL_RenderRect(renderer, &box_array[i].rect);
    }    

}
