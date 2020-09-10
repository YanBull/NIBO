/*
 ============================================================================
 Name        : helloNDS3.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Demo zur Benutzung der NDS3-Distanzsensors des Nibo2
 ============================================================================
 */

// standard Nibo2 includes
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>

// display functions
#include <nibo/display.h>

// graphics library
#include <nibo/gfx.h>

// I**2C interface function
#include <nibo/i2cmaster.h>

// NDS3 library
#include <nibo/nds3.h>

// delay
#include <nibo/delay.h>

// microcontroller hardware interrupts
#include <avr/interrupt.h>

// input - output funtions
#include <stdio.h>

int main() {

	// enable interrupts
	sei();

	// initialize robot (always)
	bot_init();

	// initialize i2c for communication with nds3
	i2c_init();

	// initialize display and graphic functions
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	// text
	char text[20] = "";

	// move NDS3 sensor, value in degrees
	nds3_move(180);

	// return distance in cm
	uint8_t distance = nds3_get_dist();

	// create output
	sprintf(text, "Distanz: %3i", (int) distance);
	gfx_move(0, 0);
	gfx_print_text(text);

	delay(2000);

	nds3_move(90);

	while (1 == 1) {

		uint8_t distance = nds3_get_dist();

		sprintf(text, "Distanz: %3i", (int) distance);
		gfx_fill(0);
		gfx_move(0, 0);
		gfx_print_text(text);

		delay(100);
	}

}

