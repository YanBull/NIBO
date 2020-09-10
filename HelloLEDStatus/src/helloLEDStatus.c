/*
 ============================================================================
 Name        : helloLEDStatus.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Status LED Demo fuer den Nibo2
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

// Hauptfunktion
int main(){

	/*
	 * Initialisierungsfunktionen
	 * Aktivieren die jeweiligen Funktionen der Hardware des Nibo2
	 */
	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// Initialisierung der LEDs
	leds_init();

	// Endlosschleife, laeuft immer wieder durch
	while(1==1){
		/*
		 * LED Nummer 4 auf gruen setzen
		 *
		 * fuer den Aufruf leds_set_status werden zwei Parameter benoetigt
		 * leds_set_status(uint8_t color, uint8_t led);
		 * color bestimmt ueber die gewuenschte Farbe und led bestimmt, welche LED geschaltet wird
		 */
		leds_set_status(LEDS_GREEN, 4);

		// LED 5 auf rot setzen
		leds_set_status(LEDS_RED, 5);

		// LED 6 auf orange setzen
		leds_set_status(LEDS_ORANGE, 6);

		// 2 Sekunden warten
		delay(2000);

		/*
		 * Angeschaltete LEDs wieder ausschalten
		 */
		leds_set_status(LEDS_OFF, 4);
		leds_set_status(LEDS_OFF, 5);
		leds_set_status(LEDS_OFF, 6);

		delay(2000);

	}
}
