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

#ifndef _BOARD_DRIVER_LED_
#define _BOARD_DRIVER_LED_

#include <sam.h>
#include "board_definitions.h"

inline void LED_RED_init(void) { PORT->Group[BOARD_LED_RED_PORT].WRCONFIG.reg = (PORT_WRCONFIG_HWSEL | PORT_WRCONFIG_WRPINCFG | /* PORT_WRCONFIG_DRVSTR | */ (1 << 14)); \
PORT->Group[BOARD_LED_RED_PORT].DIRSET.reg = (1<<BOARD_LED_RED_PIN); }
//inline void LED_RED_init(void) { PORT->Group[BOARD_LED_RED_PORT].DIRSET.reg = (1<<BOARD_LED_RED_PIN); }
inline void LED_RED_on(void) { PORT->Group[BOARD_LED_RED_PORT].OUTCLR.reg = (1<<BOARD_LED_RED_PIN); }
inline void LED_RED_off(void) { PORT->Group[BOARD_LED_RED_PORT].OUTSET.reg = (1<<BOARD_LED_RED_PIN); }
inline void LED_RED_toggle(void) { PORT->Group[BOARD_LED_RED_PORT].OUTTGL.reg = (1<<BOARD_LED_RED_PIN); }
inline void LED_RED_release(void) { PORT->Group[BOARD_LED_RED_PORT].DIRCLR.reg = (1<<BOARD_LED_RED_PIN); }

inline void LED_GREEN_init(void) { PORT->Group[BOARD_LED_GREEN_PORT].DIRSET.reg = (1<<BOARD_LED_GREEN_PIN); }
inline void LED_GREEN_on(void) { PORT->Group[BOARD_LED_GREEN_PORT].OUTCLR.reg = (1<<BOARD_LED_GREEN_PIN); }
inline void LED_GREEN_off(void) { PORT->Group[BOARD_LED_GREEN_PORT].OUTSET.reg = (1<<BOARD_LED_GREEN_PIN); }
inline void LED_GREEN_toggle(void) { PORT->Group[BOARD_LED_GREEN_PORT].OUTTGL.reg = (1<<BOARD_LED_GREEN_PIN); }
inline void LED_GREEN_release(void) { PORT->Group[BOARD_LED_GREEN_PORT].DIRCLR.reg = (1<<BOARD_LED_GREEN_PIN); }

inline void LED_BLUE_init(void) { PORT->Group[BOARD_LED_BLUE_PORT].DIRSET.reg = (1<<BOARD_LED_BLUE_PIN); }
inline void LED_BLUE_on(void) { PORT->Group[BOARD_LED_BLUE_PORT].OUTCLR.reg = (1<<BOARD_LED_BLUE_PIN); }
inline void LED_BLUE_off(void) { PORT->Group[BOARD_LED_BLUE_PORT].OUTSET.reg = (1<<BOARD_LED_BLUE_PIN); }
inline void LED_BLUE_toggle(void) { PORT->Group[BOARD_LED_BLUE_PORT].OUTTGL.reg = (1<<BOARD_LED_BLUE_PIN); }
inline void LED_BLUE_release(void) { PORT->Group[BOARD_LED_BLUE_PORT].DIRCLR.reg = (1<<BOARD_LED_BLUE_PIN); }

//void LED_pulse();

#endif // _BOARD_DRIVER_LED_
