/*
 * Author: Zane J Cersovsky
 * Implementation of the Audio BoosterPack driver
 */

#include "System/chip.h"
#include "Drivers/SPIMaster.h"
#include "AudioPack.h"
#include "Packages/driverlib/pin_map.h"
#include "Packages/driverlib/sysctl.h"
#include "Packages/driverlib/gpio.h"
void AudioInit(struct AudioInst* audioInst)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ); //SPI 3 is routed through port Q
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP); //The AMP ON signal is on PP3
    GPIOPinConfigure(GPIO_PQ0_SSI3CLK); //sclk
    GPIOPinConfigure(GPIO_PQ1_SSI3FSS); //frame signal
    GPIOPinConfigure(GPIO_PQ2_SSI3XDAT0); //MOSI
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_3); //amp on
    GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, 0x00); //low to enable amp
    SPIMInit(&(audioInst->spim), Fourth, SPI_mode_0);
    DAC8311Init(&(audioInst->dac), &(audioInst->spim));
}

void DACWrite(struct AudioInst audioInst, uint16_t val)
{
    DAC8311Write(&(audioInst.dac), val);
}