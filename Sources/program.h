/*
 * PREN2.h
 *
 *  Created on: 23.03.2017
 *      Author: pirmin
 */

#ifndef SOURCES_PROGRAM_H_
#define SOURCES_PROGRAM_H_

/*
 * External Includes
 */
#include "Events.h" // Used for indirect Includes of Hardware Components

/*
 * Declaration of Constants used for the serial Interfaces
 */
enum serialPort
{
	PC,
	RasPi
};
enum serialResponse
{
	ACKNOWLEDGE = 0x20,
	ERROR = 0x10
};
enum serialCommands // !!!ERROR!!! not every value may be used, serial Rx interrupt isn't called with every byte
{
	START = 0x80, // RPi to FD
	ROMAN_NUMERAL_REQUEST = 0x40, // FD to RPi
	CURVE = 0x08, // FD to RPi
	PAUSE = 0xB0, // RPi to FD
	RESUME = 0x70 // RPi to FD
};

/*
 * program.c
 */
void start(void); // init method
void serialRxInt(uint8_t ch, uint8_t port); // called from Hardware Interrupt
void serialSend(uint8_t ch, uint8_t port); // sends byte to serial port
void simulateParcour(void); // method to simulate the serial communication of a complete parcour

#endif /* SOURCES_PROGRAM_H_ */
