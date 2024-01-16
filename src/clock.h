#ifndef CLOCK_H
#define CLOCK_H

#include "defs.h"

typedef enum {
    PAUSED,
    RUNNING,
    STOPPED,
} clock_state_t;

typedef struct {
    u64 start_ms;
    u64 current_ms;
    clock_state_t state;
} Clock;

void start_clock(Clock *clock);
void restart_clock(Clock *clock);
void pause_clock(Clock *clock);
void stop_clock(Clock *clock);
void update_clock(Clock *clock);
u64 get_clock_time_sec(Clock clock);
u64 get_clock_time_min(Clock clock);
u64 get_clock_time_hr(Clock clock);

#endif // CLOCK_H
