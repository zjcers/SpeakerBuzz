/*
 * Author: Zane J Cersovsky
 * Provides a basic driver for the Texas Instruments DAC8311
 * Depends on the SPIMaster driver in this directory
 */
#pragma once

#include "SPIMaster.h"

/*
 * Initializes the driver and hardware
 * @param dacInst - An uninitialized DAC8311Instance struct to keep driver state in
 * @param spiInst - A SPIMaster driver instance which has been initialized
 */
extern void DAC8311Init(struct DAC8311Instance* dacInst, struct SPIInstance* spiInst);

/*
 * Writes a single value to the DAC
 * @param dacInst - An initialized instance of this driver
 * @param value - The value to write (between 0 and 2^14)
 */
extern void DAC8311Write(struct DAC8311Instance* dacInst, uint16_t value);