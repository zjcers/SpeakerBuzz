/*
 * Author: Zane J Cersovsky
 * Provides a basic driver for the Texas Instruments DAC8311
 * Depends on the SPIMaster driver in this directory
 */
#pragma once

#include "SPIMaster.h"

/*
 * Example implementation of void select(bool enable):
 * (assuming the select line of the DAC was on port G, pin 2)
 * void DACSelect(bool enable)
 * {
 *     if (enable)
 *         GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_2, GPIO_PIN_2);
 *     else
 *         GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_2, 0x00);
 * }
 */

struct DAC8311Instance {
    struct SPIInstance* spim; //The spi driver instance associated with this driver
    void (*select)(bool); //A function to enable/disable the select line for the DAC
};

/*
 * Initializes the driver and hardware
 * @param dacInst - An uninitialized DAC8311Instance struct to keep driver state in
 * @param spiInst - A SPIMaster driver instance which has been initialized
 * @param select - A function that enables or disables the select line for the DAC
 */
extern void DAC8311Init(struct DAC8311Instance* dacInst, struct SPIInstance* spiInst, void (*select)(bool));

/*
 * Writes a single value to the DAC
 * @param dacInst - An initialized instance of this driver
 * @param value - The value to write (between 0 and 2^14)
 */
extern void DAC8311Write(struct DAC8311Instance* dacInst, uint16_t value);