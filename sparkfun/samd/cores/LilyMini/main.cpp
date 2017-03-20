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

#define ARDUINO_MAIN
#include "Arduino.h"

void __sleepIRQ();
void __wakeIRQ();

// Weak empty variant initialization function.
// May be redefined by variant files.
// void initVariant() __attribute__((weak));

volatile uint8_t __sleeping;

void __voltageFade(uint8_t fadeout)
// Sleep entry/exit indicator for RGB LED
// If parameter fadeout is true, fades from on to off. If false, fades from off to on.
// Fade the RGB LED up or down in a specific color chosen by measuring the battery voltage
// Green if above threshold ("good battery") or red if below threshold ("empty battery")
// Does not use PWM or millis() to work within IRQ
{
	int pin,bright,pwm,x;
	
	pinMode(PIN_LED_RED,OUTPUT);
	pinMode(PIN_LED_GREEN,OUTPUT);
	pinMode(PIN_LED_BLUE,OUTPUT);

	digitalWrite(PIN_LED_RED,LOW);
	digitalWrite(PIN_LED_GREEN,LOW);
	digitalWrite(PIN_LED_BLUE,LOW);

	if (analogReadBattVolts() < 250) // < 2.50V, see macro in variant.h
		pin = PIN_LED_RED;
	else
		pin = PIN_LED_GREEN;
		
#define __FADESPEED 80 // larger is slower

	if (fadeout)
	{
		digitalWrite(pin,HIGH);
		for (bright = 0; bright <= (__FADESPEED*200); bright++) __asm__ __volatile__("");

		for (bright = 255; bright >= 0; bright--)
		{
			for (x = 0; x < __FADESPEED; x++)
			{
				digitalWrite(pin,HIGH);
				for (pwm = 0; pwm <= bright; pwm++) __asm__ __volatile__("");
				digitalWrite(pin,LOW);
				for (pwm = 0; pwm <= (255-bright); pwm++) __asm__ __volatile__("");
			}
		}
	}
	else // fade in
	{
		for (bright = 0; bright <= 255; bright++)
		{
			for (x = 0; x < __FADESPEED; x++)
			{
				digitalWrite(pin,HIGH);
				for (pwm = 0; pwm <= bright; pwm++) __asm__ __volatile__("");
				digitalWrite(pin,LOW);
				for (pwm = 0; pwm <= (255-bright); pwm++) __asm__ __volatile__("");
			}
		}

		digitalWrite(pin,HIGH);
		for (bright = 0; bright <= (__FADESPEED*200); bright++) __asm__ __volatile__("");
	}	

	digitalWrite(PIN_LED_RED,LOW);
	digitalWrite(PIN_LED_GREEN,LOW);
	digitalWrite(PIN_LED_BLUE,LOW);

	pinMode(PIN_LED_RED,INPUT);
	pinMode(PIN_LED_GREEN,INPUT);
	pinMode(PIN_LED_BLUE,INPUT);
}

