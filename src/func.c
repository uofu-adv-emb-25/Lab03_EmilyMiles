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