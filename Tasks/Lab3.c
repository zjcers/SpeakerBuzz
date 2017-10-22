/*
 * Author: Zane J Cersovsky
 * Lab 3 of 3: Non-trivial SpeakerBuzz with timing derived from a timer interrupt
 * Tone frequency is varied using a sine function generated in a FreeRTOS task
 */

#include "FreeRTOS.h"
#include "task.h"
#include "System/chip.h"
#include "Drivers/driver_utils.h"
#include "Packages/driverlib/sysctl.h"
#include "Packages/driverlib/timer.h"
#include "Drivers/AudioPack.h"
#include <math.h>
#include <stdio.h>

#define VOLUME ((uint16_t)((1 << 14)/2))
#define CENTER_FREQUENCY 600
#define RANGE 300
#define INCREMENT 0.02
#define INCREMENT_TIME 10

static struct AudioInst audioDriver;

void Tone_Lab3_ISR()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    static bool isHighSide = false;
    if (isHighSide)
        DACWrite(audioDriver, VOLUME);
    else
        DACWrite(audioDriver, 0x00);
    isHighSide = !isHighSide;
}
static inline double FrequencyFunc(float x)
{
    float y = sinf(x);
    return (double)CENTER_FREQUENCY + (y*(double)RANGE);
}
void Task_SpeakerBuzz_Lab3(void* pvParameters)
{
    static float x = 0.0; //The input for the frequency function
    //Configure the audio output hardware (SPI, DAC...)
    AudioInit(&audioDriver);
    //Set up a periodic timer interrupt to drive the DAC
    EnablePeriphBlocking(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (system_clock/CENTER_FREQUENCY));
    TimerIntRegister(TIMER0_BASE, TIMER_A, &Tone_Lab3_ISR);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    while (1) {
        int newDelay = FrequencyFunc(x);
        printf("New frequency is %d\r", newDelay);
        TimerLoadSet(TIMER0_BASE, TIMER_A, system_clock/newDelay);
        x += INCREMENT;
        vTaskDelay(INCREMENT_TIME);
    }
}