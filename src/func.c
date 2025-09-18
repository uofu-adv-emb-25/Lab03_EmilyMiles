#include "func.h"



int increment_counter(SemaphoreHandle_t counter_semaphore, int* counter_ptr)
{
    int result = xSemaphoreTake(counter_semaphore, portMAX_DELAY);
    if (result == pdTRUE)
    {
        *counter_ptr += 1;
        xSemaphoreGive(counter_semaphore);
    }
    
    return result;
}

//Deadlocked Code
void taskA(void *arg)
{
    deadlockParams *args = (deadlockParams *) arg;
    //ARGS semaphore A, semaphore B, ??

    // Acquire lock A  
    args->counter += xSemaphoreTake(args->semaphore_A, portMAX_DELAY);

    // Delay to allow task B to acquire lock B
    vTaskDelay(1000);

    // Attempt to acquire lock B
    args->counter += xSemaphoreTake(args->semaphore_B, portMAX_DELAY);
    
    xSemaphoreGive(args->semaphore_B);
    xSemaphoreGive(args->semaphore_A);

    vTaskSuspend(NULL);
}

void taskB(void *arg) 
{
    deadlockParams *args = (deadlockParams *) arg;
    // Acquire lock B
    args->counter += xSemaphoreTake(args->semaphore_B, portMAX_DELAY);

    // Attempt to acquire lock A
    args->counter += xSemaphoreTake(args->semaphore_A, portMAX_DELAY);

    xSemaphoreGive(args->semaphore_A);
    xSemaphoreGive(args->semaphore_B);

    vTaskSuspend(NULL);
}