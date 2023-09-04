/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for SCL0 pin ***/
#define SCL0_Set()               (LATESET = (1<<5))
#define SCL0_Clear()             (LATECLR = (1<<5))
#define SCL0_Toggle()            (LATEINV= (1<<5))
#define SCL0_OutputEnable()      (TRISECLR = (1<<5))
#define SCL0_InputEnable()       (TRISESET = (1<<5))
#define SCL0_Get()               ((PORTE >> 5) & 0x1)
#define SCL0_PIN                  GPIO_PIN_RE5

/*** Macros for SCL1 pin ***/
#define SCL1_Set()               (LATESET = (1<<6))
#define SCL1_Clear()             (LATECLR = (1<<6))
#define SCL1_Toggle()            (LATEINV= (1<<6))
#define SCL1_OutputEnable()      (TRISECLR = (1<<6))
#define SCL1_InputEnable()       (TRISESET = (1<<6))
#define SCL1_Get()               ((PORTE >> 6) & 0x1)
#define SCL1_PIN                  GPIO_PIN_RE6

/*** Macros for SCL2 pin ***/
#define SCL2_Set()               (LATESET = (1<<7))
#define SCL2_Clear()             (LATECLR = (1<<7))
#define SCL2_Toggle()            (LATEINV= (1<<7))
#define SCL2_OutputEnable()      (TRISECLR = (1<<7))
#define SCL2_InputEnable()       (TRISESET = (1<<7))
#define SCL2_Get()               ((PORTE >> 7) & 0x1)
#define SCL2_PIN                  GPIO_PIN_RE7

/*** Macros for SCL3 pin ***/
#define SCL3_Set()               (LATGSET = (1<<6))
#define SCL3_Clear()             (LATGCLR = (1<<6))
#define SCL3_Toggle()            (LATGINV= (1<<6))
#define SCL3_OutputEnable()      (TRISGCLR = (1<<6))
#define SCL3_InputEnable()       (TRISGSET = (1<<6))
#define SCL3_Get()               ((PORTG >> 6) & 0x1)
#define SCL3_PIN                  GPIO_PIN_RG6

/*** Macros for SCL4 pin ***/
#define SCL4_Set()               (LATGSET = (1<<7))
#define SCL4_Clear()             (LATGCLR = (1<<7))
#define SCL4_Toggle()            (LATGINV= (1<<7))
#define SCL4_OutputEnable()      (TRISGCLR = (1<<7))
#define SCL4_InputEnable()       (TRISGSET = (1<<7))
#define SCL4_Get()               ((PORTG >> 7) & 0x1)
#define SCL4_PIN                  GPIO_PIN_RG7

/*** Macros for SCL5 pin ***/
#define SCL5_Set()               (LATGSET = (1<<8))
#define SCL5_Clear()             (LATGCLR = (1<<8))
#define SCL5_Toggle()            (LATGINV= (1<<8))
#define SCL5_OutputEnable()      (TRISGCLR = (1<<8))
#define SCL5_InputEnable()       (TRISGSET = (1<<8))
#define SCL5_Get()               ((PORTG >> 8) & 0x1)
#define SCL5_PIN                  GPIO_PIN_RG8

/*** Macros for SCL6 pin ***/
#define SCL6_Set()               (LATGSET = (1<<9))
#define SCL6_Clear()             (LATGCLR = (1<<9))
#define SCL6_Toggle()            (LATGINV= (1<<9))
#define SCL6_OutputEnable()      (TRISGCLR = (1<<9))
#define SCL6_InputEnable()       (TRISGSET = (1<<9))
#define SCL6_Get()               ((PORTG >> 9) & 0x1)
#define SCL6_PIN                  GPIO_PIN_RG9

/*** Macros for SCL7 pin ***/
#define SCL7_Set()               (LATBSET = (1<<5))
#define SCL7_Clear()             (LATBCLR = (1<<5))
#define SCL7_Toggle()            (LATBINV= (1<<5))
#define SCL7_OutputEnable()      (TRISBCLR = (1<<5))
#define SCL7_InputEnable()       (TRISBSET = (1<<5))
#define SCL7_Get()               ((PORTB >> 5) & 0x1)
#define SCL7_PIN                  GPIO_PIN_RB5

/*** Macros for RTS pin ***/
#define RTS_Get()               ((PORTB >> 14) & 0x1)
#define RTS_PIN                  GPIO_PIN_RB14

