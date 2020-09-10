/*
 ============================================================================
 Name        : helloRC5.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Demo zum Auslesen von empfangenen RC5 Kommandos
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
 * Fuer die RC5 Kommunikation, werden die Distanzsensoren benutzt.
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

int main() {

	// Aktivierung von Interrupts
	sei();

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// Initialisierung der SPI Schnittstelle
	spi_init();

	// initialisiert das Display und die Grafikfunktionen
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	/*
	 * nur zu Demozwecken: Distanzmessung anschalten
	 * copro_ir_startMeasure();
	 *
	 * Da die Distanzsensoren zum Erkennen der RC5 Kommandos genutzt
	 * werden, muessen diese erst wieder ausgeschaltet werden.
	 * (Es sei denn, sie wurden nicht angeschaltet)
	 *
	 * copro_ir_stop();
	 */


	// Ausgabetext
	char text1[20] = "";
	char text2[20] = "";

	// Variable haelt das RC5 Kommando
	int rc5 = 0;

	// Beschreibung ausgeben
	gfx_move(0, 0);
	gfx_print_text("RC5 Receiver");

	// Endlosschleife, empfangenen Code anzeigen und wieder aussenden
	while (1 == 1) {

		// Werte vom Coprozessor aktualisieren
		copro_update();

		// letztes RC5 Kommando auslesen
		rc5 = (int) copro_rc5_cmd;

		sprintf(text1, "RC5 (hex): %05x", rc5);
		sprintf(text2, "RC5 (int): %05i", rc5);
		gfx_move(0, 10);
		gfx_print_text(text1);

		gfx_move(0, 20);
		gfx_print_text(text2);

		delay(100);
	}

}

