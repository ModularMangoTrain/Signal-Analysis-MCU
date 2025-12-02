#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "config.h"

#define BUFFER_SIZE FFT_SIZE
#define MAX_TASKS 4

typedef void (*task_func_t)(void);

void scheduler_init(void);
void scheduler_add_task(task_func_t task, uint32_t interval_ms);
void scheduler_run(void);

#endif
