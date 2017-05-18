#ifndef SOURCES_TEST_H_
#define SOURCES_TEST_H_

#include "program.h"

void starttest(void);

#define ENABLE_TEST 0x

#define WAIT_BEFORE_TEST 0
#define WAIT_MINUTES 0

#define DO_NOTHING 0
#define TEST_SERIAL 0
#define TEST_TOF_SENSORS 0
#define TEST_TOF_SENSORS_CONTINUOUS 0
#define TEST_SERVO_BOARD 0 // !!! brushless !!!
#define TEST_BRUSHLESS_SWITCH 0// !!! brushless !!!
#define TEST_BRUSHLESS 0 // !!! brushless !!!
#define SERVO_CALIB 0 // !! brushless !!!
#define TEST_SERVO_CORR 0
#define TEST_MOTOR 0
#define TEST_MOTOR_DIRECTION 0
#define TEST_MOTOR_DIRECTION_MOTOR 3 // number of motor to test
#define TEST_MOTOR_AND_SERVO 0 // !!! brushless !!!
#define TEST_SERVO_CIRCLE 0
#define TEST_TOF_SERVO 0
#define TEST_MOTOR_FEDER 0
#define TEST_MOTOR_FEDER_BLOCKING 0
#define TEST_DRIVE_TO_START 0

void doNothing(void);

void testSerial(void);

void testTofSensors(void);

void testTofSensorsContinuous(void);

void testServoBoard(void);

void testBrushlessSwitch(void);

void testBrushless();

void servoCalib(void);

void testServoCorr(void);

void testMotor(void);

void testMotorDirection(uint8_t motor);

void testMotorAndServo();

void testServoCircle();

void testTofServo();

void testMotorFeder();

void testMotorFederBlocking();

void testDriveToStart();

#endif /* SOURCES_TEST_H_ */
