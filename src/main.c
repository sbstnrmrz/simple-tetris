#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_render.h"
#include "defs.h"
#include "game.h"
#include "ui.h"

struct {
    u64 frames;
    bool running;   
    Mouse mouse;
    SDL_Window *window;
    SDL_Renderer *renderer;
} sdl;

void init_sdl(const char *win_title, const int win_w, const int win_h, bool fullscreen) {
    sdl.running = false;
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "Failed to initialize SDL. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("Events initialized\n");

    sdl.window = SDL_CreateWindow(win_title, win_w, win_h, 0);
    if (sdl.window == NULL) {
        fprintf(stderr, "Failed to create SDL_Window. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("Window created\n");

    sdl.renderer = SDL_CreateRenderer(sdl.window, NULL);
    SDL_SetRenderVSync(sdl.renderer, 1);
    if (sdl.renderer == NULL) {
        fprintf(stderr, "Failed to create SDL_Renderer. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("Renderer created\n");

    SDL_SetRenderDrawBlendMode(sdl.renderer, SDL_BLENDMODE_BLEND);
 
    sdl.running = true;
}

void update() {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_EVENT_QUIT) {
        sdl.running = false;
    }

    SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl.renderer);

    update_game(sdl.renderer, event, sdl.frames);

    SDL_RenderPresent(sdl.renderer);

    sdl.frames++;
}

void render() {
    render_board(sdl.renderer);
    render_bag_prev(sdl.renderer);
    render_tetromino(sdl.renderer);
    render_mino_prev(sdl.renderer);
}

void debug() {
    board_info();
    mino_info();
    bag_info();
    mouse_info(sdl.mouse);
}

void uninit_sdl() {
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.window);

    SDL_Quit();
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    init_sdl("SIMPLE TETRIS", WIN_W, WIN_H, false);
    init_game();
    sdl.frames = 0;

    while(sdl.running) {
        update();
 //       debug(); 
    }

    uninit_sdl();

    return 0;
}
