#pragma once
/*
 * Forward declarations for the various FreeRTOS tasks
 */

/*
 * Alternates between the first two leds
 * The remaining two are not used so that this does not interfere with the ethernet controller
 * Uses GPIO N 0 and 1
 */
void Task_Blink(void* pvParameters);
