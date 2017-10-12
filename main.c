#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Tasks/tasks.h"
int i = 0;
int main()
{
    xTaskCreate(Task_Blink, "Blink", 128, NULL, 1, NULL);
    xTaskCreate(Task_PrintfTest, "Printf", 1024, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1)
    {
    }
}
