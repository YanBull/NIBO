/*
 ============================================================================
 Name        : helloTerminal.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Zeigt den Terminalmodus des Display vom Nibo2
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

int main(){

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// initialisiert das Display und die Grafikfunktionen
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	// Zaehlvariable
	int i = 0;

	// Textspeicher
	char text[20];

	// Endlosschleife
	while(1==1){

		// Zaehlvariable in Textspeicher schreiben
		sprintf(text, "i ist %3i", i);

		/*
		 * Text im Terminalmodus ausgeben
		 * Schreibt alles automatisch hintereinander, Umbruch am Bildschirmende
		 */
		gfx_term_print(text);

		// Zaehlvariable erhoehen
		i++;

		delay(1000);


	}

}

