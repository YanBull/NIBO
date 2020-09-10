/*
 *
 * @breif Programm to test most of the main Hardware components.
 *
 * @author Valentin Schröter
 * @version 09.2019
 */

#include "main.h"
#include "xBee.h"
#include "switchS3.h"

/**
 * updated bei jedem Aufruf die Tickanzeige
 */
void update_data() {

	copro_update();

	char text[20];

	//Ausgabe Symbol rechts
	gfx_move(0, 38);
	sprintf(text, "R");
	gfx_print_text(text);

	//Ausgabe Symbol links
	gfx_move(116, 38);
	sprintf(text, "L");
	gfx_print_text(text);

	//Ausgabe ticks rechts
	gfx_move(0, 47);
	sprintf(text, "%i", copro_ticks_r);
	gfx_print_text(text);

	//Ausgabe Beschreibung ticks
	gfx_move(48, 47);
	sprintf(text, "ticks");
	gfx_print_text(text);

	//Ausgabe ticks links
	gfx_move(108, 47);
	sprintf(text, "%i", copro_ticks_l);
	gfx_print_text(text);

	//Ausgabe ticks rechts
	gfx_move(0, 56);
	sprintf(text, "%i", copro_speed_r);
	gfx_print_text(text);

	//Ausgabe Beschreibung ticks
	gfx_move(48, 56);
	sprintf(text, "speed");
	gfx_print_text(text);

	//Ausgabe ticks links
	gfx_move(108, 56);
	sprintf(text, "%i", copro_speed_l);
	gfx_print_text(text);
}

/**
 * print activities
 */
void print_activities(char text1[], char text2[]) {
	//Info Screen zeichnen
	gfx_term_clear(0);
	gfx_move(0, 0);
	gfx_print_text("Now: ");
	gfx_move(0, 8);
	gfx_print_text(text1);
	gfx_move(0, 16);
	gfx_print_text("Next: ");
	gfx_move(0, 24);
	gfx_print_text(text2);

}

/**
 * Geschwindigkeit setzen links vorwaerts
 */
void setSpeed_left_forward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(30,0)", "setSpeed(-30,0)");

	copro_setSpeed(30, 0);
}

/**
 * Geschwindigkeit setzen links rueckwaerts
 */
void setSpeed_left_backward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(-30,0)", "setSpeed(0,30)");

	copro_setSpeed(-30, 0);
}

/**
 * Geschwindigkeit setzen links vorwaerts
 */
void setSpeed_right_forward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(0,30)", "setSpeed(0,-30)");

	copro_setSpeed(0, 30);
}

/**
 * Geschwindigkeit setzen links rueckwaerts
 */
void setSpeed_right_backward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setSpeed(0,-30)", "setTargetRel(290,290,29)");

	copro_setSpeed(0, -30);
}

/**
 * relatives Ziel, 1m vorwaerts
 */
void setTargetRel_forward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setTargetRel(290,290,29)", "setTargetRel(-290,-290,29)");

	copro_setTargetRel(290,290,29);
}

/**
 * relatives Ziel, 1m rueckwaerts
 */
void setTargetRel_backward() {

	copro_stop();
	copro_resetOdometry(0, 0);

	//Info Screen zeichnen
	print_activities("setTargetRel(-290,-290,29)", "Pause");

	copro_setTargetRel(-290,-290,29);
}

/**
 * Unterbrechung zum Nichtstun
 */
void do_nothing(){
	copro_stop();
	copro_resetOdometry(0, 0);
}


void runDistanceLedXbeeTest() {
	pwm_init();
	leds_init();

	xBee_init();

	// Aktivierung von Interrupts
	sei();

	// Initialisierung der SPI Schnittstelle
	spi_init();

	// Distanzmessung anschalten
	copro_ir_startMeasure();

	gfx_fill(0);
	gfx_move(0, 0);
	gfx_print_text("LED Test");

	// turn on all LEDs
	for (int i = 0; i < 8; i++) {
		leds_set_status(LEDS_ORANGE, i);
	}
	leds_set_headlights(1023);


	int index = 0;
	int intensity[5] =  {1023, 512, 256, 128, 0};

	char x = 0;

	char text[20];

	// Wait until button was pressed
	while(!s3_was_pressed()) {

		// if the receive buffer is not empty ->
		if (xBee_receivedData())
		{
			// -> get next received data byte of the buffer
			x = xBee_readByte();

			// prints the received char on the display
			sprintf(text, "Empfang Zeichen: %c", (char)x);
			gfx_move(0, 0);
			gfx_print_text(text);

			// if the buffer to send data is not full and the incoming char is not a 0->
			if(xBee_readyToSend() && x!=0)
			{
				// -> puts the char into the buffer to send the char
				xBee_sendByte(x);
				// prints the char "to send" on the display
				sprintf(text, "Gesendetes Zeichen: %c", (char)x);
				gfx_move(0, 10);
				gfx_print_text(text);
			}

		}

		gfx_move(0, 20);

		sprintf(text, "Intensity %i      ", intensity[index]);
		gfx_print_text(text);

		leds_set_status_intensity(intensity[index]);
		leds_set_headlights(intensity[index]);

		index = (index + 1) % 5;

		// Beschreibung
		gfx_move(0, 30);
		gfx_print_text("Distanzen");

		// Aktualisierung aller Daten vom Coprozessor
		copro_update();

		// Sensoren in Schleife abfragen
		for(int i = 0; i < 5; i++){

			// In jeder Iteration wird der Sensor weiter rechts abgefragt
			int current_distance = copro_distance[i]/256;

			// Ausgabe
			sprintf(text, "%3i", current_distance);
			gfx_move(23*i, 40);
			gfx_print_text(text);
		}



		delay(200);
	}

	// Turn off all LEDs
	for (int i = 0; i < 8; i++) {
		leds_set_status(LEDS_OFF, i);
	}
	leds_set_headlights(0);
}

