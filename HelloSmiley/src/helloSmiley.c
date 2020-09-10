/*
 ============================================================================
 Name        : helloSmiley.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Zeigt die Darstellung von xbm-Grafiken auf dem Display des Nibo2
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

// Die darzustellende Grafik
#include "gerty_smile.xbm"

int main(){

	// Initialisierung des Roboters (immer noetig)
	bot_init();

	// initialisiert das Display und die Grafikfunktionen
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	//reinige Display
    gfx_move(0, 0);
    gfx_fill(0);
    // gebe xbm-Grafik auf dem Display aus.
    // Die Werte der Parameter stehen in gerty_smile.xbm
    gfx_draw_xbm_P(gerty_smile_width, gerty_smile_height, (PGM_P) gerty_smile_bits);

    return 0;

}

