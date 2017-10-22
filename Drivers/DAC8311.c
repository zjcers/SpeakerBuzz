/*
 * Author: Zane J Cersovsky
 * Implementation of a very simple driver for the Texas Instruments DAC8311 14-bit 
 * digital to analog convertor
 */
#include <stdbool.h>
#include "DAC8311.h"
#include "SPIMaster.h"

void DAC8311Init(struct DAC8311Instance* dacInst, struct SPIInstance* spiInst, void (*select)(bool))
{
    dacInst->spim = spiInst;
    dacInst->select = select;
    select(true); // DAC8311 expects ~SYNC to be pulled HIGH by default
}
void DAC8311Write(struct DAC8311Instance* dacInst, uint16_t value)
{
    value &= ~(0b11 << 14); //Clear the highest two bits to specify "normal operation" of the DAC
    dacInst->select(false); //Set ~SYNC to LOW
    SPIMWrite(dacInst->spim, &value, 1); //Write value
    dacInst->select(true); //Reassert ~SYNC
}