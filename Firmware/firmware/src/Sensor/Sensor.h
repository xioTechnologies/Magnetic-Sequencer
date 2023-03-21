/**
 * @file Sensor.h
 * @author Seb Madgwick
 * @brief TLV493D-A1B6 3D magnetic sensor driver.
 */

#ifndef SENSOR_H
#define SENSOR_H

//------------------------------------------------------------------------------
// Includes

#include "I2C/I2CBitBang.h"
#include <stdint.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Sensor structure.
 */
typedef struct {
    const I2CBitBang i2c;
    uint8_t frameCounter;
    int16_t x;
    int16_t y;
    int16_t z;
} Sensor;

//------------------------------------------------------------------------------
// Function declarations

void SensorRead(Sensor * const sensor);

#endif

//------------------------------------------------------------------------------
// End of file
