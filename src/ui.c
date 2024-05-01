#include "ui.h"

Box box_arr[10];
static size_t box_arr_size = 0;

Box *new_box(f32 x, f32 y, f32 width, f32 height, u32 flags) {
    Box result = {
        .id = box_arr_size,
        .rect = {
            .x = x,
            .y = y,
            .w = width,
            .h = height
        },
        .color = COLOR_RED, 
    };
    box_arr[box_arr_size] = result;
    box_arr_size++;

    return &box_arr[box_arr_size];
}

void update_box() {
    for (size_t i = 0; i < box_arr_size; i++) {

    }    

}

void render_box(SDL_Renderer *renderer) {
    for (size_t i = 0; i < box_arr_size; i++) {
        SDL_SetRenderDrawColor(
            renderer, 
            box_arr[i].color.r, 
            box_arr[i].color.g, 
            box_arr[i].color.b, 
            box_arr[i].color.a);
        SDL_RenderRect(renderer, &box_arr[i].rect);
    }    

}
int mouse_input(SDL_Event event, Mouse *mouse) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        SDL_GetMouseState(&mouse->pos.x, &mouse->pos.y);
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouse->button |= MB_LEFT_CLICK;
        }
        mouse->state = M_PRESSED;
        return 1;
    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        mouse->button = 0;
        mouse->state = 0;
        return 2;
    }

    return 0;
}

void mouse_info(Mouse mouse) {
    printf("[MOUSE INFO]\n");
    printf("%p\n", &mouse);
    printf("X : Y\n%.2f, %.2f\n", mouse.pos.x, mouse.pos.y);
    printf("State: %d\n", mouse.state);
    printf("Button:\nLEFT: %d\nRIGHT: %d\nMIDDLE: %d\n", mouse.button&MB_LEFT_CLICK,
                                                         mouse.button&MB_RIGHT_CLICK,
                                                         mouse.button&MB_MIDDLE_CLICK);
    printf("\n");
}
