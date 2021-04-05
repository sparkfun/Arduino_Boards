/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_SAMD51_MICROMOD_
#define _VARIANT_SAMD51_MICROMOD_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

//----------------------------------------------------------------------------
//        Definitions
//----------------------------------------------------------------------------

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK			  (120000000ul)

#define VARIANT_GCLK0_FREQ (120000000UL)
#define VARIANT_GCLK1_FREQ (48000000UL)
#define VARIANT_GCLK2_FREQ (100000000UL)

//----------------------------------------------------------------------------
//        Headers
//----------------------------------------------------------------------------

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//----------------------------------------------------------------------------
//        Pins
//----------------------------------------------------------------------------

// Number of pins defined in PinDescription array
#define PINS_COUNT           (53u)
#define NUM_DIGITAL_PINS     (16u)
#define NUM_ANALOG_INPUTS    (11u)
#define NUM_ANALOG_OUTPUTS   (1u)
#define analogInputToDigitalPin(p)  ((p < 6u) ? (p) + 14u : -1)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port)   ( &(port->OUT.reg) )
#define portInputRegister(port)    ( &(port->IN.reg) )
#define portModeRegister(port)     ( &(port->DIR.reg) )
#define digitalPinHasPWM(P)        ( g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// General Purpose Pins
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5

#define G0  2
#define G1  3
#define G2  4
#define G3  5
#define G4  6
#define G5  7
#define G6  8
#define G7  9
#define G8  10
#define G9  11
#define G11 29

#define PWM0 19
#define PWM1 20 

#define BATT_VIN 21 
#define POWER_CONTROL 12

#define CS 48 
#define CS1 52 
#define I2CINT 12

#define AUD_OUT 40
#define AUD_IN 41
#define AUD_BCLK 42
#define AUD_LRCLK 44
#define AUD_MCLK 43

// LEDs
//-------------------------------------------
#define PIN_LED_13           (13u)
#define PIN_LED              PIN_LED_13
#define LED_BUILTIN          PIN_LED_13
//-------------------------------------------

// Analog pins
//-------------------------------------------
#define PIN_A0               (17ul)
#define PIN_A1               (PIN_A0 + 1)
#define PIN_A2               (PIN_A0 + 2)
#define PIN_A3               (PIN_A0 + 4)
#define PIN_A4               (PIN_A0 + 5)
#define PIN_A5               (PIN_A0 + 6)
#define PIN_A6               (PIN_A0 + 7)
#define PIN_A7               (PIN_A0 + 8)
#define PIN_A8               (PIN_A0 + 9)
#define PIN_A9               (PIN_A0 + 10)
#define PIN_A10              (PIN_A0) 

//DAC
#define PIN_DAC0             PIN_A0

static const uint8_t A0   = PIN_A0;
static const uint8_t A1   = PIN_A1;
static const uint8_t A2   = PIN_A2;
static const uint8_t A3   = PIN_A3;
static const uint8_t A4   = PIN_A4;
static const uint8_t A5   = PIN_A5;
static const uint8_t A6   = PIN_A6;
static const uint8_t A7   = PIN_A7;
static const uint8_t A8   = PIN_A8;
static const uint8_t A9   = PIN_A9;
static const uint8_t A10  = PIN_A10;

static const uint8_t DAC0 = PIN_DAC0;

#define ADC_RESOLUTION		12
//-------------------------------------------

// Other pins
//-------------------------------------------
#define PIN_ATN              (53ul)
static const uint8_t ATN = PIN_ATN;
//-------------------------------------------

// Serial1 
//-------------------------------------------
#define PIN_SERIAL1_RX       (32ul)
#define PIN_SERIAL1_TX       (33ul)
#define PAD_SERIAL1_TX       (UART_TX_PAD_0)
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)
//-------------------------------------------

// SPI Interfaces
//-------------------------------------------
#define SPI_INTERFACES_COUNT 2
  
#define PIN_SPI_MOSI         (45u)
#define PIN_SPI_SCK          (46u)
#define PIN_SPI_MISO         (47u)
#define PIN_SPI_SS           (48u)
#define PERIPH_SPI           sercom0
#define PAD_SPI_TX           SPI_PAD_0_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_2

