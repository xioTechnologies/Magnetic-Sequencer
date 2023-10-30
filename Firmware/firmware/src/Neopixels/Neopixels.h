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
#define NEOPIXELS_NUMBER_OF_PIXELS (64)

/**
 * @brief RGB pixel.
 */
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} NeoPixelsPixel;

//------------------------------------------------------------------------------
// Function declarations

void NeoPixelsInitialise(void);
void NeoPixelsSet(const NeoPixelsPixel * const pixels);

#endif

//------------------------------------------------------------------------------
// End of file
