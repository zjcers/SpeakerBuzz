/*
 * Author: Zane J Cersovsky
 * This is a SPI driver that wraps the SSI driver provided
 * by TivaWare and provides a similar interface to that of 
 * the I2C Master driver in the Tiva Sensor Library
 */

#include <stdint.h>
#include "Packages/driverlib/inc/hw_memmap.h"
#include "Packages/driverlib/ssi.h"
#include "Packages/driverlib/sysctl.h"
#include "Drivers/SPIMaster.h"

static inline EnablePeriphBlocking(void* periph)
{
    SysCtlPeripheralEnable(periph);
    while (!SysCtlPeripheralReady(periph)) {}
}
struct SSI_config {
    void* SSI_base_addr;
    uint32_t periph;
};
const struct SSI_config SSI_configs[] = {
    {
        .SSI_base_addr = SSI0_BASE,
        .periph = SYSCTL_PERIPH_SSI0
    },
    {
        .SSI_base_addr = SSI1_BASE,
        .periph = SYSCTL_PERIPH_SSI1
    },
    {
        .SSI_base_addr = SSI2_BASE,
        .periph = SYSCTL_PERIPH_SSI2
    }
    {
        .SSI_base_addr = SSI3_BASE,
        .periph = SYSCTL_PERIPH_SSI3
    }
};
void SPIMInit(struct SPIInstance* inst, enum SPIDevice dev, enum SPIProtocol protocol)
{
    inst->base_addr = SSI_configs[dev].SSI_base_addr;
    inst->protocol = protocol;
    EnablePeriphBlocking(SSI_configs[dev].periph);
    SSIConfigSetExpClk(SSI_configs[dev].SSI_base_addr,
                      SysCtlClockGet(),
                      protocol,
                      SSI_MODE_MASTER,
                      SPI_bit_rate,
                      16); //TODO: make this not hardcoded to 16bits/frame
    SSIEnable(SSI_configs[dev].SSI_base_addr);
}

void SPIMWrite(struct SPIInstance* inst, void* buf, size_t n)
{
    void* base = inst->base_addr;
    for(size_t i = 0; i < n; i++)
        SSIPutChar(((char*)buf)[i]);
}