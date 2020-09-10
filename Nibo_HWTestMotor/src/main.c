/*
 * main.c
 *
 * program for verifying the motor functions
 *
 *  Created on: 28.05.2011
 *      Author: Daniel Wittekind
 */

#include <nibo/niboconfig.h>
#include <nibo/display.h>
#include <nibo/gfx.h>
#include <nibo/copro.h>
#include <nibo/delay.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>
#include <nibo/spi.h>

#include <avr/interrupt.h>
#include <stdio.h>

#include "switchS3.h"

/**
 * updated bei jedem Aufruf die Tickanzeige
 */
void update_data() {

	copro_update();

	char text[20];

	//Ausgabe Symbol rechts
	gfx_move(0, 38);
	sprintf(text, "R");
	gfx_print_text(text);

	//Ausgabe Symbol links
	gfx_move(116, 38);
	sprintf(text, "L");
	gfx_print_text(text);

	//Ausgabe ticks rechts
	gfx_move(0, 47);
	sprintf(text, "%i", copro_ticks_r);
	gfx_print_text(text);

	//Ausgabe Beschreibung ticks
	gfx_move(48, 47);
	sprintf(text, "ticks");
	gfx_print_text(text);

	//Ausgabe ticks links
	gfx_move(108, 47);
	sprintf(text, "%i", copro_ticks_l);
	gfx_print_text(text);

	//Ausgabe ticks rechts
	gfx_move(0, 56);
	sprintf(text, "%i", copro_speed_r);
	gfx_print_text(text);

	//Ausgabe Beschreibung ticks
	gfx_move(48, 56);
	sprintf(text, "speed");
	gfx_print_text(text);

	//Ausgabe ticks links
	gfx_move(108, 56);
	sprintf(text, "%i", copro_speed_l);
	gfx_print_text(text);
}

/**
 * print activities
 */
void print_activities(char text1[], char text2[]) {
	//Info Screen zeichnen
	gfx_term_clear(0);
	gfx_move(0, 0);
	gfx_print_text("Now: ");
	gfx_move(0, 8);
	gfx_print_text(text1);
	gfx_move(0, 16);
	gfx_print_text("Next: ");
	gfx_move(0, 24);
	gfx_print_text(text2);

}

/**
 * Geschwindigkeit setzen links vorwaerts
 */
void setSpeed_left_forward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(30,0)", "setSpeed(-30,0)");

	copro_setSpeed(30, 0);
}

/**
 * Geschwindigkeit setzen links rueckwaerts
 */
void setSpeed_left_backward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(-30,0)", "setSpeed(0,30)");

	copro_setSpeed(-30, 0);
}

/**
 * Geschwindigkeit setzen links vorwaerts
 */
void setSpeed_right_forward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(0,30)", "setSpeed(0,-30)");

	copro_setSpeed(0, 30);
}

/**
 * Geschwindigkeit setzen links rueckwaerts
 */
void setSpeed_right_backward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(0,-30)", "setTargetRel(290,290,29)");

	copro_setSpeed(0, -30);
}

/**
 * relatives Ziel, 1m vorwaerts
 */
void setTargetRel_forward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setTargetRel(290,290,29)", "setTargetRel(-290,-290,29)");

	copro_setTargetRel(290,290,29);
}

/**
 * relatives Ziel, 1m rueckwaerts
 */
void setTargetRel_backward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setTargetRel(-290,-290,29)", "Pause");

	copro_setTargetRel(-290,-290,29);
}

/**
 * Unterbrechung zum Nichtstun
 */
void do_nothing(){
	copro_stop();
	copro_resetOdometry(0, 0);
}

int main() {

	sei();
	bot_init();
	spi_init();
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	int mode = 0;

	gfx_fill(0);
	gfx_move(0, 0);
	gfx_print_text("Motor Test");
	gfx_move(0, 8);
	gfx_print_text("Next: setSpeed(0,30)");

	while (1 == 1) {
		if (s3_was_pressed()) {

			mode++;

			switch (mode) {
			case 1:
				// Geschwindigkeit links vorwaerts
				setSpeed_left_forward();
				break;
			case 2:
				// Geschwindigkeit links rueckwaerts
				setSpeed_left_backward();
				break;
			case 3:
				// Geschwindigkeit rechts vorwaerts
				setSpeed_right_forward();
				break;
			case 4:
				// Geschwindigkeit rechts vorwaerts
				setSpeed_right_backward();
				break;
			case 5:
				// Ziel vorwaerts
				setTargetRel_forward();
				break;
			case 6:
				// Ziel rueckwaerts
				setTargetRel_backward();
				break;
			case 7:
				// Pause
				do_nothing();
				gfx_fill(0);
				gfx_move(0, 0);
				gfx_print_text("Motor Test");
				gfx_move(0, 8);
				gfx_print_text("Next: setSpeed(0,30)");
				mode = 0;
				break;
			}
		}
		update_data();
	}

	return 0;

}

