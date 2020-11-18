/*
 ============================================================================
 Name        : Header.h
 Author      : Yan
 Version     : 11.12.2020
 Description : Header des gesamtes Programs mit versch. includes
 ============================================================================
 */
//Header kann nur einmal included sein
#pragma once

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

// Sound
#include <nibo/sound.h>

/*
 * Bibliothek fuer Pulsweitenmodulation (PWM)
 * Emuliert analoge Stroeme an digitalen Ausgaengen.
 */
#include <nibo/pwm.h>

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

// NDS3 library
#include <nibo/nds3.h>

// Bibliothek fuer Bodensensoren
#include <nibo/floor.h>

// serial communication functions
#include "uart0.h"

// speed for Freie Bewegung-mode
#define _SPEED 25


//move.c
void ride();
void leftMove();
void rightMove();
void turnAround();
void deadLock();

//leds.c
void sensorLed();
void switchAll();
void musicLed();

char d_sens[5];
char backRide;
char lastTurn;
