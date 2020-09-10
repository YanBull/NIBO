/*
 ============================================================================
 Name        : helloFloor.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Auslesen der Bodensensoren des Nibo2
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

// Bibliothek fuer Bodensensoren
#include <nibo/floor.h>

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

	// initialisiert die Bodensensorfunktionen
	floor_init();

	// Variable fuer Ausgabetext
	char output[10] = "";

	// speichert die Sensorwerte
	unsigned int current_floor = 0;

	// Display leeren
	gfx_fill(0);

	// Endlosschleife
	while (1 == 1) {

		// fragt die aktuellen Werte der Bodensensoren ab
		floor_update();

		gfx_move(0, 36);

		// beschreibende Ausgabe
		gfx_print_text("Front");
		gfx_move(0, 45);

		/*
		 * Das Array floor_relative[] enthaelt die relativen Sensorwerte der Bodensensoren.
		 * Dabei handelt es sich um einen Differenzwert, bei dem das Umgebungslicht
		 * beruecksichtigt wird. Die IR-Dioden der Sensoren werden dabei abwechselnd an und
		 * ausgeschaltet, um einen Vergleichswert mit dem Umgebungslicht zu ermitteln.
		 *
		 * Abfrage des Wertes fuer den Sensor vorne rechts
		 */
		current_floor = floor_relative[FLOOR_RIGHT];

		// Ausgabe
		sprintf(output, "rel R %4u ", current_floor);
		gfx_print_text(output);

		// linken Sensor vorn abfragen
		current_floor = floor_relative[FLOOR_LEFT];

		sprintf(output, "rel L %4u ", current_floor);
		gfx_move(64, 45);
		gfx_print_text(output);

		/*
		 * floor_absolute[]	enthaelt die rohen Sensorwerte
		 *
		 * Abfrage des Sensors vorne rechts
		 */
		current_floor = floor_absolute[FLOOR_RIGHT];

		// Ausgabe
		sprintf(output, "abs R %4u ", current_floor);
		gfx_move(0, 54);
		gfx_print_text(output);

		// linken Sensor vorn abfragen
		current_floor = floor_absolute[FLOOR_LEFT];
		gfx_move(64, 54);
		gfx_print_text(output);

		// beschreibende Ausgabe
		gfx_move(0, 0);
		gfx_print_text("Hinten / Linie");

		// Abfrage des Sensors hinten rechts
		current_floor = floor_relative[LINE_RIGHT];

		sprintf(output, "rel R %4u ", current_floor);
		gfx_move(0, 9);
		gfx_print_text(output);

		// Abfrage des Sensors hinten links
		current_floor = floor_relative[LINE_LEFT];

		sprintf(output, "rel L %4u ", current_floor);
		gfx_move(64, 9);
		gfx_print_text(output);

		// absoluten Wert hinten rechts abfragen
		current_floor = floor_absolute[LINE_RIGHT];

		sprintf(output, "abs R %4u ", current_floor);
		gfx_move(0, 18);
		gfx_print_text(output);

		// Abfrage des Sensors hinten links
		current_floor = floor_absolute[LINE_LEFT];

		sprintf(output, "abs L %4u ", current_floor);
		gfx_move(64, 18);
		gfx_print_text(output);

		delay(500);
	}

}

