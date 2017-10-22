#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Tasks/tasks.h"
#include "System/chip.h"
#include "Packages/driverlib/pin_map.h"
#include "Packages/driverlib/sysctl.h"
#include "Packages/driverlib/ssi.h"
#include "Packages/driverlib/gpio.h"
#include <stdio.h>

/* Working SpeakerBuzz:
 void Task_DACtest(void *pvParameters)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    GPIOPinConfigure(GPIO_PQ0_SSI3CLK);
    GPIOPinConfigure(GPIO_PQ1_SSI3FSS);
    GPIOPinConfigure(GPIO_PQ2_SSI3XDAT0);
    GPIOPinConfigure(GPIO_PQ3_SSI3XDAT1);
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_3);
    GPIOPinTypeSSI(GPIO_PORTQ_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    SSIConfigSetExpClk(SSI3_BASE, system_clock, SSI_FRF_MOTO_MODE_1, SSI_MODE_MASTER, 1000000, 16);
    SSIEnable(SSI3_BASE);
    GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, 0x00);
    while (1)
    {
        uint32_t tmp;
        puts("Writing\r\n");
        SSIDataPut(SSI3_BASE, (uint16_t)8192);
        SSIDataGet(SSI3_BASE, &tmp);
        vTaskDelay(11);
        SSIDataPut(SSI3_BASE, (uint16_t)0);
        SSIDataGet(SSI3_BASE, &tmp);
        vTaskDelay(11);
    }
} */

int main()
{
    xTaskCreate(Task_Blink, "Blink", 128, NULL, 1, NULL);
    xTaskCreate(Task_DACtest, "ssi", 256, NULL, 1, NULL);
//    xTaskCreate(Task_SpeakerBuzz, "Buzz", 256, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1)
    {
    }
}
