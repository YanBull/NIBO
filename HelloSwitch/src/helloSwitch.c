/*
 ============================================================================
 Name        : helloSwitch.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Zeigt den Einsatz des Schalters S3 auf dem Nibo
 ============================================================================
 */

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>

// Bibliothek fuer Wartefunktionen
#include <nibo/delay.h>

// Bibliothek fuer das Ansteuern der Status LEDs
#include <nibo/leds.h>

//Funktionen zur Statusabfrage des Schalters
#include "n2switchS3.h"


// Hauptfunktion
int main() {

	// Initialisierungen
	bot_init();
	leds_init();

	// Statusvariable
	int state = 0;

	// Endlosschleife
	while(1==1){

		// Schalter wurde gedrueckt
		if (s3_was_pressed()){
			if(state == 0){
				// Status aendern
				state = 1;

				// LED einschalten
				leds_set_status(LEDS_GREEN, 4);

			}

			else{
				// Status aendern
				state = 0;

				// LED wieder ausschalten
				leds_set_status(LEDS_OFF, 4);
			}
		}

	}
}
