/*
 * ride.c
 *
 *  Created on: Nov 9, 2020
 *      Author: defaultuser
 */


#include "the_header.h"
//#include "main.c"

/**
 *Der Roboter Faengt an, nach forne zu fahren
 *Falls noetig ist, faehrt er rechts links oder auch zurueck
 */
void ride() {
	copro_update();
	sensorLed();
	deadLock();

	if (!backRide) {

		//Backlights aus
		leds_set_status(LEDS_OFF, 0);
		leds_set_status(LEDS_OFF, 1);

		// Kein Hindernis
		if ((d_sens[4] + d_sens[3] + d_sens[2] + d_sens[1] + d_sens[0]) == 0) {
			copro_setSpeed(_SPEED, _SPEED);
		}

		// in die Ecke gefahren
		else if (d_sens[0] + d_sens[1] >= 2 && d_sens[3] + d_sens[4] >= 2) {
			backRide = 1;
		}

		//Hindernis recht
		else if ((d_sens[4] + d_sens[3]) > (d_sens[1] + d_sens[0])) {
			//Ob der Sensor rot ist- dann zurueckfahren
			if (d_sens[3] == 2) {
				turnAround();
			}
			//Ob der Sensor orange ist - rihtMOve
			else {
				leftMove();
			}
		}

		//Hindernis links
		else if ((d_sens[4] + d_sens[3]) < (d_sens[1] + d_sens[0])) {
			//Ob der Sensor rot ist- dann zurueckfahren
			if (d_sens[1] == 2) {
				turnAround();
			}
			//Ob der Sensor orange ist - rihtMOve
			else {
				rightMove();
			}
		}
		// Nur der Zentraler sensor was bemerkt
		else if ((d_sens[4] + d_sens[3] + d_sens[1] + d_sens[0]) == 0
				&& d_sens[2] > 0) {
			//Orange - Verinderung der Geschwingischkeit
			if (d_sens[2] == 1) {
				copro_setSpeed(_SPEED / 2, _SPEED / 2);
			}
			//Red - MOve back
			else {
				backRide = 1;
			}
		}
	} else {

		//Backlights ein
		leds_set_status(LEDS_RED, 0);
		leds_set_status(LEDS_RED, 1);

		//zurueck, bis alle LEDS gruen werden
		if ((d_sens[4] + d_sens[3] + d_sens[2] + d_sens[1] + d_sens[0]) != 0) {
			turnAround();
		} else {
			backRide = 0;
		}
	}
}

/**
 * links fahren
 */
void leftMove() {
	copro_setSpeed(0, _SPEED / 2);
	lastTurn = 'l';
}

/**
 * rechts fahren
 */
void rightMove() {
	copro_setSpeed(_SPEED / 2, 0);
	lastTurn = 'r';
}

/**
 * Zurueck bzw. links- oder rechtszurueck fahren
 */
void turnAround() {
	if (lastTurn == 'r') {
		copro_setSpeed(-_SPEED / 2, _SPEED / 2);
	} else {
		copro_setSpeed(_SPEED / 2, -_SPEED / 2);
	}
}

/**
 * Funktion prueft ob NIbo in einem blockierten Zustand ist.
 * (die Sensoren lange gleiche Infos liefern)
 * Dann muss Nibo zuruckfahren
 */
void deadLock() {
	static int dl_val; /**< value of checksum for deadLock()*/
	static unsigned int dl_timer; /**< amount of times in deadLock()*/

	int sum = (d_sens[0] + d_sens[1] + d_sens[2] + d_sens[3] + d_sens[4]);

	if (sum != 0 && sum == dl_val) {
		dl_timer++;
	} else if (sum != 0) {
		dl_timer = 1;
		dl_val = sum;
	}

	if (dl_timer > 150) {
		backRide = 1;
		dl_timer = 0;
	}
}
