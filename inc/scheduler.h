/**
 * @file scheduler.h
 * @brief Cooperative task scheduler for RTOS
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "config.h"

#define BUFFER_SIZE FFT_SIZE  /**< Sample buffer size */
#define MAX_TASKS 4           /**< Maximum number of concurrent tasks */

/** @brief Function pointer type for scheduled tasks */
typedef void (*task_func_t)(void);

/**
 * @brief Initialize scheduler
 */
void scheduler_init(void);

/**
 * @brief Add task to scheduler
 * @param[in] fn Task function pointer
 * @param[in] period_ms Task execution period in milliseconds
 * @return Task ID or -1 if scheduler full
 */
int scheduler_add_task(task_func_t fn, uint16_t period_ms);

/**
 * @brief Decrement all task timers (called from ISR)
 */
void scheduler_tick(void);

/**
 * @brief Execute ready tasks (called from main loop)
 */
void scheduler_dispatch(void);

#endif
