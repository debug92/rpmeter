#include "Arduino.h"
#include "cInterrupt.h"

cInterrupt p;
void setup() {
	Serial.begin(9600);
	p = cInterrupt();
	p.start();

}

// The loop function is called in an endless loop
void loop() {
	delay(1000);
	p.stop();

	/* Elaborazioni con parametri ottenuti.
	 * Tutti i parametri catturati sono presenti nell'oggetto p.
	 *
	 */

	p.start();
}

