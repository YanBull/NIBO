/*
 ============================================================================
 Name        : helloMotors.c
 Author      : Daniel Wittekind
 Version     : 1.0
 Description : Demo zur Benutzung der Motoren des Nibo2
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

// Coprozessorfunktionen einbinden, da dieser die Motoren steuert
#include <nibo/copro.h>

// Kommunikationsfunktionen fuer die SPI Schnittstelle zum Coprozessor
#include <nibo/spi.h>

// Interrupts fuer die Kommunikation mit dem Coprozessor
#include <avr/interrupt.h>

// Ein- und Ausgabefunktionen
#include <stdio.h>

// zeigt die Werte der Motoren fuer die definierte Zeit in ms an
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

	// Endlosschleife
	while (1 == 1) {

		/*
		 * Die Bewegung der Raeder wird in Ticks ermittelt. Ein Tick wird gezaehlt, wenn
		 * ein Loch des roten (oder braunen) Plastikzahnrads am Fahrwerk des Nibo an
		 * der IR-Diode vorbeikommt. Beim Vorwaertsfahren wird hochgezaehlt, beim
		 * Rueckwaertsfahren runter.
		 *
		 * 29 Ticks sind etwa 10cm zurueckgelegte Strecke des jeweiligen Rades
		 *
		 * Eine Bewegungsanweisung kann als absolute oder relative Zielposition in Ticks
		 * erfolgen oder als Geschwindigkeitsangabe.
		 *
		 * Bewegungsanweisung durch Angabe der Geschwindigkeit
		 * 1. Parameter linkes Rad, 2. Parameter rechtes Rad
		 * beide Angaben in Ticks/s
		 * 29 Ticks/s entsprechen etwa 20cm/s
		 * (es sollten 10cm/s sein, sind es jedoch durch einen Fehler in der Bibliothek nicht)
		 */
		copro_setSpeed(14, 14);

		// Werte 10 s anzeigen (Funktion oben)
		showMotorValuesForTime(10000);

		// Motoren ausschalten und ausrollen lassen
		copro_stop();

		// 2s warten
		delay(2000);

		// Rueckwaerts fahren
		copro_setSpeed(-28, -28);

		// Werte anzeigen
		showMotorValuesForTime(5000);

		// Aktive Bremsung, die Motoren wirken beim Bremsen mit
		copro_stopImmediate();

		delay(2000);

		// Zuruecksetzen der Tickzaehler auf den gegebenen Wert (links, rechts)
		copro_resetOdometry(0, 0);

		/*
		 * Bewegungsanweisung durch Angabe einer Zielposition
		 * Der Nibo haelt bei Erreichen der Position an
		 *
		 * Angabe der absoluten Zielposition in Ticks, sowie der Geschwindigkeit (Ticks/s)
		 * Parameter: absolutes linkes Ziel, absolutes rechtes Ziel, Geschwindigkeit
		 */
		copro_setTargetAbs(280, 280, 28);

		// Ausgabe
		showMotorValuesForTime(4000);

		delay(4000);
		/*
		 * Bewegungsanweisung durch Angabe einer relativen Zielposition
		 *
		 * Das Ziel wird relativ zu dem aktuellen Stand an Ticks gesetzt.
		 * Also aktuell zB 40 Ticks, als relatives Ziel wird 40 uebergeben.
		 * Der Nibo faehrt 40 Ticks weit.
		 * Bei Uebergabe von 40 als absolutes Ziel (oben) wuerde der Nibo nicht
		 * losfahren, da er ja bei 40 steht.
		 *
		 * Parameter: relatives linkes Ziel, relatives rechtes Ziel, Geschwindigkeit
		 */
		copro_setTargetRel(140, 140, 14);

		// Ausgabe
		showMotorValuesForTime(3000);

		delay(4000);

		// zurueck zur Ausgangsposition fahren
		copro_setTargetRel(-420, -420, 28);

		// Ausgabe
		showMotorValuesForTime(6000);

		// Zuruecksetzen der Tickzaehler auf den gegebenen Wert (links, rechts)
		copro_resetOdometry(0, 0);

		// 2s warten
		delay(2000);
	}
}

