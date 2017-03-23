/*
 * PREN2.h
 *
 *  Created on: 23.03.2017
 *      Author: pirmin
 */

#ifndef SOURCES_PREN2_H_
#define SOURCES_PREN2_H_

/*
 * Type Definitions
 */
typedef unsigned char uint8;

/*
 * Declaration of Commands and Responses on the Serial Interface
 */
enum serialResponse
{
	ACKNOWLEDGE = 0x20,
	ERROR = 0x10
};
enum serialCommands
{
	START = 0x80,
	ROMAN_NUMERAL_REQUEST = 0x40,
	CURVE = 0x08,
	PAUSE = 0xC0,
	RESUME = 0x60
};

/*
 * program.c
 */
void start(void);

#endif /* SOURCES_PREN2_H_ */
