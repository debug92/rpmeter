/*
 * Interrupts.cpp
 *
 *  Created on: 20 giu 2016
 *      Author: Mario
 */
#include "cInterrupt.h"

#include "Arduino.h"
#include "Config.h"
#include "PinChangeInt.h"

cInterrupt::cInterrupt() {

	/*
	 * Se definita "PULLUP", verrà attivata la resistenza di pull-up per
	 * garantire che gli ingressi arduino siano a livelli logici previsti.
	 * */

#ifndef PULLUP
	pinMode(Config::PIN_IR, INPUT_PULLUP);
#else
	pinMode(Config::PIN_IR, INPUT);
#endif

}
int rpmCount = 0;
unsigned long timeOfCapture = 0;

int count = 0;

void cInterrupt::stop() {
	PCintPort::detachInterrupt(Config::PIN_IR);
}

/* Restituisce il timestamp relativo al campionamento fatto. */
unsigned long cInterrupt::getTimeOfCapture() {
	return timeOfCapture;
}
/*
 * Crea un pacco di 5 misurazioni con una differenza di tempo pari (espressa in ms)
 * a quella specificata nelle configurazioni.
 */
cInterrupt::Sample tmp[Config::NUMBER_OF_SAMPLES];

/*
 * Restituisce il Sample con il numero di interrupt contati fino all'istante timeOfCapture.
 */
cInterrupt::Sample getRaw() {
	cInterrupt::Sample tmp;
	tmp.rpmCount = rpmCount;
	tmp.timeOfCapture = timeOfCapture;
	return tmp;
}
/*
 * Restituisce la differenza tra due timestamp per capire il tempo in millisecondi trascorso.
 */
int getDifference(unsigned long oldTime, unsigned long newTime) {
	return (newTime - oldTime);
}
/*
 * Inserisce nell'array dei Sample, N° misurazioni con differenza di tempo pari a quella specificata
 * nel file di configurazione.
 */
void addSample() {
	if (count <= Config::NUMBER_OF_SAMPLES) {
		if (count > 1) {
			if (getDifference(tmp[count - 1].timeOfCapture, millis())
					>= Config::TIME_OF_CAPTURE) {
				tmp[count] = getRaw();
				count++;
			}
		} else {
			tmp[count] = getRaw();
			count++;
		}

	} else {
		count = 0;
		tmp[count] = getRaw();

	}
}

/*
 * Restituisce il numero di conteggi degli interrupt fatti.
 */
int cInterrupt::getRpmCount() {
	return rpmCount;
}

/*
 * Resituisce un Pack di N° misurazioni, dove N° è uguale al numero massimo di misurazioni
 * specificato nel file di Config.
 */
cInterrupt::Sample * cInterrupt::getPack() {
	return tmp;
}

/*
 * Verrà richiamato ad ogni Interrupt sul PIN specificato nel file config.
 */
void intRpm() {
	/*
	 * Qui va inserito il codice da eseguire ogni qualvolta si verifica
	 * l'interrupt RISING sul PIN specificato nel file di configurazione.
	 */
	rpmCount++;
	timeOfCapture = millis();
#ifndef PACK_SAMPLE
	addSample();
#endif
}

void cInterrupt::start() {
	/*
	 * Va richiamato per effettuare l'attachInterrupt sul PIN specificato nel file
	 * di configurazione.
	 * Per ogni interrupt in fronte di salita sul PIN specificato, verra richiamata la
	 * funzione intRpm.
	 */
	rpmCount = 0;
	timeOfCapture = 0;

	PCintPort::attachInterrupt(Config::PIN_IR, &intRpm, RISING);
}
