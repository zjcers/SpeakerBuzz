#include <stdbool.h>
#include <stdint.h>
#include "System/chip.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Tasks/tasks.h"
#define LEDs (GPIO_PIN_1 | GPIO_PIN_0)
/*
 * Alternates between the first two leds
 * The remaining two are not used so that this does not interfere with the ethernet controller
 * Uses GPIO N 0 and 1
 */
void Task_Blink(void* pvParameters)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, LEDs);
    uint32_t currentState = 0x01;
    while(1) {
        GPIOPinWrite(GPIO_PORTN_BASE, LEDs , currentState);
        currentState ^= LEDs;
        vTaskDelay(1000);
    }
}