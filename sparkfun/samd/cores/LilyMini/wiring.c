/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * System Core Clock is at 1MHz (8MHz/8) at Reset.
 * It is switched to 48MHz in the Reset Handler (startup.c)
 */
uint32_t SystemCoreClock=1000000ul ;

/*
void calibrateADC()
{
  volatile uint32_t valeur = 0;

  for(int i = 0; i < 5; ++i)
  {
    ADC->SWTRIG.bit.START = 1;
    while( ADC->INTFLAG.bit.RESRDY == 0 || ADC->STATUS.bit.SYNCBUSY == 1 )
    {
      // Waiting for a complete conversion and complete synchronization
    }

    valeur += ADC->RESULT.bit.RESULT;
  }

  valeur = valeur/5;
}*/

/*
 * Arduino Zero board initialization
 *
 * Good to know:
 *   - At reset, ResetHandler did the system clock configuration. Core is running at 48MHz.
 *   - Watchdog is disabled by default, unless someone plays with NVM User page
 *   - During reset, all PORT lines are configured as inputs with input buffers, output buffers and pull disabled.
 */
void init( void )
{
  uint32_t ul ;

  // Set Systick to 1ms interval, common to all Cortex-M variants
  if ( SysTick_Config( SystemCoreClock / 1000 ) )
  {
    // Capture error
    while ( 1 ) ;
  }
  NVIC_SetPriority (SysTick_IRQn,  (1 << __NVIC_PRIO_BITS) - 2);  /* set Priority for Systick Interrupt (2nd lowest) */

  // Clock PORT for Digital I/O
//	PM->APBBMASK.reg |= PM_APBBMASK_PORT ;
//
//  // Clock EIC for I/O interrupts
//	PM->APBAMASK.reg |= PM_APBAMASK_EIC ;

  // Clock SERCOM for Serial
  PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0 | PM_APBCMASK_SERCOM1 | PM_APBCMASK_SERCOM2 ;

  // Clock TC/TCC for Pulse and Analog
  PM->APBCMASK.reg |= PM_APBCMASK_TCC0 | PM_APBCMASK_TC1 | PM_APBCMASK_TC2 ;

  // Clock ADC/DAC for Analog
  PM->APBCMASK.reg |= PM_APBCMASK_ADC; // | PM_APBCMASK_DAC ;

  //PORT->Group[0].OUTCLR.reg = 0xFFFF; // Outputs off or pullups down 
  //PORT->Group[0].DIRCLR.reg = 0xFFFF; // Set all pins to be inputs
  //PORT->Group[0].WRCONFIG.reg = 0x4000FFFF; // Disable pullups, lower 16 pins
  //PORT->Group[0].WRCONFIG.reg = 0xC000FFFF; // Disable pullups, upper 16 pins 

  // Setup all pins (digital and analog) in INPUT mode (default is nothing)
  for ( ul = 0 ; ul < PINS_COUNT ; ul++ ) // nee NUM_DIGITAL_PINS
  {
	  pinMode( ul, INPUT ) ;
  }

  // Initialize Analog Controller
  // Setting clock
  while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID( GCM_ADC ) | // Generic Clock ADC
                      GCLK_CLKCTRL_GEN_GCLK0     | // Generic Clock Generator 0 is source
                      GCLK_CLKCTRL_CLKEN ;

  while( ADC->STATUS.bit.SYNCBUSY == 1 );          // Wait for synchronization of registers between the clock domains

  ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV512 |    // Divide Clock by 512.
                   ADC_CTRLB_RESSEL_16BIT;         // 16 bits resolution for averaging

  ADC->SAMPCTRL.reg = 0x3f;                        // Set max Sampling Time Length

  while( ADC->STATUS.bit.SYNCBUSY == 1 );          // Wait for synchronization of registers between the clock domains

  ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXNEG_GND;   // No Negative input (Internal Ground)

  // Averaging (see datasheet table in AVGCTRL register description)
  ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_4 |    // Average over 4 samples
                     ADC_AVGCTRL_ADJRES(4);       // Shift right by 4 to get 10 bits

  analogReference( AR_DEFAULT ) ; // See wiring_analog.c

  // Initialize DAC
  // Setting clock
//  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY );
//  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID( GCM_DAC ) | // Generic Clock DAC
//                      GCLK_CLKCTRL_GEN_GCLK0     | // Generic Clock Generator 0 is source
//                      GCLK_CLKCTRL_CLKEN ;
//
//  while ( DAC->STATUS.bit.SYNCBUSY == 1 ); // Wait for synchronization of registers between the clock domains
//  DAC->CTRLB.reg = DAC_CTRLB_REFSEL_AVCC | // Using the 3.3V reference
//                   DAC_CTRLB_EOEN ;        // External Output Enable (Vout)

  // Turn on bandgap reference and temperature sensor (ADC internal sources)

  SYSCTRL->VREF.reg |= (SYSCTRL_VREF_BGOUTEN | SYSCTRL_VREF_TSEN);

  // Shut down VREG in sleep, ensure power is reduced before sleeping

//  SYSCTRL->VREG.bit.RUNSTDBY = 0; // Not in CMSIS?
}

#ifdef __cplusplus
}
#endif
