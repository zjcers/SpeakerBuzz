/*
 * Author: Zane J Cersovsky
 * Lab 2 of 3: Basic SpeakerBuzz with timing derived from a timer interrupt.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "System/chip.h"
#include "Drivers/driver_utils.h"
#include "Packages/driverlib/sysctl.h"
#include "Packages/driverlib/timer.h"
#include "Drivers/AudioPack.h"

#define VOLUME ((uint16_t)((1 << 14)/2))
#define FREQUENCY 440
#define PERIOD (system_clock / FREQUENCY)
#define HALF_PERIOD (PERIOD / 2)

static struct AudioInst audioDriver;

void Tone_Lab2_ISR()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    static bool isHighSide = false;
    if (isHighSide)
        DACWrite(audioDriver, VOLUME);
    else
        DACWrite(audioDriver, 0x00);
    isHighSide = !isHighSide;
}

void Task_SpeakerBuzz_Lab2(void* pvParameters)
{
    //Configure the audio output hardware (SPI, DAC...)
    AudioInit(&audioDriver);
    //Set up a periodic timer interrupt to drive the DAC
    EnablePeriphBlocking(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, HALF_PERIOD);
    TimerIntRegister(TIMER0_BASE, TIMER_A, &Tone_Lab2_ISR);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    //Sleep forever
    vTaskSuspend(NULL);
}