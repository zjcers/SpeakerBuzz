/*
 * Author: Zane J Cersovsky
 * A driver for the Texas Instruments Audio Boosterpack
 */
#pragma once

#include "SPIMaster.h"
#include "DAC8311.h"

/*
 * Contains all of the state necessary to run an Audio BoosterPack
 * (Optimized to work well for the sake of these labs, not generalized)
 */
struct AudioInst {
    struct SPIInstance spim;
    struct DAC8311Instance dac;
}


/*
 * Initializes an Audio Booster on the EK-TM4C1294's second BoosterPack spot.
 * Also initializes the required GPIO, SPI, and DAC
 * @param audioInst - An uninitialized instance of the driver
 */
extern void AudioInit(struct AudioInst* audioInst);

/*
 * Passes through a write to the DAC driver
 * @param value - The value to write (0-2^14)
 */
extern void DACWrite(uint16_t val);