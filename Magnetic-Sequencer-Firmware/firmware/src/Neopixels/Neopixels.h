/**
 * @file NeoPixels.h
 * @author Seb Madgwick
 * @brief NeoPixels driver.
 */

#ifndef NEOPIXELS_H
#define NEOPIXELS_H

//------------------------------------------------------------------------------
// Includes

#include <stdint.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Number of pixels.
 */
#define NUMBER_OF_PIXELS (64)

/**
 * @brief NepPixel RGB values.
 */
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} NeoPixel;

//------------------------------------------------------------------------------
// Function declarations

void NeoPixelsInitialise();
void NeoPixelsSet(const NeoPixel * const pixels);

#endif

//------------------------------------------------------------------------------
// End of file
