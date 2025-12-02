#include "scheduler.h"

typedef struct {
    task_func_t func;
    uint32_t interval_ms;
    uint32_t last_run;
} task_t;

static task_t tasks[MAX_TASKS];
static uint8_t task_count = 0;
static uint32_t tick_count = 0;

void scheduler_init(void) {
    task_count = 0;
    tick_count = 0;
}

void scheduler_add_task(task_func_t task, uint32_t interval_ms) {
    if (task_count < MAX_TASKS) {
        tasks[task_count].func = task;
        tasks[task_count].interval_ms = interval_ms;
        tasks[task_count].last_run = 0;
        task_count++;
    }
}

void scheduler_run(void) {
    while (1) {
        tick_count++;
        
        for (uint8_t i = 0; i < task_count; i++) {
            if ((tick_count - tasks[i].last_run) >= tasks[i].interval_ms) {
                tasks[i].func();
                tasks[i].last_run = tick_count;
            }
        }
    }
}
