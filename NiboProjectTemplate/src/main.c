

/*
 ============================================================================
 Name        : helloDistance.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Demo zum Auslesen der Distanzsensoren des Nibo2
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

/*
 * Die Distanzsensoren sowie die Motoren werden vom Coprozessor gesteuert.
 * Daher sind eine Bibliotheken fuer die Kommunikation mit diesem noetig.
 *
 * Bibliothek fuer Coprozessor-spezifische Funktionen
 */
#include <nibo/copro.h>

// Kommunikationsfunktionen fuer die SPI Schnittstelle zum Coprozessor
#include <nibo/spi.h>

// Interrupts fuer die Kommunikation mit dem Coprozessor
#include <avr/interrupt.h>

// Ein- und Ausgabefunktionen
#include <stdio.h>

// Bibliothek fuer das Ansteuern der Status LEDs
#include <nibo/leds.h>

#include "the_header.h"
void showMotorValuesForTime(int time) {

  // Textspeicher
  char text[20] = "";

  // Zaehlvariable
  int i = 0;

  // 8s Schleife, waehrend der die Werte auf dem Display gezeigt werden
  while (i < time + 1) {

    // Erhoehen & Warten
    i += 200;
    delay(200);

    // Werte des Coprozessors aktualisieren
    copro_update();

    /*
     * Folgende Daten stehen zur Verfuegung:
     *
     * Aktuelle Geschwindigkeiten der beiden Raeder (Ticks/s)
     *
     * copro_speed_l & copro_speed_r
     *
     * Aktuelle Ticks der beiden Raeder
     *
     * copro_ticks_l & copro_ticks_r
     */

    sprintf(text, "Ticks l: %3i  r: %3i", copro_ticks_l, copro_ticks_r);
    gfx_fill(0);
    gfx_move(0, 0);
    gfx_print_text(text);

    sprintf(text, "Speed l: %3i  r: %3i", copro_speed_l, copro_speed_r);
    gfx_move(0, 10);
    gfx_print_text(text);

    /*
     * Wurde eine Funktion ausgewaehlt, die Zielpositionen angibt, kann
     * au\3erdem die verbleibende Distanz zum Ziel angezeigt werden.
     * Es wird jeweils der Wert des Rades mit der groe\3eren verbleibenden Distanz
     * zurueckgegeben
     */
    sprintf(text, "Ziel in %4i Ticks", copro_target_distance);
    gfx_move(0, 20);
    gfx_print_text(text);
  }
}

int main(){

	// Aktivierung von Interrupts
	sei();

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// Initialisierung der SPI Schnittstelle
	spi_init();

	// initialisiert das Display und die Grafikfunktionen
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	// Distanzmessung anschalten
	copro_ir_startMeasure();

	// Ausgabetext
	char output[20] = "";

	// Variable zum Zwischenspeichern der Sensorwerte
	int current_distance = 0;

	// Initialisierung der LEDs
	leds_init();

//	int redborder = 200;
//	int orangeborder = 150;
	copro_setSpeed(19, 19);
	// Endlosschleife
	while (1 == 1) {

		// Display leeren
		gfx_fill(0);

		// Beschreibung
		gfx_move(0, 0);
		gfx_print_text("Distanzen");

		// Aktualisierung aller Daten vom Coprozessor
		copro_update();

		/*
		 * Das Array copro_distance[] enthaelt die rohen Distanzwerte
		 * Index 0 bezeichnet den linken Sensor, 4 den rechten, die
		 * Werte dazwischen entsprechend den Sensoren dazwischen.
		 *
		 * Da die Werte in einem gro\3en Spektrum liegen, sollte man sie
		 * durch Division normalisieren.
		 *
		 * Abfrage des linken Sensors
		 */
		current_distance = copro_distance[0]/256;

		// Ausgabe
		sprintf(output, "%3i ", current_distance);
		gfx_move(0, 10);
		gfx_print_text(output);

		ride();
		delay(20);

	}

}

