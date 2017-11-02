/*
 * Author: Zane J Cersovsky
 * Lab 4 of 3: Non-trivial SpeakerBuzz with timing derived from a timer interrupt
 * Produces a high-quality sine wave with a precomputed lookup table
 */

#include "FreeRTOS.h"
#include "task.h"
#include "System/chip.h"
#include "Drivers/driver_utils.h"
#include "Packages/driverlib/sysctl.h"
#include "Packages/driverlib/timer.h"
#include "Packages/driverlib/rom.h"
#include "Packages/driverlib/rom_map.h"
#include "Drivers/AudioPack.h"
#include <math.h>
#include <stdio.h>

#define VOLUME ((uint16_t)((1 << 14)/2))
#define CENTER_FREQUENCY 900
#define SAMPLE_COUNT 100

static uint16_t samples[SAMPLE_COUNT];
static struct AudioInst audioDriver;

static void Tone_Lab4_ISR(void)
{
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    static uint32_t i = 0;
    DACWrite(audioDriver, samples[i]);
    i = (i+1)%SAMPLE_COUNT;
}
static void makeWave(void)
{
    float x = 0.0;
    for(size_t i=0; i<SAMPLE_COUNT; i++) {
        x = (3.14159265358979323846*2.0)*((float)i/(float)(SAMPLE_COUNT));
        samples[i] = ((float)(VOLUME/2) * sinf(x)) + VOLUME/2;
    }
}
void Task_SpeakerBuzz_Lab4(void* pvParameters)
{
    //static float x = 0.0; //The input for the frequency function
    //Configure the audio output hardware (SPI, DAC...)
    AudioInit(&audioDriver);
    //Generate the sine wave samples
    makeWave();
    //Set up a periodic timer interrupt to drive the DAC
    EnablePeriphBlocking(SYSCTL_PERIPH_TIMER0);
    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, (system_clock/(CENTER_FREQUENCY*SAMPLE_COUNT)));
    TimerIntRegister(TIMER0_BASE, TIMER_A, &Tone_Lab4_ISR);
    MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerEnable(TIMER0_BASE, TIMER_A);
    //Sleep forever
    vTaskSuspend(NULL);
}