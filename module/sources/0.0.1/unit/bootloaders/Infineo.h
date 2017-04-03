/** \file
 *
 *  Header file for BootloaderCDC.c.
 */

#ifndef _CDC_H_
#define _CDC_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/boot.h>
		#include <avr/eeprom.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>
	/* Macros: */
		/** Version major of the CDC bootloader. */
		#define BOOTLOADER_VERSION_MAJOR     0x01

		/** Version minor of the CDC bootloader. */
		#define BOOTLOADER_VERSION_MINOR     0x00

		/** Hardware version major of the CDC bootloader. */
		#define BOOTLOADER_HWVERSION_MAJOR   0x01

		/** Hardware version minor of the CDC bootloader. */
		#define BOOTLOADER_HWVERSION_MINOR   0x00

		/** Eight character bootloader firmware identifier reported to the host when requested */
		#define SOFTWARE_IDENTIFIER          "INFINEO"
		
		#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
		#define LED_SETUP()		DDRC |= (1<<7); DDRB |= (1<<0); DDRD |= (1<<5);
		#define L_LED_OFF()		PORTC &= ~(1<<7)
		#define L_LED_ON()		PORTC |= (1<<7)
		#define L_LED_TOGGLE()	PORTC ^= (1<<7)
		#if DEVICE_PID == 0x0037	// polarity of the RX and TX LEDs is reversed on the Micro
			#define TX_LED_OFF()	PORTD &= ~(1<<5)
			#define TX_LED_ON()		PORTD |= (1<<5)
			#define RX_LED_OFF()	PORTB &= ~(1<<0)
			#define RX_LED_ON()		PORTB |= (1<<0)			
		#else 
			#define TX_LED_OFF()	PORTD |= (1<<5)
			#define TX_LED_ON()		PORTD &= ~(1<<5)
			#define RX_LED_OFF()	PORTB |= (1<<0)
			#define RX_LED_ON()		PORTB &= ~(1<<0)
		#endif

	/* Type Defines: */
		/** Type define for a non-returning pointer to the start of the loaded application in flash memory. */
		typedef void (*AppPtr_t)(void) ATTR_NO_RETURN;

	/* Function Prototypes: */
		void StartSketch(void);
		void LEDPulse(void);
	
		void CDC_Task(void);
		void SetupHardware(void);

		void EVENT_USB_Device_ConfigurationChanged(void);

		#if defined(INCLUDE_FROM_INFINEO_C) || defined(__DOXYGEN__)
			#if !defined(NO_BLOCK_SUPPORT)
			static void    ReadWriteMemoryBlock(const uint8_t Command);
			#endif
			static uint8_t FetchNextCommandByte(void);
			static void    WriteNextResponseByte(const uint8_t Response);
		#endif

#endif