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
#include "ResetCause/ResetCause.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "Timer/Timer.h"
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

    // Main program loop
    while (true) {
        SYS_Tasks();

        // Application tasks
        UsbCdcTasks();
        char data[256];
        const size_t numberOfBytes = UsbCdcRead(data, sizeof (data));
        UsbCdcWrite(data, numberOfBytes);
    }
    return (EXIT_FAILURE);
}

//------------------------------------------------------------------------------
// End of file
