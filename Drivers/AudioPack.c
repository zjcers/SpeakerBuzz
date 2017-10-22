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
#include "Drivers/driver_utils.h"
static void AmpEnable()
{
    EnablePeriphBlocking(SYSCTL_PERIPH_GPIOP); //The AMP ON signal is on PP3
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_3); //amp on
    GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, 0x00); //low to enable amp
}
void AudioInit(struct AudioInst* audioInst)
{
    AmpEnable();
    SPIMInit(&(audioInst->spim), Fourth, SPI_mode_1);
    DAC8311Init(&(audioInst->dac), &(audioInst->spim));
}

void DACWrite(struct AudioInst audioInst, uint16_t val)
{
    DAC8311Write(&(audioInst.dac), val);
}