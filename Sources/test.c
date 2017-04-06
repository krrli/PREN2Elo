#include "test.h"

void starttest(void) {
	/* exit if tests are not wanted */
	if (ENABLE_TEST == 0) {
		return;
	}

	/* wait */
	for (uint8_t i = 0; i < WAIT_MINUTES; i++) {
		WAIT1_Waitms(60000);
	}
	WAIT1_Waitms(10000);

	/* test serial communication */
	if (TEST_SERIAL) {
		testSerial();
	}

	/* test tof sensors */
	if (TEST_TOF_SENSORS) {
		testTofSensors();
	}

	/* test tof sensors */
	if (TEST_TOF_SENSORS_CONTINUOUS) {
		testTofSensorsContinuous();
	}

	/* test servo board */
	if (TEST_SERVO_BOARD) {
		testServoBoard();
	}

	/* test motor controller */
	if (TEST_MOTOR) {
		testMotor();
	}

	/* end loop */
	for (;;)
		;
}

void testSerial(void) {
	/* send CURVE signal to raspi */
	serialSend(CURVE, PC);
	serialSend(CURVE, RasPi);

	/* wait */
	WAIT1_Waitms(1000);

	/* send ROMAN_NUMERAL_REQUEST to raspi */
	serialSend(ROMAN_NUMERAL_REQUEST, PC);
	serialSend(ROMAN_NUMERAL_REQUEST, RasPi);

	/* end loop */
	for (;;) {
	}
}

void testTofSensors(void) {
	uint8_t res;
	uint16_t val;

	/* init tof */
	res = initToF();
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(1);

	/* read tof */
	for (uint8_t i = 0; i < NUMBER_OF_SENSORS; i++) {
		res = getToFValueMillimeters(i, &val);
		serialSend(i, PC);
		WAIT1_Waitms(1);
		serialSend(i, RasPi);
		WAIT1_Waitms(1);
		serialSend(res, PC);
		WAIT1_Waitms(1);
		serialSend(res, RasPi);
		WAIT1_Waitms(1);
		serialSend((val >> 8), PC);
		WAIT1_Waitms(1);
		serialSend((val >> 8), RasPi);
		WAIT1_Waitms(1);
		serialSend((val & 0xff), PC);
		WAIT1_Waitms(1);
		serialSend((val & 0xff), RasPi);
		WAIT1_Waitms(1);
	}
}

void testTofSensorsContinuous(void) {
	uint8_t res;
	uint16_t val;

	/* init tof */
	res = initToF();
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(1);

	/* read tof */
	for (;;) {
		for (uint8_t i = 0; i < NUMBER_OF_SENSORS; i++) {
			res = getToFValueMillimeters(i, &val);
			serialSend(i, PC);
			WAIT1_Waitms(1);
			serialSend(i, RasPi);
			WAIT1_Waitms(1);
			serialSend(res, PC);
			WAIT1_Waitms(1);
			serialSend(res, RasPi);
			WAIT1_Waitms(1);
			serialSend((val >> 8), PC);
			WAIT1_Waitms(1);
			serialSend((val >> 8), RasPi);
			WAIT1_Waitms(1);
			serialSend((val & 0xff), PC);
			WAIT1_Waitms(1);
			serialSend((val & 0xff), RasPi);
			WAIT1_Waitms(1);
		}
	}
}

void testServoBoard(void) {
	uint8_t res;

	/* init servo board */
	res = initServo();
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(1);

	/* set servos */
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, STRAIGHT);
		serialSend(i, PC);
		WAIT1_Waitms(1);
		serialSend(i, RasPi);
		WAIT1_Waitms(1);
		serialSend(res, PC);
		WAIT1_Waitms(1);
		serialSend(res, RasPi);
		WAIT1_Waitms(2000);
		res = setServo(i, SIDEWAYS);
		serialSend(res, PC);
		WAIT1_Waitms(1);
		serialSend(res, RasPi);
		WAIT1_Waitms(2000);
	}

	/* set brushless */
	res = setBrushless(BRUSHLESS_ON);
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(2000);
	res = setBrushless(BRUSHLESS_OFF);
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(1);
}

void testMotor(void) {
	uint8_t res;

	/* init motor */
	res = initMotor();
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(1);
	for (uint8_t i = 0; i < NUMBER_OF_MOTOR; i++) {
		res = setMotorDirection(i, MOTOR_FORWARD);
		serialSend(i, PC);
		WAIT1_Waitms(1);
		serialSend(i, RasPi);
		WAIT1_Waitms(1);
		serialSend(res, PC);
		WAIT1_Waitms(1);
		serialSend(res, RasPi);
		WAIT1_Waitms(1);
		res = setMotorSpeed(i, 0xFFFF);
		serialSend(res, PC);
		WAIT1_Waitms(1);
		serialSend(res, RasPi);
		WAIT1_Waitms(1);
	}
}
