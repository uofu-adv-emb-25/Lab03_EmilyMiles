#include "func.h"



void increment_counter(SemaphoreHandle_t counter_semaphore, int* counter_ptr)
{
    xSemaphoreTake(counter_semaphore, (TickType_t) 10);
    {
        *counter_ptr += 1;
    }
    xSemaphoreGive(counter_semaphore);

}