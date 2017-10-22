/*
 * Author: Zane J Cersovsky
 * Implementation of a very simple driver for the Texas Instruments DAC8311 14-bit 
 * digital to analog convertor
 */
#include <stdbool.h>
#include "DAC8311.h"
#include "SPIMaster.h"

void DAC8311Init(struct DAC8311Instance* dacInst, struct SPIInstance* spiInst)
{
    dacInst->spim = spiInst;
}
void DAC8311Write(struct DAC8311Instance* dacInst, uint16_t value)
{
    value &= ~(0b11 << 14); //Clear the highest two bits to specify "normal operation" of the DAC
    SPIMWrite(dacInst->spim, &value, 1); //Write value
}