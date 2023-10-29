/**
 * @file main.c
 * @author Seb Madgwick
 * @brief Main file.
 *
 * Device:
 * PIC32MX470F512H
 *
 * Compiler:
 * XC32 v4.35, MPLAB Harmony 3
 */

//------------------------------------------------------------------------------
// Includes

#include "definitions.h"
#include "NeoPixels/NeoPixels.h"
#include "ResetCause/ResetCause.h"
#include "Sensor/Sensor.h"
#include "Sensors.h"
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

        // Test sensors and pixels
        static NeoPixelsPixel pixels[NEOPIXELS_NUMBER_OF_PIXELS];
        for (int index = 0; index < NEOPIXELS_NUMBER_OF_PIXELS; index++) {
            SensorRead(&sensors[index]);
            pixels[index].red = abs(sensors[index].x) / 8;
            pixels[index].green = abs(sensors[index].y) / 8;
            pixels[index].blue = abs(sensors[index].z) / 8;
        }
        NeoPixelsSet(pixels);
    }
    return (EXIT_FAILURE);
}

//------------------------------------------------------------------------------
// End of file
