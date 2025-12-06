#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "config.h"

#define BUFFER_SIZE FFT_SIZE
#define MAX_TASKS 4

typedef void (*task_func_t)(void);

void scheduler_init(void);
int scheduler_add_task(task_func_t fn, uint16_t period_ms);
void scheduler_tick(void);
void scheduler_dispatch(void);

#endif
