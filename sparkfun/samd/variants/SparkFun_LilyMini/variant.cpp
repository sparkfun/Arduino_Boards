/*
  SparkFul LilyMini Configuration File

  Based on Arduino SAMD21 configuration files,
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
 * Pin descriptions
 */
const PinDescription g_APinDescription[]=
{
// Pin array starts at 0, but LilyMini sewtaps start at 1, so duplicate pin 0 = pin 1
/* sewtap 0*/{ PORTA, 14, PIO_DIGITAL,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_EXTINT), ADC_Channel6,   PWM0_CH0,   TCC0_CH0,      EXTERNAL_INT_NMI }, // 0
/* sewtap 1*/{ PORTA, 14, PIO_DIGITAL,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_EXTINT), ADC_Channel6,   PWM0_CH0,   TCC0_CH0,      EXTERNAL_INT_NMI }, // 1
/* sewtap 2*/{ PORTA, 15, PIO_DIGITAL,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_EXTINT), ADC_Channel7,   PWM0_CH1,   TCC0_CH1,      EXTERNAL_INT_1 },   // 2
/* sewtap 3*/{ PORTA,  7, PIO_DIGITAL,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_EXTINT), ADC_Channel5,   PWM0_CH3,   TCC0_CH3,      EXTERNAL_INT_7 },   // 3
/* sewtap 4*/{ PORTA,  6, PIO_DIGITAL,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_EXTINT), ADC_Channel4,   PWM0_CH2,   TCC0_CH2,      EXTERNAL_INT_6 },   // 4
/*red LED 5*/{ PORTA, 30, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),                                 No_ADC_Channel, PWM2_CH0,   TC2_CH0,       EXTERNAL_INT_NONE },// 5 
/*grn LED 6*/{ PORTA, 27, PIO_OUTPUT, (PIN_ATTR_DIGITAL/*|PIN_ATTR_PWM*/),                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER,  EXTERNAL_INT_NONE },// 6
/*blu LED 7*/{ PORTA, 31, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),                                 No_ADC_Channel, PWM2_CH1,   TC2_CH1,       EXTERNAL_INT_NONE },// 7
/*sewtap+ 8*/{ PORTA,  2, PIO_OUTPUT, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL/*|PIN_ATTR_PWM*/),             ADC_Channel0,   NOT_ON_PWM, NOT_ON_TIMER,  EXTERNAL_INT_NONE },// 8
/*USB DM  9*/{ PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // 9
/*USB DP 10*/{ PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // 10
/*button 11*/{ PORTA,  5, PIO_DIGITAL, (PIN_ATTR_EXTINT), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 },       // 11
/*unused 12*/{ NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 12
/*red LED 13*/{ PORTA, 30, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),No_ADC_Channel,PWM2_CH0,TC2_CH0,EXTERNAL_INT_NONE }, // 13 
// Note that pin 13 is mapped to red LED to support example code that uses pin 13
} ;

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TC1, TC2 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;

Uart Serial0( &sercom0, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX ) ;

void SERCOM0_Handler()
{
  Serial0.IrqHandler();
}

