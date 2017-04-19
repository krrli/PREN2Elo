#include "test.h"

void starttest(void) {
	/* exit if tests are not wanted */
	if (ENABLE_TEST == 0) {
		return;
	}

	/* wait */
	if (WAIT_BEFORE_TEST) {
		for (uint8_t i = 0; i < WAIT_MINUTES; i++) {
			WAIT1_Waitms(60000);
		}
		WAIT1_Waitms(10000);
	}

	/* test serial communication */
	if (TEST_SERIAL) {
		testSerial();
	}

	/* test tof sensors */
	if (TEST_TOF_SENSORS) {
		testTofSensors();
	}

	/* test tof sensors continuously */
	if (TEST_TOF_SENSORS_CONTINUOUS) {
		testTofSensorsContinuous();
	}

	/* test servo board */
	if (TEST_SERVO_BOARD) {
		testServoBoard();
	}

	/* test brushless and switch */
	if (TEST_BRUSHLESS_SWITCH) {
		testBrushlessSwitch();
	}

	if (SERVO_CALIB) {
		servoCalib();
	}

	/* test motor controller */
	if (TEST_MOTOR) {
		testMotor();
	}

	if (TEST_MOTOR_DIRECTION) {
		testMotorDirection(TEST_MOTOR_DIRECTION_MOTOR);
	}

	if (TEST_MOTOR_AND_SERVO) {
		testMotorAndServo();
	}

	/* end loop */
	for (;;){

	}
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
			//WAIT1_Waitms(1);
			serialSend(i, RasPi);
			//WAIT1_Waitms(1);
			serialSend(res, PC);
			//WAIT1_Waitms(1);
			serialSend(res, RasPi);
			//WAIT1_Waitms(1);
			serialSend((val >> 8), PC);
			//WAIT1_Waitms(1);
			serialSend((val >> 8), RasPi);
			//WAIT1_Waitms(1);
			serialSend((val & 0xff), PC);
			//WAIT1_Waitms(1);
			serialSend((val & 0xff), RasPi);
			//WAIT1_Waitms(1);
			//WAIT1_Waitms(10);
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

void testBrushlessSwitch(void) {
	/* local variables for brushless */
	uint8_t cent_switch, cent_switch_old = CENT_OFF;
	/* local variable to catch errors */
	uint8_t res;
	/* init servo board */
	res = initServo();
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(1);
	for (;;) {
		/* check centrifuge state */
		cent_switch = SW_Zent_GetVal();
		if (cent_switch != cent_switch_old) {
			if (cent_switch == CENT_ON) {
				res = setBrushless(BRUSHLESS_ON);
				serialSend(res, PC);
				WAIT1_Waitms(1);
				serialSend(res, RasPi);
				WAIT1_Waitms(1);
				cent_switch_old = cent_switch;
			} else {
				res = setBrushless(BRUSHLESS_OFF);
				serialSend(res, PC);
				WAIT1_Waitms(1);
				serialSend(res, RasPi);
				WAIT1_Waitms(1);
				cent_switch_old = cent_switch;
			}
		}
	}
}

void servoCalib(void) {
	initServo();
	WAIT1_Waitms(2000);
	//for (;;) {
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
			//WAIT1_Waitms(2000);
		}
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_SIDEWAYS);
			//WAIT1_Waitms(2000);
		}
		WAIT1_Waitms(2000);
	//}
	for (uint8_t i = 0; i < 4; i++) {
	 setServo(i, SERVO_STRAIGHT);
	 //WAIT1_Waitms(2000);
	 }
}

void testMotor(void) {
	uint8_t res;
	/* init motor */
	res = initMotor();
	serialSend(res, PC);
	WAIT1_Waitms(1);
	serialSend(res, RasPi);
	WAIT1_Waitms(1);
	WAIT1_Waitms(2000);
	for (;;) {
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
			res = setMotorSpeed(i, 100);
			serialSend(res, PC);
			WAIT1_Waitms(1);
			serialSend(res, RasPi);
			WAIT1_Waitms(1);
		}
		WAIT1_Waitms(10000);
		for (uint8_t i = 0; i < NUMBER_OF_MOTOR; i++) {
			res = setMotorDirection(i, MOTOR_BACKWARD);
			serialSend(i, PC);
			WAIT1_Waitms(1);
			serialSend(i, RasPi);
			WAIT1_Waitms(1);
			serialSend(res, PC);
			WAIT1_Waitms(1);
			serialSend(res, RasPi);
			WAIT1_Waitms(1);
			res = setMotorSpeed(i, 50);
			serialSend(res, PC);
			WAIT1_Waitms(1);
			serialSend(res, RasPi);
			WAIT1_Waitms(1);
		}
		WAIT1_Waitms(10000);
	}
}

void testMotorDirection(uint8_t motor) {
	initMotor();
	for (;;) {
		setMotorDirection(motor, MOTOR_FORWARD);
		setMotorSpeed(motor, MOTOR_MAXSPEED);
	}
}

void testMotorAndServo() {
	initServo();
	initMotor();
	for (;;) {
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
		}
		WAIT1_Waitms(1000);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
		setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
		setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
		setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
		setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
		WAIT1_Waitms(10000);
		setMotorSpeed(MOTOR_FRONT_LEFT, 0);
		setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
		setMotorSpeed(MOTOR_REAR_LEFT, 0);
		setMotorSpeed(MOTOR_REAR_RIGHT, 0);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_SIDEWAYS);
		}
		WAIT1_Waitms(1000);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
		setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
		setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
		setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
		setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
		WAIT1_Waitms(10000);
		setMotorSpeed(MOTOR_FRONT_LEFT, 0);
		setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
		setMotorSpeed(MOTOR_REAR_LEFT, 0);
		setMotorSpeed(MOTOR_REAR_RIGHT, 0);
	}
}
