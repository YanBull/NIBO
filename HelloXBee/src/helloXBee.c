/**
 * @author Felix Hahn
 * @author Valentin Schroeter
 *
 * @version 09.2019
 *
 * @brief This Program can be used to test the XBEE communication between to XBEE modules.
 */


// libraries for standard functions of the Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>

// libary for the use of the display
#include <nibo/display.h>

// libary for the use of the graphical functions
#include <nibo/gfx.h>

// libary for standard input and output operations of the Nibo2
#include <stdio.h>

// includes interrupts
#include <stdint.h>

// includes header file for the use of the UART1-Port
//#include "uart0.h"

// include delay operations
#include <nibo/delay.h>


// includes SPI communication library
#include <nibo/spi.h>

// includes microcontroller hardware interrupts
#include <avr/interrupt.h>

#include <nibo/leds.h>

// includes xBee Communication
// be aware to include it locally with ""
#include "xBee.h"


/**
 * Main function of the helloXBee.c file.
 * Receives and sends chars using the UART1-Port of the Nibo.
 */
int main(){


    // initialize the robot
    bot_init();

    // initialize spi-port
    spi_init();

    // initialize the display and the graphical operations
    display_init(DISPLAY_TYPE_TXT);
    gfx_init();

    // buffer for the chars, is needed to print the chars on the display
    char text[20] = "";

    // declare and initialize a variable for storing received characters
    uint8_t x=0;

    // prints text on the Display
    sprintf(text, "Hallo XBEE");
    gfx_move(0, 0);
    gfx_print_text(text);


    leds_init();

    // initialize xBee Module
    xBee_init();

    sei();

    // Operation loop
    while (1) {

        // if the receive buffer is not empty ->
        if (xBee_receivedData())
        {
            // -> get next received data byte of the buffer
            x = xBee_readByte();

            // prints the received char on the display
            sprintf(text, "Empfang Zeichen: %c", (char)x);
            gfx_move(0, 15);
            gfx_print_text(text);

            // if the buffer to send data is not full and the incoming char is not a 0->
            if(xBee_readyToSend() && x!=0)
            {
                // -> puts the char into the buffer to send the char
                xBee_sendByte(x);
                // prints the char "to send" on the display
                sprintf(text, "Gesendetes Zeichen: %c", (char)x);
                gfx_move(0, 30);
                gfx_print_text(text);
            }

        }


        // Delay for the operation loop
        _delay_ms(5);

    }

    return 0;

}


