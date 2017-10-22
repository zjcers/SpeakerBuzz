/*
 * Author: Zane J Cersovsky
 * Forward declarations for the various FreeRTOS tasks
 */
#pragma once

/*
 * Alternates between the first two leds
 * The remaining two are not used so that this does not interfere with the ethernet controller
 * Uses GPIO N 0 and 1
 */
extern void Task_Blink(void* pvParameters);

/*
 * The implementation of SpeakerBuzz for Lab 1. Uses vTaskDelayUntil for timing.
 * Outputs a constant 440hz tone.
 */
extern void Task_SpeakerBuzz_Lab1(void* pvParameters);

/*
 * The implementation of SpeakerBuzz for Lab 2. Uses a hardware timer and interrupt for timing.
 * Outputs a constant 440hz tone
 */
extern void Task_SpeakerBuzz_Lab2(void* pvParameters);

/*
 * The implementation of SpeakerBuzz for Lab 3. Uses a hardware timer and interrupt for timing.
 * Does a frequency sweep using the FreeRTOS task to calulate the delay
 */
extern void Task_SpeakerBuzz_Lab3(void* pvParameters);

#ifdef LAB1
#define Task_SpeakerBuzz Task_SpeakerBuzz_Lab1
#endif

#ifdef LAB2
#define Task_SpeakerBuzz Task_SpeakerBuzz_Lab2
#endif

#ifdef LAB3
#define Task_SpeakerBuzz Task_SpeakerBuzz_Lab3
#endif