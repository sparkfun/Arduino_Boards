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

#include "variant.h"

/*
 * Pins descriptions
 */

//TCC0 IOSET 6
//TCC1 IOSET 1
//TC0 IOSET 1
//TC1 IOSET 1
//TC2 IOSET 2
//TC3 IOSET 1
//TC4 IOSET 1
const PinDescription g_APinDescription[]=
{
  // 0..13 - Digital pins
  // ----------------------
  // 0/1 - SERCOM/UART (Serial1)
  { PORTA, 13, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TC2_CH1, NOT_ON_TIMER, EXTERNAL_INT_13 }, // RX: SERCOM2/PAD[1]
  { PORTA, 12, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TC2_CH0, NOT_ON_TIMER, EXTERNAL_INT_12 }, // TX: SERCOM2/PAD[2]

  // 2..12
  // Digital
  { NOT_A_PORT, 0,  PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { NOT_A_PORT, 0,  PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 6, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC1_CH0, TC1_CH0, EXTERNAL_INT_6 },
  { PORTA,  15, PIO_TIMER_ALT, PIN_ATTR_PWM_F, No_ADC_Channel, TCC2_CH1, TC3_CH1, EXTERNAL_INT_2  },
  { PORTA,  20, PIO_TIMER_ALT, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH0, TC7_CH0, EXTERNAL_INT_4 },
  { NOT_A_PORT, 0,  PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { NOT_A_PORT, 0,  PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  { PORTA,  7,  PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, //pin 9
  { PORTA,  18, PIO_TIMER_ALT, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH2, TC3_CH0, EXTERNAL_INT_2 },
  { PORTA,  16, PIO_TIMER_ALT, PIN_ATTR_PWM_G, No_ADC_Channel, TCC1_CH0, NOT_ON_TIMER, EXTERNAL_INT_0 },
  { PORTA,  19, PIO_TIMER_ALT, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH3, TC3_CH1, EXTERNAL_INT_3 },

  // 13 (LED)
  { PORTA, 17, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH3, TC4_CH1, EXTERNAL_INT_1 }, // TCC2/WO[1]

  // 14..19 - Analog pins
  // --------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },
  { PORTB,  8, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel2, TC4_CH0, TC4_CH0, EXTERNAL_INT_8 },
  { PORTB,  9, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel3, TC4_CH1, TC4_CH1, EXTERNAL_INT_9 },
  { PORTA,  4, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel4, TC0_CH0, TC0_CH0, EXTERNAL_INT_6 },
  { PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 },
  { PORTB,  2, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel14, TC6_CH0, TC6_CH0, EXTERNAL_INT_2 },

  // 20..21 I2C pins (SDA/SCL)
  // ----------------------
  { PORTA, 22, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TC4_CH0, TC4_CH0, EXTERNAL_INT_6 }, // SDA: SERCOM3/PAD[0]
  { PORTA, 23, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TC4_CH1, TC4_CH1, EXTERNAL_INT_7 }, // SCL: SERCOM3/PAD[1]

  // 22..24 - SPI pins (MISO,MOSI,SCK)
  // ----------------------
  { PORTB, 11, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, // MISO: SERCOM4/PAD[3]
  { PORTB, 12, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 }, // MOSI: SERCOM4/PAD[0]
  { PORTB, 13, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 }, // SCK: SERCOM4/PAD[1]

  // 25..26 - RX/TX LEDS  -- unused
  // --------------------
  { NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  // 27..29 - USB
  // --------------------
  { NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB Host enable DOES NOT EXIST ON THIS BOARD
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP

  // 30 (AREF)
  { PORTA, 3, PIO_ANALOG, PIN_ATTR_ANALOG, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // DAC/VREFP

  // ----------------------
  // 31..32 - Alternate use of A0/A4 (DAC output)
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // DAC/VOUT0
  { PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // DAC/VOUT1

  // ----------------------
  // 33..36 SPI for Flash (SCK, CS, MISO, MOSI)
  { PORTA, 9, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SCK: SERCOM0/PAD[1]
  { PORTA, 10, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, //CS: SERCOM0/PAD[2]
  { PORTA, 11, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, //MISO: SERCOM0/PAD[3]
  { PORTA, 8, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, //MOSI: SERCOM0/PAD[0]
} ;

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TCC3, TCC4, TC0, TC1, TC2, TC3, TC4, TC5 } ;
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM+TC_INST_NUM] = { TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

Uart Serial1( &sercom2, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;

void SERCOM2_0_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM2_1_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM2_2_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM2_3_Handler()
{
  Serial1.IrqHandler();
}