void runMotorTest() {

	int mode = 0;
	int goon = 1;

	gfx_fill(0);
	gfx_move(0, 0);
	gfx_print_text("Motor Test");
	gfx_move(0, 8);
	gfx_print_text("Next: setSpeed(0,30)");

	while (goon) {
		if (s3_was_pressed()) {

			mode++;

			switch (mode) {
			/*
			case 1:
				// Geschwindigkeit links vorwaerts
				setSpeed_left_forward();
				break;
			case 2:
				// Geschwindigkeit links rueckwaerts
				setSpeed_left_backward();
				break;
			case 3:
				// Geschwindigkeit rechts vorwaerts
				setSpeed_right_forward();
				break;
			case 4:
				// Geschwindigkeit rechts vorwaerts
				setSpeed_right_backward();
				break;
			*/
			case 1:
				// Ziel vorwaerts
				setTargetRel_forward();
				break;
			case 2:
				// Ziel rueckwaerts
				setTargetRel_backward();
				break;
			case 3:
				// Pause
				do_nothing();
				gfx_fill(0);
				gfx_move(0, 0);
				gfx_print_text("Motor Test");
				//gfx_move(0, 8);
				//gfx_print_text("Next: setSpeed(0,30)");
				mode = 0;
				goon = 0;
				break;
			}
		}
		update_data();
	}
}



/**
 * draws a chess board to the display
 * int starting_field determines whether to start with a white (0) or black (1) field
 * int tile_size determines the size of the chess board tiles
 */
void draw_chess_board(int starting_field, int tile_size) {

	gfx_fill(0);

	gfx_move(0, 0);

	int column = 0;

	while ((column * tile_size) < 64) {
		int row = 0;
		while ((row * tile_size) < 128) {
			if (((column % 2 == 0) && (starting_field == 1)) || ((column % 2
					== 1) && (starting_field == 0)))
				gfx_move((row * tile_size), column * tile_size);
			else if (((column % 2 == 1) && (starting_field == 1)) || ((column
					% 2 == 0) && (starting_field == 0)))
				gfx_move(((row + 1) * tile_size), column * tile_size);
			gfx_box(tile_size, tile_size);
			row = row + 2;
		}
		column++;
	}

}


void runDisplayTest() {
	int mode = 0;
	int goOn = 1;
	while (goOn) {
		if (s3_was_pressed()) {

			mode++;

			switch (mode) {
			case 1:
				// chess pattern
				draw_chess_board(0, 4);
				break;
			case 2:
				// reversed chess pattern
				draw_chess_board(1, 4);
				break;
			case 3:

				// place cursor in upper left corner
				gfx_move(0, 0);
				// draw filled rectangle over all pixels
				gfx_box(128, 64);
				break;
			case 4:
				// clear screen
				gfx_fill(0);
				mode = 0;
				goOn = 0;
				break;
			}
		}
	}
}


void runFloorTest() {

	// initialisiert die Bodensensorfunktionen
	floor_init();

	// Variable fuer Ausgabetext
	char output[10] = "";

	// speichert die Sensorwerte
	unsigned int current_floor = 0;

	while (!s3_was_pressed()) {

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
		sprintf(output, "rel R %4u", current_floor);
		gfx_print_text(output);

		// linken Sensor vorn abfragen
		current_floor = floor_relative[FLOOR_LEFT];

		sprintf(output, "rel L %4u", current_floor);
		gfx_move(64, 45);
		gfx_print_text(output);

		/*
		 * floor_absolute[]	enthaelt die rohen Sensorwerte
		 *
		 * Abfrage des Sensors vorne rechts
		 */
		current_floor = floor_absolute[FLOOR_RIGHT];

		// Ausgabe
		sprintf(output, "abs R %4u", current_floor);
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

		sprintf(output, "rel R %4u", current_floor);
		gfx_move(0, 9);
		gfx_print_text(output);

		// Abfrage des Sensors hinten links
		current_floor = floor_relative[LINE_LEFT];

		sprintf(output, "rel L %4u", current_floor);
		gfx_move(64, 9);
		gfx_print_text(output);

		// absoluten Wert hinten rechts abfragen
		current_floor = floor_absolute[LINE_RIGHT];

		sprintf(output, "abs R %4u", current_floor);
		gfx_move(0, 18);
		gfx_print_text(output);

		// Abfrage des Sensors hinten links
		current_floor = floor_absolute[LINE_LEFT];

		sprintf(output, "abs L %4u", current_floor);
		gfx_move(64, 18);
		gfx_print_text(output);
	}

}


int main() {

	sei();
	bot_init();
	spi_init();
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();



	while (1) {
		runDistanceLedXbeeTest();
		runDisplayTest();
		runFloorTest();
		runMotorTest();
	}




	return 0;

}

