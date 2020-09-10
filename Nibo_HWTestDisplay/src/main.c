/*
 * main.c
 *
 * program for verifying the display function
 *
 *  Created on: 28.05.2011
 *      Author: Daniel Wittekind
 */

#include <nibo/niboconfig.h>
#include <nibo/display.h>
#include <nibo/gfx.h>
#include <nibo/copro.h>
#include <nibo/delay.h>
#include <nibo/iodefs.h>
#include <nibo/pwm.h>
#include <nibo/bot.h>
#include <nibo/spi.h>

#include <avr/interrupt.h>
#include <stdio.h>

#include "switchS3.h"

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

int main() {

	sei();
	bot_init();
	spi_init();
	pwm_init();
	display_init(DISPLAY_TYPE_TXT);
	gfx_init();

	int mode = 0;

	while (1 == 1) {
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
				break;
			}
		}
	}

}

