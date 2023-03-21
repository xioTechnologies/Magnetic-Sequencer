/**
 * @file Sensor.c
 * @author Seb Madgwick
 * @brief TLV493D-A1B6 3D magnetic sensor driver.
 */

//------------------------------------------------------------------------------
// Includes

#include "I2C/I2CStartSequence.h"
#include "Sensor.h"
#include <string.h> // memset

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief I2C slave address.
 */
#define I2C_SLAVE_ADDRESS (0x5E)

/**
 * @brief Temp register.
 */
typedef struct {
    unsigned int ch : 2;
    unsigned int frm : 2;
    unsigned int temp : 4;
} __attribute__((__packed__)) TempRegister;

/**
 * @brief Bx2 register.
 */
typedef struct {
    unsigned int by : 4;
    unsigned int bx : 4;
} __attribute__((__packed__)) Bx2Register;

/**
 * @brief Bz2 register.
 */
typedef struct {
    unsigned int bz : 4;
    unsigned int pd : 1;
    unsigned int ff : 1;
    unsigned int t : 1;
    unsigned int : 1;
} __attribute__((__packed__)) Bz2Register;

/**
 * @brief FactSet1 register.
 */
typedef struct {
    unsigned int : 3;
    unsigned int bits3to4 : 2;
    unsigned int : 3;
} __attribute__((__packed__))FactSet1Register;

/**
 * @brief FactSet3 register.
 */
typedef struct {
    unsigned int bits0to4 : 5;
    unsigned int : 3;
} __attribute__((__packed__)) FactSet3Register;

/**
 * @brief Read registers.
 */
typedef union {

    struct {
        uint8_t bx;
        uint8_t by;
        uint8_t bz;
        TempRegister temp;
        Bx2Register bx2;
        Bz2Register bz2;
        uint8_t temp2;
        FactSet1Register factSet1;
        uint8_t factSet2;
        FactSet3Register factSet3;
    } __attribute__((__packed__));
    uint8_t array[10];
} ReadRegisters;

/**
 * @brief MOD1 register.
 */
typedef struct {
    unsigned int low : 1;
    unsigned int fast : 1;
    unsigned int inter : 1;
    unsigned int factSet : 2;
    unsigned int iicAddr : 2;
    unsigned int p : 1;
} __attribute__((__packed__)) Mod1Register;

/**
 * @brief MOD2 register.
 */
typedef struct {
    unsigned int factSet : 5;
    unsigned int pt : 1;
    unsigned int lp : 1;
    unsigned int t : 1;
} __attribute__((__packed__)) Mod2Register;

/**
 * @brief Write registers.
 */
typedef union {

    struct {
        uint8_t res;
        Mod1Register mod1;
        uint8_t res2;
        Mod2Register mod2;
    };
    uint8_t array[4];
} WriteRegisters;

//------------------------------------------------------------------------------
// Function declarations

static void Reset(const I2CBitBang * const i2cBitBang);
static void Read(const I2CBitBang * const i2cBitBang, ReadRegisters * const registers);
static void Write(const I2CBitBang * const i2cBitBang, const WriteRegisters * const registers);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Reads the sensor.
 * @param sensor Sensor structure.
 */
void SensorRead(Sensor * const sensor) {

    // Read registers
    ReadRegisters readRegisters;
    Read(&sensor->i2c, &readRegisters);

    // Reset if frame counter has not incremented
    if (readRegisters.temp.frm == sensor->frameCounter) {

        // Reset
        Reset(&sensor->i2c);

        // Read registers
        Read(&sensor->i2c, &readRegisters);

        // Write registers (configure for Master Controlled Mode)
        WriteRegisters writeregisters;
        memset(&writeregisters, 0, sizeof (WriteRegisters));
        writeregisters.mod1.low = 1; // low-power mode enabled
        writeregisters.mod1.fast = 1; // fast mode enabled
        writeregisters.mod1.factSet = readRegisters.factSet1.bits3to4;
        writeregisters.res2 = readRegisters.factSet2;
        writeregisters.mod2.factSet = readRegisters.factSet3.bits0to4;
        writeregisters.mod2.pt = 0; // parity test disabled
        Write(&sensor->i2c, &writeregisters);
    }

    // Store measurements
    sensor->x = (int16_t) ((int16_t) readRegisters.bx << 8 | (int16_t) readRegisters.bx2.bx << 4) / 16;
    sensor->y = (int16_t) ((int16_t) readRegisters.by << 8 | (int16_t) readRegisters.bx2.by << 4) / 16;
    sensor->z = (int16_t) ((int16_t) readRegisters.bz << 8 | (int16_t) readRegisters.bz2.bz << 4) / 16;
    sensor->frameCounter = readRegisters.temp.frm;
}

/**
 * @brief Resets device.
 * @param i2cBitBang I2C bit bang structure.
 */
static void Reset(const I2CBitBang * const i2cBitBang) {
    I2CBitBangStart(i2cBitBang);
    I2CBitBangSend(i2cBitBang, 0x00);
    I2CBitBangStop(i2cBitBang);
}

/**
 * @brief Reads registers.
 * @param i2cBitBang I2C bit bang structure.
 * @param registers Read registers.
 */
static void Read(const I2CBitBang * const i2cBitBang, ReadRegisters * const registers) {
    I2CBitBangStart(i2cBitBang);
    I2CBitBangSend(i2cBitBang, I2CSlaveAddressWrite(I2C_SLAVE_ADDRESS));
    I2CBitBangSend(i2cBitBang, 0x00);
    I2CBitBangRepeatedStart(i2cBitBang);
    I2CBitBangSend(i2cBitBang, I2CSlaveAddressRead(I2C_SLAVE_ADDRESS));
    for (int index = 0; index < sizeof (ReadRegisters); index++) {
        registers->array[index] = I2CBitBangReceive(i2cBitBang, index != (sizeof (ReadRegisters) - 1));
    }
    I2CBitBangStop(i2cBitBang);
}

/**
 * @brief Writes registers.
 * @param i2cBitBang I2C bit bang structure.
 * @param registers Write registers.
 */
static void Write(const I2CBitBang * const i2cBitBang, const WriteRegisters * const registers) {
    I2CBitBangStart(i2cBitBang);
    I2CBitBangSend(i2cBitBang, I2CSlaveAddressWrite(I2C_SLAVE_ADDRESS));
    I2CBitBangSend(i2cBitBang, 0x00);
    I2CBitBangRepeatedStart(i2cBitBang);
    I2CBitBangSend(i2cBitBang, I2CSlaveAddressWrite(I2C_SLAVE_ADDRESS));
    for (int index = 0; index < sizeof (WriteRegisters); index++) {
        I2CBitBangSend(i2cBitBang, registers->array[index]);
    }
    I2CBitBangStop(i2cBitBang);
}

//------------------------------------------------------------------------------
// End of file
