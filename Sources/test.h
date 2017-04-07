#ifndef SOURCES_TEST_H_
#define SOURCES_TEST_H_

#include "program.h"

void starttest(void);

#define ENABLE_TEST 1

#define WAIT_BEFORE_TEST 0
#define WAIT_MINUTES 0

#define TEST_SERIAL 0
#define TEST_TOF_SENSORS 0
#define TEST_TOF_SENSORS_CONTINUOUS 0
#define TEST_SERVO_BOARD 0 // !!! brushless !!!
#define TEST_BRUSHLESS_SWITCH 1// !!! brushless !!!
#define TEST_MOTOR 0

void testSerial(void);

void testTofSensors(void);

void testTofSensorsContinuous(void);

void testServoBoard(void);

void testBrushlessSwitch(void);

void testMotor(void);

#endif /* SOURCES_TEST_H_ */
