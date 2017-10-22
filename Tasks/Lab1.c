/*
 * Author: Zane J Cersovsky
 * Lab 1 of 3: Basic SpeakerBuzz with timing derived from FreeRTOS's scheduler.
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "Drivers/AudioPack.h"

#define VOLUME ((uint16_t)((1 << 14)/2))
#define FREQUENCY 440
#define PERIOD (configTICK_RATE_HZ / FREQUENCY)
#define HALF_PERIOD (PERIOD / 2)

void Task_SpeakerBuzz(void* pvParameters)
{
    struct AudioInst audioDriver;
    AudioInit(&audioDriver);
    /*
     * vTaskDelayUntil() is used instead of vTaskDelay() in order to get as much 
     * accuracy as possible. This requires getting an initial time to start with.
     */
    TickType_t lastWakeUp = xTaskGetTickCount();
    while(1) {
        //Write the high portion of the output signal
        DACWrite(audioDriver, VOLUME);
        vTaskDelayUntil(&lastWakeUp, HALF_PERIOD);
        //Write the low portion of the output signal
        DACWrite(audioDriver, 0);
        vTaskDelayUntil(&lastWakeUp, HALF_PERIOD);
    }
}