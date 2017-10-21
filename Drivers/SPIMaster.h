/*
 * Author: Zane J Cersovsky
 * This is a SPI driver that wraps the SSI driver provided
 * by TivaWare and provides a similar interface to that of 
 * the I2C Master driver in the Tiva Sensor Library
 */
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Packages/driverlib/ssi.h"

#define SPI_bit_rate 20000000

enum SPIDevice {
    First,
    Second,
    Third,
    Fourth
};

enum SPIProtocol {
    SPI_mode_0 = SSI_FRF_MOTO_MODE_0,
    SPI_mode_1 = SSI_FRF_MOTO_MODE_1,
    SPI_mode_2 = SSI_FRF_MOTO_MODE_2,
    SPI_mode_3 = SSI_FRF_MOTO_MODE_3
};

/*
 * Holds the internal state of the driver
 */
struct SPIInstance {
    void* base_addr;
    enum SPIProtocol protocol;
};

/*
 * Initializes a SPIInstance and related hardware
 * @param inst An instance of SPIInstance
 * @param proto The flavor of SPI to use (https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Mode_numbers)
 */
extern void SPIMInit(struct SPIInstance* inst, enum SPIDevice dev, enum SPIProtocol proto);

/*
 * Writes data to a SPI device
 * Note: The user of this method is responsible for selecting the correct slave enable line
 * @param inst An initialized SPIInstance
 * @param buf A buffer to write to the SPI device
 * @param n The number of bytes to write
 */
extern void SPIMWrite(struct SPIInstance* inst, void* buf, size_t n);
