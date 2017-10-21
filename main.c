#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Tasks/tasks.h"
int main()
{
    xTaskCreate(Task_Blink, "Blink", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1)
    {
    }
}