static const uint8_t SS	  = PIN_SPI_SS ;
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;  

// SPI1
#define PIN_SPI1_MOSI         (49u)
#define PIN_SPI1_SCK          (50u)
#define PIN_SPI1_MISO         (51u)
#define PIN_SPI1_SS           (52u)
#define PERIPH_SPI1           sercom2
#define PAD_SPI1_TX           SPI_PAD_0_SCK_1
#define PAD_SPI1_RX           SERCOM_RX_PAD_2
//-------------------------------------------

static const uint8_t SS1	 = PIN_SPI1_SS ; 	
static const uint8_t MOSI1 = PIN_SPI1_MOSI ;
static const uint8_t MISO1 = PIN_SPI1_MISO ;
static const uint8_t SCK1  = PIN_SPI1_SCK ;

// Wire Interfaces
//-------------------------------------------
#define WIRE_INTERFACES_COUNT 2

#define PIN_WIRE_SCL         (34u)
#define PIN_WIRE_SDA         (35u)
#define PERIPH_WIRE          sercom3
#define WIRE_IT_HANDLER      SERCOM3_Handler
#define WIRE_IT_HANDLER_0    SERCOM3_0_Handler
#define WIRE_IT_HANDLER_1    SERCOM3_1_Handler
#define WIRE_IT_HANDLER_2    SERCOM3_2_Handler
#define WIRE_IT_HANDLER_3    SERCOM3_3_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#define PIN_WIRE1_SCL         (36u)
#define PIN_WIRE1_SDA         (37u)
#define PERIPH_WIRE1          sercom4
#define WIRE1_IT_HANDLER      SERCOM4_Handler
#define WIRE1_IT_HANDLER_0    SERCOM4_0_Handler
#define WIRE1_IT_HANDLER_1    SERCOM4_1_Handler
#define WIRE1_IT_HANDLER_2    SERCOM4_2_Handler
#define WIRE1_IT_HANDLER_3    SERCOM4_3_Handler

static const uint8_t SDA1 = PIN_WIRE1_SDA;
static const uint8_t SCL1 = PIN_WIRE1_SCL;
//----------------------------------------------

// USB
//----------------------------------------------
#define PIN_USB_HOST_ENABLE (29ul)
#define PIN_USB_DM          (30ul)
#define PIN_USB_DP          (31ul)
//----------------------------------------------

// I2S Interfaces
#define PIN_I2S_FS           (44u)
//----------------------------------------------
#define I2S_INTERFACES_COUNT 1

#define I2S_DEVICE           0
#define I2S_CLOCK_GENERATOR  3

#define PIN_I2S_SDO          (40u)
#define PIN_I2S_SDI          (41u)
#define PIN_I2S_SCK          (42u)
#define PIN_I2S_MCK          (43u)
#define PIN_I2S_FS           (44u)
//----------------------------------------------


#if !defined(VARIANT_QSPI_BAUD_DEFAULT)
  #define VARIANT_QSPI_BAUD_DEFAULT 5000000
#endif

#ifdef __cplusplus
}
#endif

//----------------------------------------------------------------------------
//        Arduino objects - C++ only
//----------------------------------------------------------------------------

#ifdef __cplusplus

//	------------------------
//	 SERCOM DEFINITION
//	------------------------
extern SERCOM sercom0; //SPI
extern SERCOM sercom1; // I2S occupies lines
extern SERCOM sercom2; //SPI1
extern SERCOM sercom3; //I2C 
extern SERCOM sercom4; //I2C1 or Serial2
extern SERCOM sercom5; //Serial1

extern Uart Serial1;

#endif
/*
* These serial port names are intended to allow libraries and architecture-neutral
* sketches to automatically default to the correct port name for a particular type
* of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
* the first hardware serial port whose RX/TX pins are not dedicated to another use.
*
* SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
*
* SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
*
* SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
*
* SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
*
* SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
*                            pins are NOT connected to anything by default.
*/
#define SERIAL_PORT_USBVIRTUAL      Serial
#define SERIAL_PORT_MONITOR         Serial
// Serial has no physical pins broken out, so it's not listed as HARDWARE port

#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

#endif // SAMD51 MicroMod Processor Board

