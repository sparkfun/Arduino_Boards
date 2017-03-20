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

#ifndef _VARIANT_SPARKFUN_LILYMINI_
#define _VARIANT_SPARKFUN_LILYMINI_

// The definitions here needs a SAMD core >=1.6.3
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10603

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK			  (48000000ul)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (13u)
#define NUM_DIGITAL_PINS     (10u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (0u)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
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

// Interrupts
#define digitalPinToInterrupt(P)   ( g_APinDescription[P].ulExtInt )

// Digital pins
#define LED_RED              (5u)
#define LED_GREEN            (6u)
#define LED_BLUE             (7u)
#define LED_BUILTIN			 (5u) // Introduced in Arduino 1.8, tied to red LED

#define PIN_LED_RED          (5u)
#define PIN_LED_GREEN        (6u)
#define PIN_LED_BLUE         (7u)
#define PIN_POWER			 (8u)
#define PIN_BUTTON			 (11u)

// Analog pins
#define PIN_A0               (1ul)
#define PIN_A1               (1ul)
#define PIN_A2               (2ul)
#define PIN_A3               (3ul)
#define PIN_A4               (4ul)

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
#define ADC_RESOLUTION		10

// Internal "pins"
#define PIN_BATT			(ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val)
#define PIN_1V				(ADC_INPUTCTRL_MUXPOS_BANDGAP_Val)
#define PIN_TEMP			(ADC_INPUTCTRL_MUXPOS_TEMP_Val)

#define analogReadBattVolts() ((analogRead(PIN_BATT)*4000)/((analogRead(PIN_1V)*100)/11))	// will be e.g. 199 for 1.99V
#define analogReadVolts(pin) ((analogRead(pin)*1000)/((analogRead(PIN_1V)*100)/11))			// will be e.g. 199 for 1.99V

// Serial (SERCOM0)
#define PIN_SERIAL_RX       (3ul)
#define PIN_SERIAL_TX       (4ul)
#define PAD_SERIAL_TX       (UART_TX_PAD_0)
#define PAD_SERIAL_RX       (SERCOM_RX_PAD_1)

// SPI
#define SPI_INTERFACES_COUNT 1
#define PIN_SPI_MISO         (4u)
#define PIN_SPI_MOSI         (1u)
#define PIN_SPI_SCK          (2u)
#define PIN_SPI_SS           (3u)
#define PERIPH_SPI           sercom1
// Pad Map:     0       1   2     3
//          MOSI (TX)  SCK  SS  MOSI (RX)
#define PAD_SPI_TX           SPI_PAD_0_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_3

static const uint8_t SS	  = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// I2C (wire)
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (1u)
#define PIN_WIRE_SCL         (2u)
#define PERIPH_WIRE          sercom2
#define WIRE_IT_HANDLER      SERCOM2_Handler

// USB
#define PIN_USB_DM          (9ul)
#define PIN_USB_DP          (10ul)

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
*/
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;

extern Uart Serial0;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         Serial0
// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial0
#define SERIAL_PORT_HARDWARE_OPEN   Serial0

#define Serial                      SerialUSB
#define SerialPins					Serial0

#endif /* _VARIANT_SPARKFUN_LILYMINI_ */

