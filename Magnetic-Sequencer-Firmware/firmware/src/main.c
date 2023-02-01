/**
 * @file main.c
 * @author Seb Madgwick
 * @brief Main file.
 *
 * Device:
 * PIC32MX470F512H
 *
 * Compiler:
 * XC32 v4.10, MPLAB Harmony 3
 */

//------------------------------------------------------------------------------
// Includes

#include "definitions.h"
#include "NeoPixels/NeoPixels.h"
#include "ResetCause/ResetCause.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "Timer/Timer.h"
#include "Timer/TimerEvent.h"
#include "Uart/Uart1.h"
#include "Usb/UsbCdc.h"

//------------------------------------------------------------------------------
// Functions

int main(void) {
    SYS_Initialize(NULL);

    // Initialise debug UART
    Uart1Initialise(&uartSettingsDefault);

    // Print reset cause
    ResetCausePrint(ResetCauseGet());

    // Initialise modules
    TimerInitialise();
    NeoPixelsInitialise();

    // Main program loop
    while (true) {
        SYS_Tasks();

        // Application tasks
        UsbCdcTasks();

        // Echo USB data
        char data[256];
        const size_t numberOfBytes = UsbCdcRead(data, sizeof (data));
        UsbCdcWrite(data, numberOfBytes);

        // NeoPixel test pattern
        static TimerEvent timerEvent;
        if (TimerEventPoll(&timerEvent, 0.05f) == true) {
            static NeoPixel neoPixels[NUMBER_OF_PIXELS];
            for (int index = 0; index < NUMBER_OF_PIXELS; index++) {
                neoPixels[index].red += index + 1;
                neoPixels[index].green += index + 2;
                neoPixels[index].blue += index + 3;
            }
            NeoPixelsSet(neoPixels);
        }
    }
    return (EXIT_FAILURE);
}

//------------------------------------------------------------------------------
// End of file
