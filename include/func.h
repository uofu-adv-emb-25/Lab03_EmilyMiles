#pragma once
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>


#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

#define SIDE_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define SIDE_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

typedef struct deadlockParams {
    SemaphoreHandle_t A;
    SemaporeHandle_t B;
    int counter;
} deadlockParams;

void side_thread(void *params);
void main_thread(void *params);
int increment_counter(SemaphoreHandle_t counter_semaphore, int* counter_ptr);
void taskA(void *arg);
void taskB(void *arg);