void __powerButtonIRQ()
// IRQ for asychronous sleep/wake
// Depends on global __sleeping variable preinitialized to false (make static local?)
{
	static uint32_t DIR,OUT,INTENAB,x;
	static uint8_t PINCFG1,PINCFG2,PINCFG3,PINCFG4,PINCFG5,PINCFG6,PINCFG7,PINCFG8;

	if (__sleeping) // wake up
	{
		__sleeping = false;

		// Clear "sleep on exit"
		SCB->SCR &= (~SCB_SCR_SLEEPONEXIT_Msk);

		SYSCTRL->VREF.reg |= (SYSCTRL_VREF_BGOUTEN | SYSCTRL_VREF_TSEN);

		// Enable preexisting input pullups only
		//PORT->Group[0].OUT.reg = (OUT & (~DIR));
		//PORT->Group[0].PINCFG[14].reg |= (PINCFG1 & 0X02); 
		//PORT->Group[0].PINCFG[15].reg |= (PINCFG2 & 0X02); 
		//PORT->Group[0].PINCFG[7].reg |= (PINCFG3 & 0X02); 
		//PORT->Group[0].PINCFG[6].reg |= (PINCFG4 & 0X02); 
		//PORT->Group[0].PINCFG[30].reg |= (PINCFG5 & 0X02); 
		//PORT->Group[0].PINCFG[27].reg |= (PINCFG6 & 0X02); 
		//PORT->Group[0].PINCFG[31].reg |= (PINCFG7 & 0X02); 
		//PORT->Group[0].PINCFG[2].reg |= (PINCFG8 & 0X02); 

		// Wait for ADC system to recover and pullups to charge input pin caps
		for (x = 0; x < 2400000; x++) __asm__ __volatile__(""); // 50ms

		// RGB wake indicator
		__voltageFade(false);

		// Restore pin configs
//		PORT->Group[0].OUT.reg = OUT; //(OUT & (~DIR)); // Enable preexisting input pullups only
		PORT->Group[0].PINCFG[14].reg = PINCFG1;
		PORT->Group[0].PINCFG[15].reg = PINCFG2;
		PORT->Group[0].PINCFG[7].reg = PINCFG3;
		PORT->Group[0].PINCFG[6].reg = PINCFG4;
		PORT->Group[0].PINCFG[30].reg = PINCFG5;
		PORT->Group[0].PINCFG[27].reg = PINCFG6;
		PORT->Group[0].PINCFG[31].reg = PINCFG7;
		PORT->Group[0].PINCFG[2].reg = PINCFG8;

		PORT->Group[0].DIR.reg = DIR;
		PORT->Group[0].OUT.reg = OUT;

		// Clear any pending interrupts
		EIC->INTFLAG.reg = 0;
		// Restore interrupts
		EIC->INTENSET.reg = INTENAB;

		// Restore USB connection
		USBDevice.init();
		USBDevice.attach();
	}
	else // go to sleep
	{
		__sleeping = true;

		// Turn off USB
		USBDevice.detach();

		// Save enabled interrupts
		INTENAB = EIC->INTENCLR.reg;
		// Disable external interrupts except this one
		EIC->INTENCLR.reg = 0b11011111;

		// Save pin values to restore on wake
		DIR = PORT->Group[0].DIR.reg; // Save all pin directions
		OUT = PORT->Group[0].OUT.reg; // Save all pin states
		PINCFG1 = PORT->Group[0].PINCFG[14].reg; // Save individual pin configs
		PINCFG2 = PORT->Group[0].PINCFG[15].reg;
		PINCFG3 = PORT->Group[0].PINCFG[7].reg;
		PINCFG4 = PORT->Group[0].PINCFG[6].reg;
		PINCFG5 = PORT->Group[0].PINCFG[30].reg;
		PINCFG6 = PORT->Group[0].PINCFG[27].reg;
		PINCFG7 = PORT->Group[0].PINCFG[31].reg;
		PINCFG8 = PORT->Group[0].PINCFG[2].reg;

		// Set all pins to lowest power state

		// Disable all pins except power
		PORT->Group[0].DIR.reg = 0; // Set all pins to be inputs
		PORT->Group[0].OUT.reg = 0x00008020; // Turn off all outputs except power ######## AND BUTTON pullups
		PORT->Group[0].WRCONFIG.reg = 0x40007FDF; // Disable pullups, lower 16 pins except A5 ############### AND A15 (REMOVE!)
//		PORT->Group[0].WRCONFIG.reg = 0x4000FFDF; // Disable pullups, lower 16 pins except A5
		PORT->Group[0].WRCONFIG.reg = 0xC000FFFF; // Disable pullups, upper 16 pins 

		// If pins are outputs, disable the pullup
		// Keep pullups active for inputs, disable for former outputs (avoid LED glow through pullup)
		//if (DIR & (1<<14)) /* output */ PORT->Group[0].PINCFG[14].reg = 0;
		//if (DIR & (1<<15)) /* output */ PORT->Group[0].PINCFG[15].reg = 0;
		//if (DIR & (1<<7)) /* output */ PORT->Group[0].PINCFG[7].reg = 0;
		//if (DIR & (1<<6)) /* output */ PORT->Group[0].PINCFG[6].reg = 0;
		//if (DIR & (1<<30)) /* output */ PORT->Group[0].PINCFG[30].reg = 0;
		//if (DIR & (1<<27)) /* output */ PORT->Group[0].PINCFG[27].reg = 0;
		//if (DIR & (1<<31)) /* output */ PORT->Group[0].PINCFG[31].reg = 0;
		//if (DIR & (1<<2)) /* output */ PORT->Group[0].PINCFG[2].reg = 0;

		// Wait for voltage to stabilize before ADC read
//		for (x = 0; x < 2400000; x++) __asm__ __volatile__(""); // 50ms
		__voltageFade(true);

		// Misc low-power settings
//		NVMCTRL->CTRLB.bit.SLEEPPRM = NVMCTRL_CTRLB_SLEEPPRM_WAKEUPINSTANT_Val;
 	    // Turn off bandgap reference and temperature sensor (ADC internal sources)
		SYSCTRL->VREF.reg &= ~(SYSCTRL_VREF_BGOUTEN | SYSCTRL_VREF_TSEN);
		
		// Set deep sleep + sleep on exit: system will WFI after IRQ exits
		SCB->SCR |= (SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk);

	}
}

void initVariant()
{
	// Preset onboard RGB LED to outputs/off
	pinMode(PIN_LED_RED,OUTPUT);
	pinMode(PIN_LED_GREEN,OUTPUT);
	pinMode(PIN_LED_BLUE,OUTPUT);
	digitalWrite(PIN_LED_RED,LOW);
	digitalWrite(PIN_LED_GREEN,LOW);
	digitalWrite(PIN_LED_BLUE,LOW);

	// Set up power button for sleep / wake
	__sleeping = false;
	pinMode(PIN_BUTTON,INPUT_PULLUP);
    attachInterrupt(PIN_BUTTON,__powerButtonIRQ,LOW);

	// Turn on "+" sewtab
	pinMode(PIN_POWER,OUTPUT);
	digitalWrite(PIN_POWER,HIGH);
}

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
  init();
  initVariant();

  delay(1);
#if defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif

  setup();

  for (;;)
  {
    loop();
    if (serialEventRun) serialEventRun();
  }

  return 0;
}