/*** Macros for CTS pin ***/
#define CTS_Get()               ((PORTB >> 15) & 0x1)
#define CTS_PIN                  GPIO_PIN_RB15

/*** Macros for RX pin ***/
#define RX_Get()               ((PORTF >> 4) & 0x1)
#define RX_PIN                  GPIO_PIN_RF4

/*** Macros for TX pin ***/
#define TX_Get()               ((PORTF >> 5) & 0x1)
#define TX_PIN                  GPIO_PIN_RF5

/*** Macros for VBUS_DETECT pin ***/
#define VBUS_DETECT_Set()               (LATFSET = (1<<3))
#define VBUS_DETECT_Clear()             (LATFCLR = (1<<3))
#define VBUS_DETECT_Toggle()            (LATFINV= (1<<3))
#define VBUS_DETECT_OutputEnable()      (TRISFCLR = (1<<3))
#define VBUS_DETECT_InputEnable()       (TRISFSET = (1<<3))
#define VBUS_DETECT_Get()               ((PORTF >> 3) & 0x1)
#define VBUS_DETECT_PIN                  GPIO_PIN_RF3

/*** Macros for CLKI pin ***/
#define CLKI_Get()               ((PORTC >> 12) & 0x1)
#define CLKI_PIN                  GPIO_PIN_RC12

/*** Macros for SDA7 pin ***/
#define SDA7_Set()               (LATCSET = (1<<15))
#define SDA7_Clear()             (LATCCLR = (1<<15))
#define SDA7_Toggle()            (LATCINV= (1<<15))
#define SDA7_OutputEnable()      (TRISCCLR = (1<<15))
#define SDA7_InputEnable()       (TRISCSET = (1<<15))
#define SDA7_Get()               ((PORTC >> 15) & 0x1)
#define SDA7_PIN                  GPIO_PIN_RC15

/*** Macros for SDA6 pin ***/
#define SDA6_Set()               (LATDSET = (1<<8))
#define SDA6_Clear()             (LATDCLR = (1<<8))
#define SDA6_Toggle()            (LATDINV= (1<<8))
#define SDA6_OutputEnable()      (TRISDCLR = (1<<8))
#define SDA6_InputEnable()       (TRISDSET = (1<<8))
#define SDA6_Get()               ((PORTD >> 8) & 0x1)
#define SDA6_PIN                  GPIO_PIN_RD8

/*** Macros for SDA5 pin ***/
#define SDA5_Set()               (LATDSET = (1<<9))
#define SDA5_Clear()             (LATDCLR = (1<<9))
#define SDA5_Toggle()            (LATDINV= (1<<9))
#define SDA5_OutputEnable()      (TRISDCLR = (1<<9))
#define SDA5_InputEnable()       (TRISDSET = (1<<9))
#define SDA5_Get()               ((PORTD >> 9) & 0x1)
#define SDA5_PIN                  GPIO_PIN_RD9

/*** Macros for SDA4 pin ***/
#define SDA4_Set()               (LATDSET = (1<<10))
#define SDA4_Clear()             (LATDCLR = (1<<10))
#define SDA4_Toggle()            (LATDINV= (1<<10))
#define SDA4_OutputEnable()      (TRISDCLR = (1<<10))
#define SDA4_InputEnable()       (TRISDSET = (1<<10))
#define SDA4_Get()               ((PORTD >> 10) & 0x1)
#define SDA4_PIN                  GPIO_PIN_RD10

/*** Macros for SDA3 pin ***/
#define SDA3_Set()               (LATDSET = (1<<11))
#define SDA3_Clear()             (LATDCLR = (1<<11))
#define SDA3_Toggle()            (LATDINV= (1<<11))
#define SDA3_OutputEnable()      (TRISDCLR = (1<<11))
#define SDA3_InputEnable()       (TRISDSET = (1<<11))
#define SDA3_Get()               ((PORTD >> 11) & 0x1)
#define SDA3_PIN                  GPIO_PIN_RD11

/*** Macros for SDA2 pin ***/
#define SDA2_Set()               (LATDSET = (1<<0))
#define SDA2_Clear()             (LATDCLR = (1<<0))
#define SDA2_Toggle()            (LATDINV= (1<<0))
#define SDA2_OutputEnable()      (TRISDCLR = (1<<0))
#define SDA2_InputEnable()       (TRISDSET = (1<<0))
#define SDA2_Get()               ((PORTD >> 0) & 0x1)
#define SDA2_PIN                  GPIO_PIN_RD0

