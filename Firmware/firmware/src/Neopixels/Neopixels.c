/**
 * @file NeoPixels.c
 * @author Seb Madgwick
 * @brief NeoPixels driver.
 */

//------------------------------------------------------------------------------
// Includes

#include "HexToBitPattern.h"
#include "NeoPixels.h"
#include "Spi/Spi1Dma.h"
#include <string.h> // memcpy, memset

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Bit pattern to encode RGB data.
 */
typedef struct {
    uint32_t green;
    uint32_t red;
    uint32_t blue;
} BitPattern;

/**
 * @brief SPI data to be transfered.
 */
typedef struct {
    BitPattern pixels[NEOPIXELS_NUMBER_OF_PIXELS];
    uint8_t resetCode[35]; // 84 us
} __attribute__((__packed__)) SpiData;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises the module.  This function must only be called once, on
 * system startup.
 */
void NeoPixelsInitialise() {
    SpiSettings settings = spiSettingsDefault;
    settings.clockFrequency = 3333333; // 4 bits = 1.2 us
    Spi1DmaInitialise(&settings);
}

/**
 * @brief Sets the NeoPixels.
 * @param pixels Pixels.  The array length must equal to
 * NEOPIXELS_NUMBER_OF_PIXELS.
 */
void NeoPixelsSet(const NeoPixelsPixel * const pixels) {

    // Wait for previous transfer to complete
    while (Spi1DmaIsTransferInProgress() == true);

    // Encode data
    static SpiData spiData;
    for (int index = 0; index < NEOPIXELS_NUMBER_OF_PIXELS; index++) {
        spiData.pixels[index].red = hexToBitPattern[pixels[index].red];
        spiData.pixels[index].green = hexToBitPattern[pixels[index].green];
        spiData.pixels[index].blue = hexToBitPattern[pixels[index].blue];
    }

    // Clear reset code bytes
    memset(spiData.resetCode, 0, sizeof (spiData.resetCode));

    // Begin transfer
    Spi1DmaTransfer(&spiData, sizeof (spiData));
}

//------------------------------------------------------------------------------
// End of file
