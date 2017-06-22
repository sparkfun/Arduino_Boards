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

// REMOVED:
// Extended capabilities
// USART mode
// Interactive mode

#include "sam.h"
#include <string.h>
#include "sam_ba_monitor.h"
#include "board_driver_usb.h"
#include "sam_ba_usb.h"
#include "sam_ba_cdc.h"
#include "board_driver_led.h"
#include "board_definitions.h"

const char RomBOOT_Version[] = SAM_BA_VERSION;

uint32_t current_number;
uint32_t i, length;
uint8_t command, *ptr_data, *ptr, data[SIZEBUFMAX];
uint8_t j;
uint32_t u32tmp;
uint32_t PAGE_SIZE, PAGES, MAX_FLASH;

typedef struct
{
  /* send one byte of data */
  int (*put_c)(int value);
  /* Get one byte */
  int (*get_c)(void);
  /* Receive buffer not empty */
  bool (*is_rx_ready)(void);
  /* Send given data (polling) */
  uint32_t (*putdata)(void const* data, uint32_t length);
  /* Get data from comm. device */
  uint32_t (*getdata)(void* data, uint32_t length);
  /* Send given data (polling) using xmodem (if necessary) */
  uint32_t (*putdata_xmd)(void const* data, uint32_t length);
  /* Get data from comm. device using xmodem (if necessary) */
  uint32_t (*getdata_xmd)(void* data, uint32_t length);
} t_monitor_if;

const t_monitor_if usbcdc_if =
{
  .put_c =         cdc_putc,
  .get_c =         cdc_getc,
  .is_rx_ready =   cdc_is_rx_ready,
  .putdata =       cdc_write_buf,
  .getdata =       cdc_read_buf,
  .putdata_xmd =   cdc_write_buf,
  .getdata_xmd =   cdc_read_buf_xmd
};

/* The pointer to the interface object use by the monitor */
t_monitor_if * ptr_monitor_if;

void sam_ba_monitor_init()
{
	ptr_monitor_if = (t_monitor_if*) &usbcdc_if;
	ptr_data = NULL;
	command = 'z';
}

/*
 * Central SAM-BA monitor putdata function
 */
static uint32_t sam_ba_putdata(t_monitor_if* pInterface, void const* data, uint32_t length)
{
	uint32_t result ;

	result=pInterface->putdata(data, length);

	if (result)
	{
		LED_RED_toggle();
	}

	return result;
}

/*
 * Central SAM-BA monitor getdata function
 */
static uint32_t sam_ba_getdata(t_monitor_if* pInterface, void* data, uint32_t length)
{
	uint32_t result ;

	result=pInterface->getdata(data, length);

	if (result)
	{
		LED_GREEN_toggle();
	}

	return result;
}

/*
 * Central SAM-BA monitor putdata function using
 */
static uint32_t sam_ba_putdata_xmd(t_monitor_if* pInterface, void const* data, uint32_t length)
{
	uint32_t result ;

	result=pInterface->putdata_xmd(data, length);

	if (result)
	{
		LED_RED_toggle();
	}

	return result;
}

/*
 * Central SAM-BA monitor getdata function
 */
static uint32_t sam_ba_getdata_xmd(t_monitor_if* pInterface, void* data, uint32_t length)
{
	uint32_t result ;

	result=pInterface->getdata_xmd(data, length);

	if (result)
	{
		LED_GREEN_toggle();
	}

	return result;
}

/**
 * \brief This function allows data emission by USART
 *
 * \param *data  Data pointer
 * \param length Length of the data
 */
void sam_ba_putdata_term(uint8_t* data, uint32_t length)
{
	sam_ba_putdata(ptr_monitor_if, data, length);
	return;
}

volatile uint32_t sp;

void call_applet(uint32_t address)
{
  uint32_t app_start_address;

	LED_RED_off();
	LED_GREEN_off();
	LED_BLUE_off();

  __disable_irq();

  sp = __get_MSP();

  /* Rebase the Stack Pointer */
  __set_MSP(*(uint32_t *) address);

  /* Load the Reset Handler address of the application */
  app_start_address = *(uint32_t *)(address + 4);

  /* Jump to application Reset Handler in the application */
  asm("bx %0"::"r"(app_start_address));
}

