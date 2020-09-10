/*
 ============================================================================
 Name        : helloSound.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Dieses Testprogramm zeigt Ihnen, wie Sie dem Lautsprecher
               des Nibos Toene entlocken koennen.
 ============================================================================
 */
#include <nibo/niboconfig.h>
#include <nibo/display.h>
#include <nibo/gfx.h>

#include <nibo/sound.h>
#include <avr/interrupt.h>
#include "gerty_smile.xbm"
#include "n2sound.h"



// drei Lieder zur Anregung
/**
 * playIndi - plays the "Indianer Jones" soundtrack
 * Authors: Konstantin Barth, Christian Schilling
 */
void playIndi() {
	//note timings, tempo = 140 bpm
	int l8 = 214;
	int l16 = 107;
	cli(); 			//Atomarer Zustand: damit die Toene korrekt abgespielt werden.
					//Lied wird komplett abgespielt und dann unterbrochen werden.

	//Indiana Jones -Soundtrack
	tone(E4, l16);
	_delay_ms(l16);
	tone(F4, l16);
	tone(G4, l16);
	_delay_ms(l8);
	tone(C5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(D4, l16);
	_delay_ms(l8);
	tone(E4, l16);
	//_delay_ms(l8);
	tone(F4, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(G4, l16);
	_delay_ms(l8);
	tone(A4, l16);
	tone(B4, l16);
	_delay_ms(l8);
	tone(F5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(A4, l16);
	_delay_ms(l8);
	tone(B4, l16);
	tone(C5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(D5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(E5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(E4, l16);
	_delay_ms(l8);
	tone(F4, l16);
	tone(G4, l16);
	_delay_ms(l8);
	tone(C5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(D5, l16);
	_delay_ms(l8);
	tone(E5, l16);
	tone(F5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(G4, l16);
	_delay_ms(l8);
	tone(G4, l16);
	_delay_ms(l16);
	tone(E5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(D5, l16);
	_delay_ms(l8);
	tone(G4, l16);
	_delay_ms(l8);
	tone(E5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(D5, l16);
	_delay_ms(l8);
	tone(G4, l16);
	_delay_ms(l8);
	tone(E5, l16);
	_delay_ms(l8);
	_delay_ms(l8);
	tone(D5, l16);
	_delay_ms(l8);
	tone(G4, l16);
	_delay_ms(l8);
	tone(F5, l16);
	_delay_ms(l8);
	tone(E5, l16);
	tone(D5, l16);
	_delay_ms(l8);
	tone(C5, l16);
	tone(C5, l16);
	sei();			// Ende des AZ: jetzt sind Interrupts wieder moeglich

	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	//ENDE:
}

/**
 * playGodfather - plays the "Godfather" song
 * Authors      : Konstantin Barth, Christian Schilling
 */
void playGodfather() {
	//note timings, tempo = 140 bpm
	int l8 = 214;
	int l16 = 107;
	cli();

	// The Godfather
	tone(B4, l8);
	_delay_ms(l16);
	tone(E5, l8);
	_delay_ms(l16);
	tone(G5, l8);
	_delay_ms(l16);
	tone(F5, l8);
	_delay_ms(l16);
	tone(E5, l8);
	_delay_ms(l16);
	tone(G5, l8);
	_delay_ms(l16);
	tone(E5, l8);
	_delay_ms(l16);
	tone(G5, l8);
	_delay_ms(l16);
	tone(E5, l8);
	_delay_ms(l16);
	tone(F5SHARP, l8);
	_delay_ms(l16);
	tone(C5, l8);
	_delay_ms(l16);
	tone(D5, l8);
	_delay_ms(l16);
	tone(B4, l8);
	sei();

	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	_delay_ms(l8);
	//ENDE:
}

/**
 * playDarthVader
 * Authors: Yaroslav Sabinin, Yulia Zhuravleva
 */
int playDarthVader() //darth vader
{
	    int duration=500;
	    int del=120;
	    int re = 0;

//1---------------------------
	    //G4
		re = tone(392, duration);
		_delay_ms(del);

		//G4
		re = tone(392, duration);
		_delay_ms(del);

		//G4
		re = tone(392, duration);
		_delay_ms(del);

		//F4#
		re = tone(311, duration-(duration/4));
		_delay_ms(del);

		//A4#
		re = tone(466, duration/4);
		_delay_ms(del);

//2----------------------------------------
		//G4
		re = tone(392, duration);
		_delay_ms(del);

		//F4#
		re = tone(311, duration-(duration/4));
		_delay_ms(del);

		//A4#
		re = tone(466, duration/4);
		_delay_ms(del);

		//D5
		re = tone(392, duration);
		re = tone(392, duration);
		_delay_ms(del);

//3---------------------------------------------

		//D5
		re = tone(587, duration);
		_delay_ms(del);

         //D5
		re = tone(587, duration);
		_delay_ms(del);

		//D5
		re = tone(587, duration);
		_delay_ms(del);

		 //D5#
		re = tone(587, duration-(duration/4));
		_delay_ms(del);

		//A4#
		re = tone(466, duration/4);
		_delay_ms(del);
//4------------------------------------------------

		//F#4
		re = tone(369, duration);
		_delay_ms(del);

		//D4#
		re = tone(311, duration-(duration/4));
		_delay_ms(del);

		//A4#
		re = tone(466, duration/4);
		_delay_ms(del);

		//G4
		re = tone(392, duration);
		re = tone(392, duration);
		_delay_ms(del);

		_delay_ms(2*del);

		re = 0;
	    return re;
}

int main() {

   display_init(DISPLAY_TYPE_TXT);
   gfx_init();

   //Wichtig fuer die Initialisierung des Lautsprechers.
   //Sonst erklingen die Toene nur sehr leise:
   sound_init();

   //Und nun ein Smiley...
   gfx_move(0, 0);
   gfx_fill(0);
   gfx_draw_xbm_P(gerty_smile_width, gerty_smile_height, (PGM_P) gerty_smile_bits);

   //Es folgt ein Beispiel zur Ansteuerung des Lautsprechers:
   while (1) {
	   playDarthVader();
   }

  return 0;
}

