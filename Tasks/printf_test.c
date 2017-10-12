#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Tasks/tasks.h"
extern _ssize_t _write(int fd, const void* buffer, size_t count);
void Task_PrintfTest(void* pvParameters)
{
    char buf[100]; 
    puts("Starting up...");
    while(1) {
        extern char heap_cur;
        int n = rand();
        int d = rand();
        double frac = (double)n / (double)d;
        taskENTER_CRITICAL();
        int written = sprintf(buf, "Current heap end: %p\r\n", &heap_cur);
        if (written >= 0) {
            _write(0, buf, written);
        }
        taskEXIT_CRITICAL();
        /*written = printf(buf, "The result of %d / %d is %f\r\n", n, d, frac);
        if (written >= 0) {
            _write(0, buf, written);
        }
        written = sprintf(buf, "Current heap end: %p\r\n", &heap_cur);
        if (written >= 0) {
            _write(0, buf, written);
        }*/
        vTaskDelay(1000);
    }
}