static void sam_ba_monitor_loop(void)
{
  length = sam_ba_getdata(ptr_monitor_if, data, SIZEBUFMAX);
  ptr = data;

  for (i = 0; i < length; i++, ptr++)
  {
    if (*ptr == 0xff) continue;

    if (*ptr == '#')
    {
      if (command == 'S') // send data to device
      {
        //Check if some data are remaining in the "data" buffer
        if(length>i)
        {
          //Move current indexes to next avail data (currently ptr points to "#")
          ptr++;
          i++;

          //We need to add first the remaining data of the current buffer already read from usb
          //read a maximum of "current_number" bytes
          if ((length-i) < current_number)
          {
            u32tmp=(length-i);
          }
          else
          {
            u32tmp=current_number;
          }

          memcpy(ptr_data, ptr, u32tmp);
          i += u32tmp;
          ptr += u32tmp;
          j = u32tmp;
        }
        //update i with the data read from the buffer
        i--;
        ptr--;
        //Do we expect more data ?
        if(j<current_number)
          sam_ba_getdata_xmd(ptr_monitor_if, ptr_data, current_number-j);

        __asm("nop");
      }
      else if (command == 'R') // read data from device
      {
        sam_ba_putdata_xmd(ptr_monitor_if, ptr_data, current_number);
      }
      else if (command == 'O') // write octet
      {
        *ptr_data = (char) current_number;
      }
      else if (command == 'H') // write halfword
      {
        *((uint16_t *) ptr_data) = (uint16_t) current_number;
      }
      else if (command == 'W') // write word
      {
        *((int *) ptr_data) = current_number;
      }
      else if (command == 'o') // read octet
      {
        sam_ba_putdata_term(ptr_data, 1);
      }
      else if (command == 'h') // read halfword
      {
        current_number = *((uint16_t *) ptr_data);
        sam_ba_putdata_term((uint8_t*) &current_number, 2);
      }
      else if (command == 'w') // read word
      {
        current_number = *((uint32_t *) ptr_data);
        sam_ba_putdata_term((uint8_t*) &current_number, 4);
      }
      else if (command == 'G') // run code
      {
        call_applet(current_number);
        /* Rebase the Stack Pointer */
        __set_MSP(sp);
        __enable_irq();
      }
      else if (command == 'V') // report version string
      {
//      sam_ba_putdata( ptr_monitor_if, "v", 1);
		
        sam_ba_putdata( ptr_monitor_if, (uint8_t *) RomBOOT_Version, SAM_BA_VERSION_STRLEN);
        sam_ba_putdata( ptr_monitor_if, " ", 1);
        ptr = (uint8_t*) &(__DATE__);
        i = 0;
        while (*ptr++ != '\0')
          i++;
        sam_ba_putdata( ptr_monitor_if, (uint8_t *) &(__DATE__), i);
        sam_ba_putdata( ptr_monitor_if, " ", 1);
        i = 0;
        ptr = (uint8_t*) &(__TIME__);
        while (*ptr++ != '\0')
          i++;
        sam_ba_putdata( ptr_monitor_if, (uint8_t *) &(__TIME__), i);
        sam_ba_putdata( ptr_monitor_if, "\n\r", 2);
      }
      command = 'z';
      current_number = 0;
    }
    else
    {
      if (('0' <= *ptr) && (*ptr <= '9'))
      {
        current_number = (current_number << 4) | (*ptr - '0');
      }
      else if (('A' <= *ptr) && (*ptr <= 'F'))
      {
        current_number = (current_number << 4) | (*ptr - 'A' + 0xa);
      }
      else if (('a' <= *ptr) && (*ptr <= 'f'))
      {
        current_number = (current_number << 4) | (*ptr - 'a' + 0xa);
      }
      else if (*ptr == ',')
      {
        ptr_data = (uint8_t *) current_number;
        current_number = 0;
      }
      else
      {
        command = *ptr;
        current_number = 0;
      }
    }
  }
}

/**
 * \brief This function starts the SAM-BA monitor.
 */

void sam_ba_monitor_run(void)
{

//	while (1)
//	{
		sam_ba_monitor_loop();
//	}
}
