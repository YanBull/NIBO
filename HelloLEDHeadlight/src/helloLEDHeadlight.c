/*
 ============================================================================
 Name        : helloLEDHeadLight.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Frontscheinwerfer Demo fuer den Nibo2
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

/*
 * Bibliothek fuer Pulsweitenmodulation (PWM)
 * Emuliert analoge Stroeme an digitalen Ausgaengen.
 */
#include <nibo/pwm.h>

/*
 * Um die PWM zu ermoeglichen, muessen Interrupts aktiviert werden.
 * Ueber avr/interrupt.h werden Interrupts eingebunden
 */
#include <avr/interrupt.h>

// Hauptfunktion
int main(){

	/*
	 * Initialisierungsfunktionen
	 * Aktivieren die jeweiligen Funktionen der Hardware des Nibo2
	 */

	// Einschalten der Interrupts. Noetig fuer die PWM
	sei();

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// Initialisierung der LEDs
	leds_init();

	// Initialisierung der Pulsweitenmodulation
	pwm_init();

	// Endlosschleife, laeuft immer wieder durch
	while(1==1){

		/*
		 * Schaltet die beiden Frontscheinwerfer ein.
		 * Der uebergebene Parameter bestimmt die Helligkeit.
		 * 0 = aus, 1024 = maximale Helligkeit
		 */
		leds_set_headlights(1024);

		// eine halbe Sekunde warten
		delay_ms(500);

		// Helligkeit herabsetzen
		leds_set_headlights(768);

		// Helligkeit alle halbe Sekunde weiter herabsetzen
		delay(500);
		leds_set_headlights(640);
		delay(500);
		leds_set_headlights(512);
		delay(500);
		leds_set_headlights(384);
		delay(500);
		leds_set_headlights(256);
		delay(500);
		leds_set_headlights(128);
		delay(500);
		leds_set_headlights(64);
		delay(500);
		leds_set_headlights(32);
		delay(500);

		// Frontscheinwerfer ausschalten
		leds_set_headlights(0);

		// 3 Sekunden warten
		delay(3000);

	}
}
