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
#define CENTER_FREQUENCY 900
#define RANGE 300
#define INCREMENT 0.02
#define INCREMENT_TIME 10
static uint16_t samples[100];
static struct AudioInst audioDriver;

static void Tone_Lab4_ISR(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    static uint32_t i = 0;
    DACWrite(audioDriver, samples[i]);
    i = (i+1)%100;
}
static void makeWave(void)
{
    float x = 0.0;
    for(size_t i=0; i<100; i++) {
        x = (3.14159265358979323846*2.0)*((float)i/100.0);
        samples[i] = ((float)(VOLUME/2) * sinf(x)) + VOLUME/2;
    }
}
void Task_SpeakerBuzz_Lab4(void* pvParameters)
{
    //static float x = 0.0; //The input for the frequency function
    //Configure the audio output hardware (SPI, DAC...)
    AudioInit(&audioDriver);
    //Set up a periodic timer interrupt to drive the DAC
    EnablePeriphBlocking(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (system_clock/(CENTER_FREQUENCY*100)));
    TimerIntRegister(TIMER0_BASE, TIMER_A, &Tone_Lab4_ISR);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    makeWave();
    while (1) {
//        int newDelay = FrequencyFunc(x);
//        printf("New frequency is %d\r", newDelay);
//        TimerLoadSet(TIMER0_BASE, TIMER_A, system_clock/newDelay);
//        x += INCREMENT;
        vTaskDelay(INCREMENT_TIME);
    }
}