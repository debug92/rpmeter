/*
 * Interrupts.h
 *
 *  Created on: 20 giu 2016
 *      Author: Mario
 */

#ifndef CINTERRUPT_H_
#define CINTERRUPT_H_

/*
 *
 */
class cInterrupt {
public:

	cInterrupt();
	void start();
	unsigned long getTimeOfCapture();
	int getRpmCount();
	void stop();
	int getDifference(unsigned long oldTime, unsigned long newTime);
	struct Sample {
		int rpmCount = 0;
		unsigned long timeOfCapture = 0;
	};
	Sample * getPack();
private:
	Sample getRaw();
};


#endif /* CINTERRUPT_H_ */

