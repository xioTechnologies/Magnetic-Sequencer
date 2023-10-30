/**
 * @file Send.c
 * @author Seb Madgwick
 * @brief Message sending.
 */

//------------------------------------------------------------------------------
// Includes

#include "Sensor/Sensor.h"
#include "Sensors.h"
#include <stdarg.h>
#include <stdio.h> // vsnprintf
#include <string.h> // strlen
#include "Timer/TimerEvent.h"
#include "Uart/Uart1.h"
#include "Usb/UsbCdc.h"

//------------------------------------------------------------------------------
// Function declarations

void SendString(const char* format, ...);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Module tasks.  This function should be called repeatedly within the
 * main program loop.
 */
void SendTasks(void) {

    // Do nothing else unless period has elapsed
    static TimerEvent timerEvent;
    if (TimerEventPoll(&timerEvent, 0.01f) != true) {
        return;
    }

    // Read sensors
    for (int index = 0; index < SENSORS_NUMBER_OF_SENSORS; index++) {
        SensorRead(&sensors[index]);
    }

    // Send messages
    for (int index = 0; index < SENSORS_NUMBER_OF_SENSORS; index++) {
        SendString("%i %i %i %i\n", index, sensors[index].x, sensors[index].y, sensors[index].z);
    }
}

/**
 * @brief Sends string.
 * @param format Format.
 * @param ... Arguments.
 */
void SendString(const char* format, ...) {

    // Create string
    char string[256];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(string, sizeof (string), format, arguments);
    va_end(arguments);

    // Send string
    const size_t numberOfBytes = strlen(string);
    Uart1Write(string, numberOfBytes);
    UsbCdcWrite(string, numberOfBytes);
}

//------------------------------------------------------------------------------
// End of file
