/*
 ============================================================================
 Name        : helloVoltage.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Anzeige der Batteriespannung auf dem Nibo
 ============================================================================
 */

// Standard Includes fuer das Funktionieren des Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>

// Bibliothek zum Ansteuern des Display
#include <nibo/display.h>

// Bibliothek mit Grafikfunktionen
#include <nibo/gfx.h>

// Wartefunktionen
#include <nibo/delay.h>

// Ein- und Ausgabefunktionen
#include <stdio.h>

int main() {

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// initialisiert das Display und die Grafikfunktionen
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	// speichert die aktuelle Batteriespannung
	double volt = 0;
	int voltInt = 0;
	int voltFract = 0;

	// Ausgabetext
	char output[20] = "";

	// Endlosschleife
	while(1==1){

		// Fuellt das Display mit der uebergebenen Bitmaske. Leert es in diesem Fall.
		gfx_fill(0);

		// aktualisiert den Wert fuer bot_supply
		bot_update();

		/*
		 * Berechnung der Versorgungsspannung
		 * bot_supply enthaelt den Rohdatenwert des Analog-Digital Komperators
		 */
		volt = 0.0166 * bot_supply - 1.19;
		voltInt = (int)volt;
		voltFract = (int)((volt - (double)voltInt) * 100);

		// Wert in Ausgabetext speichern
		sprintf(output, "Spannung: %i.%i V", voltInt, voltFract);

		gfx_move(0,0);

		// Auf Display ausgeben
		gfx_print_text(output);

		// 6s warten
		delay(2000);
	}
}

