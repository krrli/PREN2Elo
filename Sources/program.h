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
	ERROR = 0x10,
	BUTTON1 = 0x01,
	BUTTON2 = 0x02,
	BUTTON3 = 0x03,
	BUTTON4 = 0x04,
	BUTTON5 = 0x05
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
 * Declaration of states for main loop
 */
enum parcoursState
{
	DRIVE_FORWARD,
	DRIVE_BACKWARD,
	DRIVE_LEFT,
	DRIVE_RIGHT,
	STOPPED
};
enum parcourType
{
	PARCOUR_A = 0x00,
	PARCOUR_B = 0x01
};
enum buttonChecked
{
	BUTTON_CHECKED,
	BUTTON_UNCHECKED
};
enum wheelPosition
{
	STRAIGHT,
	SIDEWAYS
};
enum parcourEnd
{
	REACHED,
	NOT_REACHED
};
enum driveDistance
{
	CURVE_DIST = 0xA0, // todo: change values
	BUTTON1_A = 0xA0,
	BUTTON2_A = 0xA0,
	BUTTON3_A = 0xA0,
	BUTTON4_A = 0xA0,
	BUTTON5_A = 0xA0,
	BUTTON1_B = 0xA0,
	BUTTON2_B = 0xA0,
	BUTTON3_B = 0xA0,
	BUTTON4_B = 0xA0,
	BUTTON5_B = 0xA0,
};

/*
 * method declarations
 */
/*
 * program.c
 */
void start(void); // init method
void serialRxInt(uint8_t ch, uint8_t port); // called from Hardware Interrupt
void serialSend(uint8_t ch, uint8_t port); // sends byte to serial port
void simulateParcour(void); // method to simulate the serial communication of a complete parcour
void mainLoop(void); // main loop for driving

/*
 * tof.c
 */
void initToF(void);

#endif /* SOURCES_PROGRAM_H_ */
