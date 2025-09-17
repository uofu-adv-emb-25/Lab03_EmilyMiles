#include <stdio.h>
#include <pico/stdlib.h>
#include "pico/cyw43_arch.h"
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "func.h"


void setUp(void) 
{        
    printf("Start test\n");
}

void tearDown(void) 
{
    printf("Finished test\n");
}

void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

void test_multiplication(void)
{
    int x = 30;
    int y = 6;
    int z = x / y;
    TEST_ASSERT_TRUE_MESSAGE(z == 5, "Multiplication of two integers returned incorrect value.");
}

void test_increment_count(void)
{
    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1,1);
    int count = 0;
    int result = increment_counter(semaphore, &count);
    TEST_ASSERT_EQUAL_MESSAGE(result, 1, "Lock was not acquired");
    TEST_ASSERT_EQUAL_MESSAGE(count, 1, "Count was not incremented");
}

void test_increment_count_fail(void)
{
    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1,1);
    int count = 0;
    xSemaphoreTake(semaphore, portMAX_DELAY);
    int result = increment_counter(semaphore, &count);
    TEST_ASSERT_EQUAL_MESSAGE(result, 0, "Lock was acquired");
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Count was incremented");
}


int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    
    sleep_ms(10000); // Give time for TTY to attach.
    UNITY_BEGIN();
    RUN_TEST(test_variable_assignment);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_increment_count);
    RUN_TEST(test_increment_count_fail);
    sleep_ms(5000);
    UNITY_END();

    while(1) { sleep_ms(5000); }

    return UNITY_END();
}
