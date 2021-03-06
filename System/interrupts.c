#include <stdint.h>
#include <string.h>
#include "chip.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"
#include "FreeRTOSConfig.h"
#include "System/interrupts.h"

//Magic values provided by the benevolent linker
extern char __bss_start__;
extern char __bss_end__;
extern char _data;
extern char _edata;
extern char _etext;

extern void main() __attribute__ ((noreturn));
extern void ConfigureUART();

size_t system_clock = 0;

void ResetISR()
{
    //Enable FPU
    FPUEnable();
    //Zero fill the bss segment
    size_t bss_size = (size_t)&__bss_end__ - (size_t)&__bss_start__;
    memset(&__bss_start__, 0, bss_size);
    //Copy data values from flash to ram
    size_t data_size = (size_t)&_edata - (size_t)&_data;
    memcpy(&_data, &_etext, data_size);
    //Set the system clock speed
    system_clock = SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ |
                       SYSCTL_OSC_MAIN |
                       SYSCTL_USE_PLL |
                       SYSCTL_CFG_VCO_480, 120000000);
    ConfigureUART();
//__asm__ __volatile__ ("b.w _mainCRTStartup");
	main();
}

void NmiSR()
{
    while(1) {};
}
void FaultISR()
{
    while(1) {};
}
void IntDefaultHandler()
{
    while(1) {};
}
