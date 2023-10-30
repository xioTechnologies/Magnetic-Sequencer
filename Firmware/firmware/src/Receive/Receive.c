/**
 * @file Receive.c
 * @author Seb Madgwick
 * @brief Message reception.
 */

//------------------------------------------------------------------------------
// Includes

#include "NeoPixels/NeoPixels.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h> // sscanf
#include "Uart/Uart1.h"
#include "Usb/UsbCdc.h"

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Receiver structure.
 */
typedef struct {
    size_t(*read)(void* const destination, size_t numberOfBytes);
    char buffer[512];
    int index;
} Receiver;

//------------------------------------------------------------------------------
// Function declarations

static void ProcessReceivedData(Receiver * const receiver);
static void ParseCommand(const char* const string);

//------------------------------------------------------------------------------
// Variables

static Receiver usbReceiver = {.read = UsbCdcRead};
static Receiver serialReceiver = {.read = Uart1Read};
static NeoPixelsPixel pixels[NEOPIXELS_NUMBER_OF_PIXELS];

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Module tasks.  This function should be called repeatedly within the
 * main program loop.
 */
void ReceiveTasks(void) {
    ProcessReceivedData(&usbReceiver);
    ProcessReceivedData(&serialReceiver);
}

/**
 * @brief Process received data.
 * @param receiver Receiver structure.
 */
static void ProcessReceivedData(Receiver * const receiver) {
    while (true) {

        // Read data
        uint8_t data[512];
        const size_t numberOfBytes = receiver->read(data, sizeof (data));
        if (numberOfBytes == 0) {
            break;
        }

        // Process each byte
        for (int index = 0; index < numberOfBytes; index++) {

            // Add to buffer
            receiver->buffer[receiver->index] = data[index];

            // Process message
            if (receiver->buffer[receiver->index] == '\n') {

                // Terminate string
                receiver->buffer[receiver->index] = '\0';

                // Parse command
                ParseCommand(receiver->buffer);
                receiver->index = 0;
                continue;
            }

            // Increment index
            if (++receiver->index >= sizeof (receiver->buffer)) {
                receiver->index = 0;
                continue;
            }
        }
    }
}

/**
 * @brief Parses command.
 * @param string String.
 */
static void ParseCommand(const char* const string) {
    int index;
    int red;
    int green;
    int blue;
    if (sscanf(string, "%i %i %i %i", &index, &red, &green, &blue) != 4) {
        return;
    }
    if ((index < 0) || (index >= NEOPIXELS_NUMBER_OF_PIXELS)) {
        return;
    }
    pixels[index].red = (uint8_t) red;
    pixels[index].green = (uint8_t) green;
    pixels[index].blue = (uint8_t) blue;
    NeoPixelsSet(pixels);
}

//------------------------------------------------------------------------------
// End of file
