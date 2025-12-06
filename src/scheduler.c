#include "scheduler.h"
#include "config.h"
#include <stdint.h>
#include <string.h>

static struct {
    task_func_t fn;
    uint16_t period_ms;
    uint16_t time_left;
    uint8_t active;
} tasks[MAX_TASKS];

void scheduler_init(void) {
    memset(tasks, 0, sizeof(tasks));
}

int scheduler_add_task(task_func_t fn, uint16_t period_ms) {
    for(int i=0;i<MAX_TASKS;i++) {
        if(!tasks[i].active) {
            tasks[i].fn = fn;
            tasks[i].period_ms = period_ms;
            tasks[i].time_left = period_ms;
            tasks[i].active = 1;
            return i;
        }
    }
    return -1;
}

void scheduler_tick(void) {
    for(int i=0;i<MAX_TASKS;i++) {
        if(tasks[i].active && tasks[i].time_left > 0)
            tasks[i].time_left--;
    }
}

void scheduler_dispatch(void) {
    for(int i=0;i<MAX_TASKS;i++) {
        if(tasks[i].active && tasks[i].time_left == 0) {
            if(tasks[i].fn) tasks[i].fn();
            tasks[i].time_left = tasks[i].period_ms;
        }
    }
}
