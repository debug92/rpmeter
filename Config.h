/*
 * Config.h
 *
 *  Created on: 19 giu 2016
 *      Author: Mario
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#define PULLUP
#define PACK_SAMPLE
/*
 *
 */
class Config {
public:
	Config();
	const static int PIN_IR = 7; //Pin relativo al modulo infrarosso. (TX/RX)
	const static int NUMBER_OF_SAMPLES = 5;
	const static int TIME_OF_CAPTURE = 100; //E' il tempo tra una cattura e l'altra. (ms)
};

#endif /* CONFIG_H_ */
