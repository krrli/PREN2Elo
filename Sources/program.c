/*
 * program.c
 *
 *  Created on: 23.03.2017
 *      Author: pirmin
 */

#include "program.h"

void start(void){
	for(;;);
}

void serialRxInt(uint8_t ch, uint8_t port){
	switch (ch){
	case START:
		serialSend(ACKNOWLEDGE, port);
		// start driving
		break;
	case PAUSE:
		serialSend(ACKNOWLEDGE, port);
		// stop
		break;
	case RESUME:
		serialSend(ACKNOWLEDGE, port);
		// start driving again
		break;
	default:
		serialSend(ERROR, port);
	}
}

void serialSend(uint8_t ch, uint8_t port){
	switch (port){
	case PC:
		CLS1_SendChar(ch);
		break;
	case RasPi:
		CLS2_SendChar(ch);
		break;
	//default:
		// error
	}
}
