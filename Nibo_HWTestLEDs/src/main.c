/*
 * main.c
 *
 * program for verifying the led functions
 *
 *  Created on: 28.05.2011
 *      Author: Daniel Wittekind
 */

#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/delay.h>
#include <nibo/display.h>
#include <nibo/gfx.h>
#include <nibo/leds.h>
#include <nibo/pwm.h>
#include <nibo/copro.h>
#include <nibo/bot.h>
#include <nibo/nds3.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>

#include "switchS3.h"

#define LEDS_AMOUNT 8
#define LEDS_STATES 4

// keeps track of the currently active led
int led = 0;

// state variable for non-status led actions
int alt_mode = 0;

//
int leds_status[LEDS_AMOUNT] = { 0 };

/**
 * print activities
 */
void print_activities() {
	// clear screen
	gfx_fill(0);

	// show general description
	gfx_move(48, 8);
	gfx_print_text("LED Test");
	gfx_move(8, 16);
	gfx_print_text("press S3 to continue");

	// define counter variable
	int i = 0;
	// define color discription character
	char led_color[1] = " ";

	// loop through led numbers
	for (i = 0; i < LEDS_AMOUNT; i++) {

		// switch status and assign text
		switch (leds_status[i]) {
		case 0:
			sprintf(led_color, "x");
			break;
		case 1:
			sprintf(led_color, "g");
			break;
		case 2:
			sprintf(led_color, "r");
			break;
		case 3:
			sprintf(led_color, "o");
			break;
		}

		// switch led and place cursor in correct spot
		switch (i) {
		case 0:
			gfx_move(0, 0);
			break;
		case 1:
			gfx_move(120, 0);
			break;
		case 2:
			gfx_move(120, 40);
			break;
		case 3:
			gfx_move(104, 48);
			break;
		case 4:
			gfx_move(88, 56);
			break;
		case 5:
			gfx_move(32, 56);
			break;
		case 6:
			gfx_move(16, 48);
			break;
		case 7:
			gfx_move(0, 40);
			break;
		}
		gfx_print_text(led_color);
	}

	if (alt_mode == 1) {
		gfx_move(48, 48);
		gfx_print_text("w");
		gfx_move(72, 48);
		gfx_print_text("w");
	} else {
		gfx_move(48, 48);
		gfx_print_text("x");
		gfx_move(72, 48);
		gfx_print_text("x");
	}

}

int main() {
	// enable interrupts
	sei();

	bot_init();
	pwm_init();
	leds_init();
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	print_activities();

	while (1) {
		// current led state - 0 = off, 1 = green, 2 = red, 3 = orange (mixed green & red)
		int state = leds_status[led];

		// if switch 3 has been pressed
		if (s3_was_pressed()) {

			// increase state up to possible amount of states
			if ((state < LEDS_STATES - 1) && (alt_mode == 0))
				state++;
			// reset to zero after all states have been completed
			else {
				state = 0;

				// turn off current led before advancing
				leds_set_status(state, led);
				leds_status[led] = state;

				// at reset of state, increase current led counter up to possible amount of leds
				if (led < LEDS_AMOUNT - 1) {
					led++;
				}
				// otherwise reset to zero, start from beginning
				else {
					int i = 0;
					switch (alt_mode) {
					case 0:
						alt_mode++;
						leds_set_headlights(1023);
						break;
					case 1:
						alt_mode++;
						leds_set_headlights(0);
						break;
					case 2:
						alt_mode++;
						state = 3;
						for (i = 0; i < LEDS_AMOUNT; i++) {
							leds_status[i] = state;
							leds_set_status(state, i);
						}
						leds_set_status_intensity(128);
						break;
					case 3:
						alt_mode++;
						state = 3;
						for (i = 0; i < LEDS_AMOUNT; i++) {
							leds_status[i] = state;
							leds_set_status(state, i);
						}
						leds_set_status_intensity(384);
						break;
					case 4:
						alt_mode++;
						state = 3;
						for (i = 0; i < LEDS_AMOUNT; i++) {
							leds_status[i] = state;
							leds_set_status(state, i);
						}
						leds_set_status_intensity(768);
						break;
					case 5:
						alt_mode++;
						state = 0;
						for (i = 0; i < LEDS_AMOUNT; i++) {
							leds_status[i] = state;
							leds_set_status(state, i);
						}
						leds_set_status_intensity(1023);
						break;
					case 6:
						alt_mode++;
						leds_set_displaylight(512);
						break;
					case 7:
						alt_mode = 0;
						leds_set_displaylight(0);
						led = 0;
						break;
					}
				}
			}

			// update status table
			leds_status[led] = state;

			// set led
			leds_set_status(state, led);

			// print screen info
			print_activities();
		}
	}

	return 0;

}

