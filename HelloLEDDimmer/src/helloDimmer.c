/*
 ============================================================================
 Name        : helloDimmer.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Dimmen von Status LEDs und Display fuer den Nibo2
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
 * ueber avr/interrupt.h werden Interrupts eingebunden
 */
#include <avr/interrupt.h>

// Hauptfunktion
int main() {

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
	while (1 == 1) {

		// zaehlt von 0 bis 7
		for (int i = 0; i < 8; i++) {

			// LED mit Index i auf gruen setzen
			leds_set_status(LEDS_GREEN, i);
		}

		// 2 Sekunden warten
		delay(2000);

		/*
		 * veraendert die Helligkeit aller Status LEDs (einzelne Helligkeit nicht aenderbar)
		 * Parameter bestimmt Helligkeit. 0 = aus, 1024 = maximal
		 */
		leds_set_status_intensity(128);

		delay(2000);

		/*
		 * schaltet die Hintergrundbeleuchtung des Displays ein
		 * 0 = aus, 1024 = maximal
		 */
		leds_set_displaylight(1024);

		delay(2000);

		leds_set_displaylight(512);

		delay(4000);

	}
}
