#include "clock.h"

void start_clock(Clock *clock) {
    clock->start_ms = SDL_GetTicks();
    clock->state = RUNNING;

}

void pause_clock(Clock *clock) {
    clock->state = PAUSED;

}

void stop_clock(Clock *clock) {
    clock->start_ms = 0;
    clock->current_ms = 0;
    clock->state = STOPPED;

}

void restart_clock(Clock *clock) {

}

void update_clock(Clock *clock) {
    if (clock->state == RUNNING) {
        clock->current_ms = SDL_GetTicks() - clock->start_ms; 
    }
}

u64 get_clock_time_min(Clock clock) {
    return clock.current_ms / 1000;
}

u64 get_clock_time_hr(Clock clock) {
    return clock.current_ms / 3.6e+6;
}
