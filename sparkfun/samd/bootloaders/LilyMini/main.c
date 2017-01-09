/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.

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

// Modified for 4K SAMD11 bootloader by Mike Grusin, SparkFun Electronics
// With acknowledgement to Justin Mattair, Mattairtech

#include <stdio.h>
#include <sam.h>
#include "sam_ba_monitor.h"
#include "board_definitions.h"
#include "board_driver_led.h"
#include "sam_ba_usb.h"
#include "sam_ba_cdc.h"

extern uint32_t __sketch_vectors_ptr; // Exported value from linker script
extern void board_init(void);
//static volatile long int tick = 0L;

/**
 * \brief Check the application startup condition
 *
 */
static void check_start_application(void)
{
	uint32_t* pulSketch_Start_Address;

  /*
   * Test sketch stack pointer @ &__sketch_vectors_ptr
   * Stay in SAM-BA if value @ (&__sketch_vectors_ptr) == 0xFFFFFFFF (Erased flash cell value)
   */
  if (__sketch_vectors_ptr == 0xFFFFFFFF)
  {
	LED_RED_on(); // Red: no upload present, staying in bootloader
	LED_GREEN_off();
	LED_BLUE_off();
    return;
  }

  // Prepare to jump to code

  LED_RED_off(); // All LEDs off
  LED_GREEN_off();
  LED_BLUE_off();

  /*
   * Load the sketch Reset Handler address
   * __sketch_vectors_ptr is exported from linker script and point on first 32b word of sketch vector table
   * First 32b word is sketch stack
   * Second 32b word is sketch entry point: Reset_Handler()
   */
  pulSketch_Start_Address = &__sketch_vectors_ptr ;
  pulSketch_Start_Address++ ;

  /* Rebase the Stack Pointer */
  __set_MSP( (uint32_t)(__sketch_vectors_ptr) );

  /* Rebase the vector table base address */
  SCB->VTOR = ((uint32_t)(&__sketch_vectors_ptr) & SCB_VTOR_TBLOFF_Msk);

  /* Jump to application Reset Handler in the application */
  asm("bx %0"::"r"(*pulSketch_Start_Address));
}

/**
 *  \brief SAMD21 SAM-BA Main loop.
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
  P_USB_CDC pCdc;

  // Initialize LEDs
  LED_RED_init();
  LED_GREEN_init();
  LED_BLUE_init();

  LED_RED_off();
  LED_GREEN_off();
  LED_BLUE_on(); // Blue: power on

  // Stay in bootloader if power button is held down during powerup:
  
  // Initialize button
  PORT->Group[BOARD_BUTTON_PORT].DIRCLR.reg = (1<<BOARD_BUTTON_PIN);
  PORT->Group[BOARD_BUTTON_PORT].PINCFG[BOARD_BUTTON_PIN].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
  PORT->Group[BOARD_BUTTON_PORT].OUTSET.reg = (1<<BOARD_BUTTON_PIN);

  // Read button
  if (PORT->Group[BOARD_BUTTON_PORT].IN.reg & (1<<BOARD_BUTTON_PIN)) // If high (not pressed)
  // If button is not being held down, look for uploaded code, jump to code if it exists
	check_start_application();

  // Change to 48MHz clock etc. to run USB
  board_init();
  __enable_irq();
  pCdc = usb_init();

  /* Wait for USB enumeration */
  while (1)
  {
    if (pCdc->IsConfigured(pCdc) != 0)
    {
	  LED_RED_off();
	  LED_GREEN_on(); // Green: we have a connection!
	  LED_BLUE_off();

      sam_ba_monitor_init();
	  
	  while (1)
	  {
		sam_ba_monitor_run();
	  }
	}
  }
}

//void SysTick_Handler(void)
// To use, set vector in board_startup.c, initialize in board_init.c
//{
//	tick++;
//}