/*
 * Author: Zane J Cersovsky
 * This is a SPI driver that wraps the SSI driver provided
 * by TivaWare and provides a similar interface to that of 
 * the I2C Master driver in the Tiva Sensor Library
 */
#include "System/chip.h"
#include <stdint.h>
//This is included to make TivaWare happy (thanks TI...)
#include <stdbool.h>
#include "Packages/driverlib/inc/hw_memmap.h"
#include "Packages/driverlib/ssi.h"
#include "Packages/driverlib/gpio.h"
#include "Packages/driverlib/sysctl.h"
#include "Drivers/SPIMaster.h"

void EnablePeriphBlocking(uint32_t periph)
{
    SysCtlPeripheralEnable(periph);
    while (!SysCtlPeripheralReady(periph)) {}
}
struct SSI_config {
    uint32_t SSI_base_addr;
    uint32_t periph;
    void (*initGPIO)(void);
};
static void initGPIOSSI3(void)
{
    EnablePeriphBlocking(SYSCTL_PERIPH_GPIOQ);
    GPIOPinConfigure(GPIO_PQ0_SSI3CLK);
    GPIOPinConfigure(GPIO_PQ1_SSI3FSS);
    GPIOPinConfigure(GPIO_PQ2_SSI3XDAT0);
    GPIOPinConfigure(GPIO_PQ3_SSI3XDAT1);
    GPIOPinTypeSSI(GPIO_PORTQ_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
}
//TODO: Finish writing the GPIO init functions so that the other SSI devices can actually be used
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
    },
    {
        .SSI_base_addr = SSI3_BASE,
        .periph = SYSCTL_PERIPH_SSI3,
        .initGPIO = &initGPIOSSI3
    }
};
void SPIMInit(struct SPIInstance* inst, enum SPIDevice dev, enum SPIProtocol protocol)
{
    inst->base_addr = (void*)(SSI_configs[dev].SSI_base_addr);
    inst->protocol = protocol;
    EnablePeriphBlocking(SSI_configs[dev].periph);
    SSI_configs[dev].initGPIO();
    SSIConfigSetExpClk(SSI_configs[dev].SSI_base_addr,
                      system_clock,
                      protocol,
                      SSI_MODE_MASTER,
                      SPI_bit_rate,
                      16); //TODO: make this not hardcoded to 16bits/frame
    SSIEnable(SSI_configs[dev].SSI_base_addr);
}

void SPIMWriteWord(struct SPIInstance* inst, uint16_t word)
{
    uint32_t tmp;
    uint32_t base = (uint32_t)(inst->base_addr);
    SSIDataPut(base, word);
    SSIDataGet(base, &tmp); //Needed to make sure the receive FIFO does not fill up
}