/*** Macros for SDA1 pin ***/
#define SDA1_Set()               (LATCSET = (1<<13))
#define SDA1_Clear()             (LATCCLR = (1<<13))
#define SDA1_Toggle()            (LATCINV= (1<<13))
#define SDA1_OutputEnable()      (TRISCCLR = (1<<13))
#define SDA1_InputEnable()       (TRISCSET = (1<<13))
#define SDA1_Get()               ((PORTC >> 13) & 0x1)
#define SDA1_PIN                  GPIO_PIN_RC13

/*** Macros for SDA0 pin ***/
#define SDA0_Set()               (LATCSET = (1<<14))
#define SDA0_Clear()             (LATCCLR = (1<<14))
#define SDA0_Toggle()            (LATCINV= (1<<14))
#define SDA0_OutputEnable()      (TRISCCLR = (1<<14))
#define SDA0_InputEnable()       (TRISCSET = (1<<14))
#define SDA0_Get()               ((PORTC >> 14) & 0x1)
#define SDA0_PIN                  GPIO_PIN_RC14

/*** Macros for RGB pin ***/
#define RGB_Get()               ((PORTE >> 3) & 0x1)
#define RGB_PIN                  GPIO_PIN_RE3


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/
#define    GPIO_PORT_B  (0U)
#define    GPIO_PORT_C  (1U)
#define    GPIO_PORT_D  (2U)
#define    GPIO_PORT_E  (3U)
#define    GPIO_PORT_F  (4U)
#define    GPIO_PORT_G  (5U)
typedef uint32_t GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/
#define    GPIO_PIN_RB0  (0U)
#define    GPIO_PIN_RB1  (1U)
#define    GPIO_PIN_RB2  (2U)
#define    GPIO_PIN_RB3  (3U)
#define    GPIO_PIN_RB4  (4U)
#define    GPIO_PIN_RB5  (5U)
#define    GPIO_PIN_RB6  (6U)
#define    GPIO_PIN_RB7  (7U)
#define    GPIO_PIN_RB8  (8U)
#define    GPIO_PIN_RB9  (9U)
#define    GPIO_PIN_RB10  (10U)
#define    GPIO_PIN_RB11  (11U)
#define    GPIO_PIN_RB12  (12U)
#define    GPIO_PIN_RB13  (13U)
#define    GPIO_PIN_RB14  (14U)
#define    GPIO_PIN_RB15  (15U)
#define    GPIO_PIN_RC12  (28U)
#define    GPIO_PIN_RC13  (29U)
#define    GPIO_PIN_RC14  (30U)
#define    GPIO_PIN_RC15  (31U)
#define    GPIO_PIN_RD0  (32U)
#define    GPIO_PIN_RD1  (33U)
#define    GPIO_PIN_RD2  (34U)
#define    GPIO_PIN_RD3  (35U)
#define    GPIO_PIN_RD4  (36U)
#define    GPIO_PIN_RD5  (37U)
#define    GPIO_PIN_RD6  (38U)
#define    GPIO_PIN_RD7  (39U)
#define    GPIO_PIN_RD8  (40U)
#define    GPIO_PIN_RD9  (41U)
#define    GPIO_PIN_RD10  (42U)
#define    GPIO_PIN_RD11  (43U)
#define    GPIO_PIN_RE0  (48U)
#define    GPIO_PIN_RE1  (49U)
#define    GPIO_PIN_RE2  (50U)
#define    GPIO_PIN_RE3  (51U)
#define    GPIO_PIN_RE4  (52U)
#define    GPIO_PIN_RE5  (53U)
#define    GPIO_PIN_RE6  (54U)
#define    GPIO_PIN_RE7  (55U)
#define    GPIO_PIN_RF0  (64U)
#define    GPIO_PIN_RF1  (65U)
#define    GPIO_PIN_RF3  (67U)
#define    GPIO_PIN_RF4  (68U)
#define    GPIO_PIN_RF5  (69U)
#define    GPIO_PIN_RG6  (86U)
#define    GPIO_PIN_RG7  (87U)
#define    GPIO_PIN_RG8  (88U)
#define    GPIO_PIN_RG9  (89U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE    (-1)

typedef uint32_t GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xFU), (uint32_t)(value) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xFU)) & 0x1U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xFU)) & 0x1U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1UL << (pin & 0xFU));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
