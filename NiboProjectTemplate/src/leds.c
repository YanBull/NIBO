/*
 ============================================================================
 Name        : leds.c
 Author      : Yan
 Version     : 11.12.2020
 Description : Sensoren und LEDs
 ============================================================================
 */

#include "the_header.h"
//#include "main.c"

/**
 * Jede Ausfuehrung wechselt die Farbe der LEDS
 */
void musicLed() {
	static char counter; /**< Zaehlt, welche Farbe naechste ist*/

	switch (counter) {
	case 0:
		switchAll(LEDS_RED);
		leds_set_displaylight(0);
		break;
	case 1:
		switchAll(LEDS_ORANGE);
		break;
	case 2:
		switchAll(LEDS_GREEN);
		leds_set_displaylight(1024);
		break;
	case 3:
		switchAll(LEDS_ORANGE);
		break;
	}

	counter++;
	counter %= 4;
}

/**
 * alle LEDS einschalten
 */
void switchAll(int color) {
	for (int i = 0; i < 8; i++) {
		leds_set_status(color, i);
	}
}

/**
 * Laut der Informationen der Sensors werden LED blinken
 * Auch wirden die Werte der hindernisserkennung-Variablen geaendert
 */
void sensorLed() {
	//LED 7, Sensor 0
	if (copro_distance[0] / 256 > 100) { //48
		leds_set_status(LEDS_RED, 7);
		d_sens[4] = 2;
	} else if (copro_distance[0] / 256 > 25) {//17
		leds_set_status(LEDS_ORANGE, 7);
		d_sens[4] = 1;
	} else {
		leds_set_status(LEDS_GREEN, 7);
		d_sens[4] = 0;
	}

	//LED 6, Sensor 1
	if (copro_distance[1] / 256 > 100) {//65
		leds_set_status(LEDS_RED, 6);
		d_sens[3] = 2;
	} else if (copro_distance[1] / 256 > 25) {//17
		leds_set_status(LEDS_ORANGE, 6);
		d_sens[3] = 1;
	} else {
		leds_set_status(LEDS_GREEN, 6);
		d_sens[3] = 0;
	}

	//LED 5,4, Sensor 2
	if (copro_distance[2] / 256 > 100 || nds3_get_dist() < 8) {//40
		leds_set_status(LEDS_RED, 5);
		leds_set_status(LEDS_RED, 4);
		d_sens[2] = 2;
	} else if (copro_distance[2] / 256 > 25) { //6
		leds_set_status(LEDS_ORANGE, 5);
		leds_set_status(LEDS_ORANGE, 4);
		d_sens[2] = 1;
	} else {
		leds_set_status(LEDS_GREEN, 5);
		leds_set_status(LEDS_GREEN, 4);
		d_sens[2] = 0;
	}

	//LED 3, Sensor 3
	if (copro_distance[3] / 256 > 100) {//103
		leds_set_status(LEDS_RED, 3);
		d_sens[1] = 2;
	} else if (copro_distance[3] / 256 > 25) {//36
		leds_set_status(LEDS_ORANGE, 3);
		d_sens[1] = 1;
	} else {
		leds_set_status(LEDS_GREEN, 3);
		d_sens[1] = 0;
	}

	//LED 2, Sensor 4
	if (copro_distance[4] / 256 > 100) {//67
		leds_set_status(LEDS_RED, 2);
		d_sens[0] = 2;
	} else if (copro_distance[4] / 256 > 25) {//26
		leds_set_status(LEDS_ORANGE, 2);
		d_sens[0] = 1;
	} else {
		leds_set_status(LEDS_GREEN, 2);
		d_sens[0] = 0;
	}
}
