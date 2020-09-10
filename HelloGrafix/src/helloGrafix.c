/*
 ============================================================================
 Name        : helloGrafix.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Dimmen von Status LEDs und Display fuer den Nibo2
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

// Ein- und Ausgabefunktionen
#include <stdio.h>

int main(){

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// initialisiert das Display und die Grafikfunktionen
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	/*
	 * Setzt den Punkt, ab dem gezeichnet werden soll (Cursor)
	 * Der erste Parameter ist die Horizontale (x) und der zweite die Vertikale.
	 * Die Position 0,0 bezeichnet die obere linke Ecke des Displays
	 */
	gfx_move(10,0);

	/*
	 * zeichnet eine horizontale Linie mit der angegebenen Laenge in Pixeln
	 * Cursor ist nach einer Zeichenoperation immer am Ende der gezeichneten Grafik
	 */
	gfx_hline(20);

	// zeichnet eine vertikale Linie mit der angegebenen Laenge
	gfx_vline(20);

	// Die jeweilige Funktion liefert die aktuelle Cursorposition fuer Horizontale (x) und Vertikale (y)
	int x = gfx_get_x();
	int y = gfx_get_y();

	// Zeichnet eine Linie von der Cursorposition zum angegebenen Punkt
	gfx_lineTo(x - 20, y -20);

	gfx_move(40, 0);

	// schreibt den uebergebenen Text auf das Display
	gfx_print_text("word");

	gfx_move(10, 24);

	// schreibt einen einzelnen Buchstaben
	gfx_print_char('A');

	gfx_move(10, 40);

	x = gfx_get_x();
	y = gfx_get_y();

	char text[20] = "Cursorposition";

	gfx_print_text(text);

	gfx_move(10, 48);

	sprintf(text, "x: %02i pxl, y: %02i pxl", x, y);

	gfx_print_text(text);

    return 0;
}

