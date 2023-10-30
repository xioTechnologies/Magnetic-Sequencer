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
#include "Receive/Receive.h"
#include "ResetCause/ResetCause.h"
#include "Send/Send.h"
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

    // Initialise UART
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
        ReceiveTasks();
        SendTasks();
        UsbCdcTasks();
    }
    return (EXIT_FAILURE);
}

//------------------------------------------------------------------------------
// End of file
