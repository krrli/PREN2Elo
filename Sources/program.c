#include "program.h"

/*
 * global variables for serial communication
 */
volatile uint8_t lastSentCmd[NUMBER_OF_SERIAL_PORTS];

/*
 * global variables for main loop
 */
volatile enum parcoursState state;
volatile enum parcoursState stateBak;
volatile enum parcoursState stateCurr;
volatile enum wheelPosition wheelPos;
volatile enum parcourType type;
volatile enum parcourEnd endReached;
volatile enum driveDistance distance;

/*
 * global variables for new main loop
 */
volatile uint8_t cent_switch, cent_switch_old;
volatile uint8_t tof1, tof2, tof3, tof4, tof5;
volatile uint8_t parcour_state;
volatile uint8_t state0_initialized, state7_initialized, state8_initialized;
#if NEW_SERIAL_PAUSE_ENABLED
volatile uint8_t loop_paused;
#endif
volatile uint8_t state8_neg_drv_dir;

/*
 * global variables for second round
 */

uint8_t parcour_state2;

/*
 * pid vars
 */
int32_t diff, diff_old, P_diff, I_diff, D_diff, PID_diff, PID_minus;
int32_t diff_dist, diff_dist_old, P_diff_dist, I_diff_dist, D_diff_dist,
		PID_diff_dist, PID_minus_dist;

/*
 * pid both vars
 */

uint8_t reset_pid;

/*
 * global variables for button pressing
 */
volatile uint8_t button;
volatile enum buttonChecked btnchk;

void loop_pidReset() {
	diff = 0;
	I_diff = 0;
	diff_dist = 0;
	I_diff_dist = 0;
	reset_pid = 1;
}
void loop_initVars() {
	/* init variables for serial communication */
	lastSentCmd[PC] = 0x00;
	lastSentCmd[RasPi] = 0x00;

	/* init variables for main loop */
	state = STOPPED;
	stateBak = STOPPED;
	stateCurr = STOPPED;
	wheelPos = STRAIGHT;
	state = DRIVE_FORWARD; // todo
	endReached = NOT_REACHED;
	distance = CURVE_DIST;

	/* init variables for new main loop */
	parcour_state = 0;
	state0_initialized = 0;
	state7_initialized = 0;
	state8_initialized = 0;
	state8_neg_drv_dir = 0;
#if NEW_SERIAL_PAUSE_ENABLED
	loop_paused = 0;
#endif

	/* init vars for pid */
	loop_pidReset();

	/* init variables for buttons */
	button = BUTTON1;
	btnchk = BUTTON_UNCHECKED;
}
void loop_setServosStraight() {
	uint8_t res;
	res = setServo(0, SERVO_STRAIGHT);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	res = setServo(1, SERVO_STRAIGHT);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	res = setServo(2, SERVO_STRAIGHT);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	res = setServo(3, SERVO_STRAIGHT);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
}
void loop_setServosSideways() {
	uint8_t res;
	res = setServo(0, SERVO_SIDEWAYS);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	res = setServo(1, SERVO_SIDEWAYS);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	res = setServo(2, SERVO_SIDEWAYS);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	res = setServo(3, SERVO_SIDEWAYS);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
}
void loop_setMotorDirForward() {
	uint8_t res;
	res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorDirBackward() {
	uint8_t res;
	res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorDirLeft() {
	uint8_t res;
	res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorDirRight() {
	uint8_t res;
	res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorMaxSpeed() {
	uint8_t res;
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorHalfSpeed() {
	uint8_t res;
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_HALFSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_HALFSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_HALFSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_HALFSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorButtonSpeed() {
	uint8_t res;
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_BUTTON_SPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_BUTTON_SPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_BUTTON_SPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_BUTTON_SPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorButtonSpeed2() {
	uint8_t res;
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_BUTTON_SPEED_2);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_BUTTON_SPEED_2);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_BUTTON_SPEED_2);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_BUTTON_SPEED_2);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_setMotorStop() {
	uint8_t res;
	res = setMotorSpeed(MOTOR_FRONT_LEFT, 0);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, 0);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, 0);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
}
void loop_corrLeft(uint16_t delay) {
#if NEW_CORR_ENABLED
	uint8_t res;
#if PID_CORR_SET_SPEED
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SIMPLE
	if (delay >= PID_CORR_SIMPLE_MIN_PID_VAL) {
		res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_FRONT_LEFT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_LEFT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
	}
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_CORR_LEFT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	enum MotorDirection tmpdir, afterdir;
	switch (parcour_state) {
		case 2:
		tmpdir = MOTOR_BACKWARD;
		afterdir = MOTOR_FORWARD;
		break;
		case 6:
		tmpdir = MOTOR_FORWARD;
		afterdir = MOTOR_BACKWARD;
		break;
	}
	res = setMotorDirection(MOTOR_FRONT_LEFT, tmpdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, tmpdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
#if PID_CORR_SERVO_DIRECTION
	res = setServoPID(SERVO_STRAIGHT, 1, delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
#endif
#if (PID_CORR_DIRECTION || PID_CORR_SERVO || PID_CORR_SPEED)
	WAIT1_Waitms(delay);
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_STRAIGHT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	res = setMotorDirection(MOTOR_FRONT_LEFT, afterdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, afterdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
#endif
}
void loop_corrRight(uint16_t delay) {
#if NEW_CORR_ENABLED
	uint8_t res;
#if PID_CORR_SET_SPEED
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SIMPLE
	if (delay >= PID_CORR_SIMPLE_MIN_PID_VAL) {
		res = setMotorSpeed(MOTOR_FRONT_RIGHT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_RIGHT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
	}
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_CORR_RIGHT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	enum MotorDirection tmpdir, afterdir;
	switch (parcour_state) {
		case 2:
		tmpdir = MOTOR_BACKWARD;
		afterdir = MOTOR_FORWARD;
		break;
		case 6:
		tmpdir = MOTOR_FORWARD;
		afterdir = MOTOR_BACKWARD;
		break;
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, tmpdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, tmpdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
#if PID_CORR_SERVO_DIRECTION
	res = setServoPID(SERVO_STRAIGHT, 0, delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
#endif
#if (PID_CORR_DIRECTION || PID_CORR_SERVO || PID_CORR_SPEED)
	WAIT1_Waitms(delay);
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_STRAIGHT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	res = setMotorDirection(MOTOR_FRONT_RIGHT, afterdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, afterdir);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
#endif
}
void loop_corrFront(uint16_t delay) {
#if NEW_CORR_ENABLED
	uint8_t res;
#if PID_CORR_SET_SPEED
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SIMPLE
	if (delay >= PID_CORR_SIMPLE_MIN_PID_VAL) {
		res = setMotorSpeed(MOTOR_FRONT_RIGHT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_FRONT_LEFT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
	}
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_CORR_FRONT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	enum MotorDirection tmpdirleft, tmpdirright, afterdirleft,
	afterdirright;
	if (type == PARCOUR_A) {
		tmpdirleft = MOTOR_FORWARD;
		tmpdirright = MOTOR_BACKWARD;
		afterdirleft = MOTOR_BACKWARD;
		afterdirright = MOTOR_FORWARD;
	} else {
		tmpdirleft = MOTOR_BACKWARD;
		tmpdirright = MOTOR_FORWARD;
		afterdirleft = MOTOR_FORWARD;
		afterdirright = MOTOR_BACKWARD;
	}
	res = setMotorDirection(MOTOR_FRONT_LEFT, tmpdirleft);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, tmpdirright);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
#if PID_CORR_SERVO_DIRECTION
	res = setServoPID(SERVO_SIDEWAYS, 0, delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
#endif
#if (PID_CORR_DIRECTION || PID_CORR_SERVO || PID_CORR_SPEED)
	WAIT1_Waitms(delay);
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_SIDEWAYS);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	res = setMotorDirection(MOTOR_FRONT_LEFT, afterdirleft);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, afterdirright);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
#endif
}
void loop_corrRear(uint16_t delay) {
#if NEW_CORR_ENABLED
	uint8_t res;
#if PID_CORR_SET_SPEED
	res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED - delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SIMPLE
	if (delay >= PID_CORR_SIMPLE_MIN_PID_VAL) {
		res = setMotorSpeed(MOTOR_FRONT_RIGHT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_RIGHT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_FRONT_LEFT, NEW_MOTOR_MAXSPEED);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
		res = setMotorSpeed(MOTOR_REAR_LEFT,
				NEW_MOTOR_MAXSPEED - PID_CORR_SIMPLE_CORR_PERCENT);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
		}
	}
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_CORRSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_CORR_REAR);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	enum MotorDirection tmpdirleft, tmpdirright, afterdirleft,
	afterdirright;
	if (type == PARCOUR_A) {
		tmpdirleft = MOTOR_FORWARD;
		tmpdirright = MOTOR_BACKWARD;
		afterdirleft = MOTOR_BACKWARD;
		afterdirright = MOTOR_FORWARD;
	} else {
		tmpdirleft = MOTOR_BACKWARD;
		tmpdirright = MOTOR_FORWARD;
		afterdirleft = MOTOR_FORWARD;
		afterdirright = MOTOR_BACKWARD;
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, tmpdirleft);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, tmpdirright);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
#if PID_CORR_SERVO_DIRECTION
	res = setServoPID(SERVO_SIDEWAYS, 1, delay);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
#endif
#if (PID_CORR_DIRECTION || PID_CORR_SERVO || PID_CORR_SPEED)
	WAIT1_Waitms(delay);
#endif
#if PID_CORR_SPEED
	res = setMotorSpeed(MOTOR_REAR_RIGHT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
	res = setMotorSpeed(MOTOR_REAR_LEFT, NEW_MOTOR_MAXSPEED);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
	}
#endif
#if PID_CORR_SERVO
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_SIDEWAYS);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
#endif
#if PID_CORR_DIRECTION
	res = setMotorDirection(MOTOR_REAR_LEFT, afterdirleft);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, afterdirright);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
#endif
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
#endif
}
void loop_pidDiffCorr(uint16_t val_front, uint16_t val_back) {
	if (val_front == 0xFFFF || val_back == 0xFFFF) {
#if NEW_CORR_EXPERIMANTAL_ENABLED
		loop_setServosStraight();
#endif
		return;
	}
	diff_old = diff;
	diff = (int32_t) val_front - (int32_t) val_back;
	P_diff = diff;
	I_diff += diff;
	D_diff = diff - diff_old;
	PID_diff = (PID_P * P_diff) / PID_P_DIV + (PID_I * I_diff) / PID_I_DIV
			+ (PID_D * D_diff) / PID_D_DIV;
	if (PID_diff >= 0) {
		PID_minus = 0;
	} else {
		PID_minus = 1;
		PID_diff = 0 - PID_diff;
	}
	if (PID_diff > PID_MAX_CORR_TIME) {
		PID_diff = PID_MAX_CORR_TIME;
	}
	switch (parcour_state) {
	case 2:
		if ((type == PARCOUR_A && PID_minus == 0)
				|| (type == PARCOUR_B && PID_minus == 1)) {
			// corr left
			loop_corrLeft(PID_diff);
		} else {
			// corr right
			loop_corrRight(PID_diff);
		}
		break;
	case 4:
		if (PID_minus == 0) {
			// corr rear
			loop_corrRear(PID_diff);
		} else {
			// corr front
			loop_corrFront(PID_diff);
		}
		break;
	case 6:
		if ((type == PARCOUR_A && PID_minus == 0)
				|| (type == PARCOUR_B && PID_minus == 1)) {
			// corr right
			loop_corrRight(PID_diff);
		} else {
			// corr left
			loop_corrLeft(PID_diff);
		}
		break;
	}
}
void loop_pidDistCorr(uint16_t val) {
	if (val == 0xFFFF) {
#if NEW_CORR_EXPERIMANTAL_ENABLED
		loop_setServosStraight();
#endif
		return;
	}
	diff_dist_old = diff_dist;
	diff_dist = (int32_t) val - (int32_t) NEW_DIST_TO_WALL;
	P_diff_dist = diff_dist;
	I_diff_dist += diff_dist;
	D_diff_dist = diff_dist - diff_dist_old;
	PID_diff_dist = (PID_DIST_P * P_diff_dist) / PID_DIST_P_DIV
			+ (PID_DIST_I * I_diff_dist) / PID_DIST_I_DIV
			+ (PID_DIST_D * D_diff_dist) / PID_DIST_D_DIV;
	if (PID_diff_dist >= 0) {
		PID_minus_dist = 0;
	} else {
		PID_minus_dist = 1;
		PID_diff_dist = 0 - PID_diff_dist;
	}
	if (PID_diff_dist > PID_DIST_MAX_CORR_TIME) {
		PID_diff_dist = PID_DIST_MAX_CORR_TIME;
	}
	if ((type == PARCOUR_A && PID_minus_dist == 0)
			|| (type == PARCOUR_B && PID_minus_dist == 1)) {
		// corr_left
		loop_corrLeft(PID_diff_dist);
	} else {
		// corr_right
		loop_corrRight(PID_diff_dist);
	}
}
void loop_pidDoubleDistCorr(uint16_t val1, uint16_t val2) {
	uint16_t reg_val;
	if ((val1 != 0xffff) && (val2 != 0xffff)) {
		reg_val = (uint16_t) ((int32_t) NEW_DIST_TO_WALL
				+ (((int32_t) val1 - (int32_t) val2)) / 2);
		loop_pidDistCorr(reg_val);
	} else if (val1 != 0xffff) {
		loop_pidDistCorr(val1);
	} else if (val2 != 0xffff) {
		reg_val = (uint16_t) (2 * (int32_t) NEW_DIST_TO_WALL) - (int32_t) val2;
		loop_pidDistCorr(reg_val);
	} else {
#if NEW_CORR_EXPERIMANTAL_ENABLED
		loop_setServosStraight();
#endif
	}
}
void loop_pidBoth(uint16_t val_front, uint16_t val_rear) {
	static int32_t dist_err_old, diff_err_old, dist_I_err, diff_I_err;
	int32_t dist_err, diff_err, dist_D_err, diff_D_err, dist_pid_val,
			diff_pid_val;

	if (reset_pid) {
		reset_pid = 0;
		dist_err_old = 0;
		diff_err_old = 0;
		dist_I_err = 0;
		diff_I_err = 0;
	}

	if (val_front == 0xffff || val_rear == 0xffff) {
		loop_setServosStraight();
		return;
	}

	dist_err = (int32_t) val_front - (int32_t) NEW_DIST_TO_WALL;
	dist_I_err += dist_err;
	dist_D_err = dist_err - dist_err_old;
	dist_pid_val = ((int32_t) PID_BOTH_DIST_P_MULT * dist_err)
			/ (int32_t) PID_BOTH_DIST_P_DIV
			+ ((int32_t) PID_BOTH_DIST_I_MULT * dist_I_err)
					/ (int32_t) PID_BOTH_DIST_I_DIV
			+ ((int32_t) PID_BOTH_DIST_D_MULT * dist_D_err)
					/ (int32_t) PID_BOTH_DIST_D_DIV;
	dist_err_old = dist_err;

	if (dist_pid_val > PID_BOTH_MAX_CORR_VAL) {
		dist_pid_val = PID_BOTH_MAX_CORR_VAL;
	} else if ((0 - dist_pid_val) > PID_BOTH_MAX_CORR_VAL) {
		dist_pid_val = 0 - PID_BOTH_MAX_CORR_VAL;
	}

	diff_err = (int32_t) val_front - (int32_t) val_rear;
	diff_I_err += diff_err;
	diff_D_err = diff_err - diff_err_old;
	diff_pid_val = ((int32_t) PID_BOTH_DIFF_P_MULT * diff_err)
			/ (int32_t) PID_BOTH_DIFF_P_DIV
			+ ((int32_t) PID_BOTH_DIFF_I_MULT * diff_I_err)
					/ (int32_t) PID_BOTH_DIFF_I_DIV
			+ ((int32_t) PID_BOTH_DIFF_D_MULT * diff_D_err)
					/ (int32_t) PID_BOTH_DIFF_D_DIV;
	diff_err_old = diff_err;

	if (diff_pid_val > PID_BOTH_MAX_CORR_VAL) {
		diff_pid_val = PID_BOTH_MAX_CORR_VAL;
	} else if ((0 - diff_pid_val) > PID_BOTH_MAX_CORR_VAL) {
		diff_pid_val = 0 - PID_BOTH_MAX_CORR_VAL;
	}

	setServoPidBoth(dist_pid_val, diff_pid_val, type, parcour_state);
}

void start(void) {
	uint8_t res;

	cent_switch_old = CENT_OFF;

	loop_initVars();

	/* init motor */
	res = initMotor();
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_INIT_MOTOR);
	}

	/* init servoshield, servos, brushless */
	res = initServo();
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_INIT_SERVO);
	}

	/* init tof sensors */
	res = initToF();
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_INIT_TOF);
	}

	for (;;) {
#if NEW_MAIN_LOOP
		/* start new main loop */
		mainLoop2();
#else
		/* start mainloop */
		mainLoop();
#endif
		//cent_switch_old = CENT_OFF;
		loop_initVars();
	}

	for (;;) {
		/* fallback loop, should never be reached */
		serialDebugLite(DEBUG_ERROR_END_LOOP_REACHED);
	}
}

void serialRxInt(uint8_t ch, uint8_t port) {
#if NEW_SERIAL_INT_ENABLED==0
	return;
#endif
#if NEW_SERIAL_RASPI_ENABLED==0
	if (port == RasPi) {
		return;
	}
#endif
#if NEW_SERIAL_INT_DEBUG_ENABLED
	serialSend(0xee, PC);
	serialSend(port, PC);
	serialSend(ch, PC);
#endif
	switch (ch) {
	/* commands from raspi */
	case START:
		serialSend(ACKNOWLEDGE, port);
		if (state == STOPPED)
			state = DRIVE_FORWARD;
		if (parcour_state == 0) {
			parcour_state = 1;
		}
		break;
	case PAUSE:
		serialSend(ACKNOWLEDGE, port);
#if NEW_SERIAL_PAUSE_ENABLED
		stateBak = state;
		state = STOPPED;
		loop_paused = 1;
		loop_setMotorStop();
#endif
		break;
	case RESUME:
		serialSend(ACKNOWLEDGE, port);
#if NEW_SERIAL_PAUSE_ENABLED
		state = stateBak;
		if (loop_paused) {
			switch (parcour_state) {
				case 0:
				case 7:
				case 10:
				/* do nothing */
				break;
				case 8:
				loop_setMotorHalfSpeed();
				break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 9:
				loop_setMotorMaxSpeed();
			}
			loop_paused = 0;
		}
#endif
		break;

		/* answers from raspi */
	case ACKNOWLEDGE:
		break;
	case ERROR:
		serialSend(lastSentCmd[port], port);
		break;
	case BUTTON1:
	case BUTTON2:
	case BUTTON3:
	case BUTTON4:
	case BUTTON5:
		if (lastSentCmd[port] == ROMAN_NUMERAL_REQUEST || parcour_state == 7) {
			serialSend(ACKNOWLEDGE, port);
			button = ch;
			btnchk = BUTTON_CHECKED;
			parcour_state = 8;
		} else {
			serialSend(ERROR, port);
			break;
		}
		break;

		/* illegal commands from raspi */
	case ROMAN_NUMERAL_REQUEST:
	case CURVE:
	default:
		serialSend(ERROR, port);
	}
}

void serialSend(uint8_t ch, uint8_t port) {
	/* send char ch to port port */
	switch (port) {
	case PC:
		CLS1_SendChar(ch);
		break;
	case RasPi:
		CLS2_SendChar(ch);
		break;
	}

	/* save char ch as last sent command */
	lastSentCmd[port] = ch;
}

void serialDebugLite(uint8_t ch) {
	uint8_t res;
	uint16_t val;
	serialSend(ch, PC);
	if (ch == DEBUG_ERROR_GET_TOF_VALUE || ch == DEBUG_ERROR_SET_SERVO
			|| ch == DEBUG_ERROR_SET_BRUSHLESS) {
		serialSend(DEBUG_ERROR_REINIT_I2C, PC);
		GenI2C_ToF_Deinit();
		WAIT1_Waitms(10);
		GenI2C_ToF_Init();
		WAIT1_Waitms(10);
		if (PID_STOP_ON_I2C_ERROR && getToFValueMillimeters(0, &val) != ERR_OK) {
			loop_setMotorStop();
			serialSend(DEBUG_ERROR_STOPPING_BECAUSE_I2C_ERROR, PC);
			//for (;;);
		}
	} else if (ch == DEBUG_ERROR_INIT_MOTOR) {
		serialSend(DEBUG_TRY_INIT_MOTOR, PC);
		do {
			res = initMotor();
		} while (res != ERR_OK);
	} else if (ch == DEBUG_ERROR_INIT_SERVO || ch == DEBUG_ERROR_INIT_TOF) {
		serialSend(DEBUG_TRY_INIT_SERVO_AND_TOF, PC);
		GenI2C_ToF_Deinit();
		WAIT1_Waitms(5);
		GenI2C_ToF_Init();
		WAIT1_Waitms(5);
		do {
			res = initServo();
		} while (res != ERR_OK);
		do {
			res = initToF();
		} while (res != ERR_OK);
	} else if (ch == DEBUG_ERROR_SET_MOTOR_DIRECTION
			|| ch == DEBUG_ERROR_SET_MOTOR_SPEED) {
		serialSend(DEBUG_TRY_INIT_MOTOR, PC);
		//do {
		res = initMotor();
		//} while (res != ERR_OK);
	}
}

void mainLoop(void) {
#if NEW_MAIN_LOOP == 0
	/* local variables for brushless */
	uint8_t cent_switch, cent_switch_old = CENT_OFF;
	/* local variables for tof sensors */
	uint8_t tof1_tmp, tof2_tmp;
	uint16_t tof1_tmp_val, tof2_tmp_val;
	int32_t tof_diff;
	/* local variable to catch errors */
	uint8_t res;

	for (;;) {
		/* check centrifuge state */
		/*cent_switch = SW_Zent_GetVal();
		 if (cent_switch != cent_switch_old) {
		 if (cent_switch == CENT_ON) {
		 res = setBrushless(BRUSHLESS_ON);
		 if (res != ERR_OK) {
		 serialDebugLite(DEBUG_ERROR_SET_BRUSHLESS);
		 }
		 cent_switch_old = cent_switch;
		 } else {
		 res = setBrushless(BRUSHLESS_OFF);
		 if (res != ERR_OK) {
		 serialDebugLite(DEBUG_ERROR_SET_BRUSHLESS);
		 }
		 cent_switch_old = cent_switch;
		 }
		 }*/

		/* if state changed, set servo and motor outputs */
		if (stateCurr != state) {
			switch (state) {
				case STOPPED:
				/* stop */
				res = setMotorSpeed(MOTOR_FRONT_LEFT, 0);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_REAR_LEFT, 0);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_REAR_RIGHT, 0);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				WAIT1_Waitms(WAIT_TIME_DEFAULT);
				break;
				case DRIVE_FORWARD:
				case DRIVE_BACKWARD:
				/* Stop Motors before turning */
				/*res = setMotorSpeed(MOTOR_FRONT_LEFT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 res = setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 res = setMotorSpeed(MOTOR_REAR_LEFT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 res = setMotorSpeed(MOTOR_REAR_RIGHT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 WAIT1_Waitms(WAIT_TIME_DEFAULT);*/
				/* set servos */
				if (wheelPos != STRAIGHT) {
					res = setServo(0, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					res = setServo(1, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					res = setServo(2, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					res = setServo(3, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					wheelPos = STRAIGHT;
					WAIT1_Waitms(WAIT_TIME_SERVO);
				}

				/* set motors */
				if (state == DRIVE_FORWARD) {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
				} else {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
				}
				WAIT1_Waitms(WAIT_TIME_DEFAULT);
				res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				WAIT1_Waitms(WAIT_TIME_DEFAULT);

				/* define used tof sensors */
				if (type == PARCOUR_A) {
					tof1_tmp = TOF_LEFT_REAR;
					tof2_tmp = TOF_RIGHT_FRONT;
				} else {
					tof1_tmp = TOF_RIGHT_REAR;
					tof2_tmp = TOF_LEFT_FRONT;
				}

				/* drive blind first */
				WAIT1_Waitms(BLIND_TIME);
				break;
				case DRIVE_LEFT:
				case DRIVE_RIGHT:
				/* Stop Motors before turning */
				/*res = setMotorSpeed(MOTOR_FRONT_LEFT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 res = setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 res = setMotorSpeed(MOTOR_REAR_LEFT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 res = setMotorSpeed(MOTOR_REAR_RIGHT, 0);
				 if (res != ERR_OK) {
				 serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				 }
				 WAIT1_Waitms(WAIT_TIME_DEFAULT);*/
				/* set servo */
				if (wheelPos != SIDEWAYS) {
					res = setServo(0, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					res = setServo(1, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					res = setServo(2, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					res = setServo(3, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
					wheelPos = SIDEWAYS;
					WAIT1_Waitms(WAIT_TIME_SERVO);
				}

				/* set motor */
				if (state == DRIVE_LEFT) {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
				} else {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
					}
				}
				WAIT1_Waitms(WAIT_TIME_DEFAULT);
				res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
				}
				WAIT1_Waitms(WAIT_TIME_DEFAULT);

				/* set distance */
				if (endReached == NOT_REACHED) {
					/* curve */
					distance = CURVE_DIST;
				} else {
					/* button pressing */
					/* check if button checked, else ask raspi */
					while (btnchk == BUTTON_UNCHECKED) {
						serialSend(ROMAN_NUMERAL_REQUEST, PC);
						//WAIT1_Waitms(1);
						serialSend(ROMAN_NUMERAL_REQUEST, RasPi);
						WAIT1_Waitms(WAIT_TIME_SERIAL_LOOP);
					}
					/* set drive distance for button */
					if (type == PARCOUR_A) {
						/* Parcour A */
						/* press button */
						switch (button) {
							case BUTTON1:
							distance = BUTTON1_A;
							break;
							case BUTTON2:
							distance = BUTTON2_A;
							break;
							case BUTTON3:
							distance = BUTTON3_A;
							break;
							case BUTTON4:
							distance = BUTTON4_A;
							break;
							case BUTTON5:
							distance = BUTTON5_A;
							break;
							default:
							serialDebugLite(DEBUG_ERROR_WRONG_BUTTON_NUMBER);
						}
					} else {
						/* Parcour B */
						/* press button */
						switch (button) {
							case BUTTON1:
							distance = BUTTON1_B;
							break;
							case BUTTON2:
							distance = BUTTON2_B;
							break;
							case BUTTON3:
							distance = BUTTON3_B;
							break;
							case BUTTON4:
							distance = BUTTON4_B;
							break;
							case BUTTON5:
							distance = BUTTON5_B;
							break;
							default:
							serialDebugLite(DEBUG_ERROR_WRONG_BUTTON_NUMBER);
						}
					}
				}

				if (type == PARCOUR_A) {
					/* parcour a */
					tof1_tmp = TOF_LEFT_FRONT;
					tof2_tmp = TOF_LEFT_REAR;
				} else {
					/* parcour b */
					tof1_tmp = TOF_RIGHT_FRONT;
					tof2_tmp = TOF_RIGHT_REAR;
				}
				break;
			}
			stateCurr = state;

			/* if state did not change */
		} else {
			switch (state) {
				case STOPPED:
				/* do nothing */
				break;
				case DRIVE_BACKWARD:
				if (endReached == REACHED) {
					/* driving into button */
					WAIT1_Waitms(DRIVE_INTO_BUTTON_TIME);
					state = STOPPED;
					break;
				}
				case DRIVE_FORWARD:
				/* drive straight */
				res = getToFValueMillimeters(tof1_tmp, &tof1_tmp_val);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
				}
				res = getToFValueMillimeters(tof2_tmp, &tof2_tmp_val);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
				}
				if (CORR_ENABLED) {
					if ((tof1_tmp_val
									> (DISTANCE_TO_WALL + DISTANCE_TO_WALL_VAR))
							&& (tof1_tmp_val != 0xffff)) {
						/* to far from wall */
						if (type == PARCOUR_A) {
							/* parcour a */
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						} else {
							/* parcour b */
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						}
					} else if (tof1_tmp_val
							< (DISTANCE_TO_WALL - DISTANCE_TO_WALL_VAR)) {
						/* to near to wall */
						if (type == PARCOUR_B) {
							/* parcour b */
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						} else {
							/* parcour a */
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						}
					}
				}

				/* detect end */
				if (state == DRIVE_FORWARD) {
					/* drive forward */
					if ((tof1_tmp_val == 0xffff) && (tof2_tmp_val == 0xffff)) {
						/* curve reached */
						WAIT1_Waitms(CURVE_DRIVE_OVER_TIME);
						if (type == PARCOUR_A) {
							state = DRIVE_LEFT;
						} else {
							state = DRIVE_RIGHT;
						}
						serialSend(CURVE, PC);
						//WAIT1_Waitms(1);
						serialSend(CURVE, RasPi);
						//WAIT1_Waitms(1);
					}
				} else {
					/* drive backward */
					if (tof2_tmp_val > 250) {
						/* end reached */
						WAIT1_Waitms(END_DRIVE_OVER_TIME);
						if (type == PARCOUR_A) {
							state = DRIVE_RIGHT;
						} else {
							state = DRIVE_LEFT;
						}
						endReached = REACHED;
						serialSend(ROMAN_NUMERAL_REQUEST, PC);
						//WAIT1_Waitms(1);
						serialSend(ROMAN_NUMERAL_REQUEST, RasPi);
						WAIT1_Waitms(WAIT_TIME_SERIAL_ANSWER);
					}
				}
				break;
				case DRIVE_LEFT:
				case DRIVE_RIGHT:
				/* drive straight */
				res = getToFValueMillimeters(tof1_tmp, &tof1_tmp_val);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
				}
				res = getToFValueMillimeters(tof2_tmp, &tof2_tmp_val);
				if (res != ERR_OK) {
					serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
				}
				tof_diff = (int32_t) tof1_tmp_val - (int32_t) tof2_tmp_val; // front - rear
				if (CORR_ENABLED) {
					if (((type == PARCOUR_A) && (state == DRIVE_LEFT))
							|| ((type == PARCOUR_B) && (state == DRIVE_RIGHT))) {
						/* drive towards wall */
						if (tof_diff > DRIVE_SIDEWAYS_VAR) {
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						} else if (tof_diff < (0 - DRIVE_SIDEWAYS_VAR)) {
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						}
					} else {
						/* drive away from wall */
						if (tof_diff > DRIVE_SIDEWAYS_VAR) {
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_FRONT_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_FRONT_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						} else if (tof_diff < (0 - DRIVE_SIDEWAYS_VAR)) {
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_CORRSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							WAIT1_Waitms(CORR_TIME);
							res = setMotorSpeed(MOTOR_REAR_LEFT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
							res = setMotorSpeed(MOTOR_REAR_RIGHT,
									MOTOR_MAXSPEED);
							if (res != ERR_OK) {
								serialDebugLite(DEBUG_ERROR_SET_MOTOR_SPEED);
							}
						}
					}
				}

				/* detect end via fixed distance */
				if (((type == PARCOUR_A) && (state == DRIVE_LEFT))
						|| ((type == PARCOUR_B) && (state == DRIVE_RIGHT))) {
					/* drive towards wall */
					if (tof1_tmp_val <= distance) {
						state = DRIVE_BACKWARD;
					}
				} else {
					/* drive away from wall */
					if (tof1_tmp_val >= distance) {
						state = DRIVE_BACKWARD;
					}
				}
				break;
			}
		}
		/* give some time until next run */
		//WAIT1_Waitms(10);
	}
#endif
}

void loop_secondRound() {
	uint8_t res;
	uint16_t tof1_val, tof2_val, tof3_val, tof4_val;
	int32_t diff;
	serialSend(SECOND_ROUND, RasPi);
	WAIT1_Waitms(WAIT_TIME_DEFAULT);
	serialSend(SECOND_ROUND, PC);
	WAIT1_Waitms(WAIT_TIME_DEFAULT);
	parcour_state2 = 0;
	/* disable brushless */
	setBrushless(BRUSHLESS_OFF);
	WAIT1_Waitms(4000);
	/* set servo dir */
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_CIRCLE);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
	/* set motor dir */
	res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
	/* turn arround */
	loop_setMotorHalfSpeed();
	WAIT1_Waitms(NEW_SECOND_ROUND_TURN_TIME);
	loop_setMotorStop();
	/* drive to start field */
	loop_setServosStraight();
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
	loop_setMotorDirBackward();
	loop_setMotorHalfSpeed();
	WAIT1_Waitms(NEW_SECOND_ROUND_DRIVE_TO_START_TIME);
	loop_setMotorStop();
	/* set servo dir */
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_CIRCLE);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
	/* set motor dir */
	res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_MOTOR_DIRECTION);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
	/* turn arround */
	loop_setMotorHalfSpeed();
	WAIT1_Waitms(NEW_SECOND_ROUND_TURN_TIME);
	loop_setMotorStop();
	/* start second round */
	for (;;) {
		switch (parcour_state2) {
		case 0:
			loop_setServosStraight();
			WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
			loop_setMotorDirForward();
			loop_setMotorHalfSpeed();
			WAIT1_Waitms(BLIND_TIME);
			parcour_state2 = 1;
			parcour_state = 2;
			loop_pidReset();
			break;
		case 1:
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof4, &tof4_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
#if NEW_CURVE_DETECT_TOF4_ENABLED
			if (tof2_val >= NEW_CURVE_DETECT_DISTANCE
					&& tof4_val >= NEW_CURVE_DETECT_DISTANCE) {
#else
				if (tof2_val >= NEW_CURVE_DETECT_DISTANCE) {
#endif
				parcour_state2 = 2;
				WAIT1_Waitms(4 * NEW_CURVE_DRIVE_OVER_TIME);
				break;
			}
			//loop_pidDistCorr(tof2_val);
			loop_pidBoth(tof1_val, tof2_val);
			break;
		case 2:
			loop_setMotorStop();
			serialSend(CURVE, RasPi);
			WAIT1_Waitms(WAIT_TIME_DEFAULT);
			serialSend(CURVE, PC);
			WAIT1_Waitms(WAIT_TIME_DEFAULT);
			loop_setServosSideways();
			WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
			if (type == PARCOUR_A) {
				loop_setMotorDirLeft();
			} else {
				loop_setMotorDirRight();
			}
			loop_setMotorHalfSpeed();
			WAIT1_Waitms(NEW_CURVE_BLIND_TIME);
			parcour_state2 = 3;
			parcour_state = 4;
			loop_pidReset();
			break;
		case 3:
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			if (tof2_val < NEW_CURVE_DIST) {
				parcour_state2 = 4;
				break;
			}
			loop_pidDiffCorr(tof1_val, tof2_val);
			break;
		case 4:
			loop_setMotorStop();
			loop_setServosStraight();
			WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
			loop_setMotorDirBackward();
			loop_setMotorHalfSpeed();
			WAIT1_Waitms(NEW_BLIND_TIME_BACK);
			parcour_state2 = 5;
			parcour_state = 6;
			loop_pidReset();
			break;
		case 5:
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof3, &tof3_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof4, &tof4_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			if (tof3_val < NEW_DIST_END && tof4_val == 0xffff) {
				parcour_state2 = 6;
				break;
			}
			//loop_pidDistCorr(tof2_val);
			loop_pidBoth(tof1_val, tof2_val);
			break;
		case 6:
			parcour_state = 7;
			return;
		}
	}
}

void mainLoop2(void) {
#if NEW_MAIN_LOOP
	/* local variables for tof sensors */
	uint16_t tof1_val, tof2_val, tof3_val, tof4_val, tof5_val;
	int32_t diff;
	uint16_t button_dist_val;
	/* local variable to catch errors */
	uint8_t res;

	for (;;) {
#if NEW_SERIAL_PAUSE_ENABLED
		while (loop_paused) {
			WAIT1_Waitms(10);
		}
#endif

		/* check centrifuge state */
		if (parcour_state == 0) {
			//cent_switch = CENT_ON;
			cent_switch = SW_Zent_GetVal();
			if (cent_switch != cent_switch_old) {
				if (cent_switch == CENT_ON) {
#if NEW_CENT_ENABLED
					res = setBrushless(BRUSHLESS_ON);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_BRUSHLESS);
					}
#endif
					cent_switch_old = cent_switch;
				} else {
#if NEW_CENT_ENABLED
					res = setBrushless(BRUSHLESS_OFF);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_BRUSHLESS);
					}
#endif
					cent_switch_old = cent_switch;
				}
			}
		}

		switch (parcour_state) {
		case 0: /* wait for start signal */
			if (state0_initialized == 0) {
				loop_setServosStraight();
				loop_setMotorDirForward();
				loop_setMotorStop();
				state0_initialized = 1;
			}
#if NEW_SERIAL_INT_ENABLED == 0
			WAIT1_Waitms(1000);
			parcour_state = 1;
#endif
			break;
		case 1: /* drive blind */
			/* get parcour type */
			type = SW_Parc_GetVal();
			//type = PARCOUR_B; // todo
			if (type == PARCOUR_A) {
				tof1 = TOF_LEFT_FRONT;
				tof2 = TOF_LEFT_REAR;
				tof3 = TOF_REAR;
				tof4 = TOF_RIGHT_REAR;
				tof5 = TOF_RIGHT_FRONT;
			} else {
				tof1 = TOF_RIGHT_FRONT;
				tof2 = TOF_RIGHT_REAR;
				tof3 = TOF_REAR;
				tof4 = TOF_LEFT_REAR;
				tof5 = TOF_LEFT_FRONT;
			}

#if NEW_CENT_WITHOUT_SWITCH_ENABLED
			setBrushless(BRUSHLESS_ON);
			WAIT1_Waitms(2000);
#endif
			loop_setMotorMaxSpeed();
#if NEW_SERIAL_PAUSE_ENABLED
			for (uint8_t i = 0; i < 10; i++) {
				while (loop_paused) {
					WAIT1_Waitms(10);
				}
				WAIT1_Waitms(NEW_BLIND_TIME / 10);
			}
#else
			WAIT1_Waitms(NEW_BLIND_TIME);
#endif
			loop_pidReset();
			parcour_state = 2;
			break;
		case 2: /* drive forward with corr */
			/* get tof values */
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof4, &tof4_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof5, &tof5_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			/* get tof diff */
			diff = tof1_val - tof2_val;
			/* check if curve reached */
#if NEW_CURVE_DETECT_TOF4_ENABLED
			if (tof2_val >= NEW_CURVE_DETECT_DISTANCE
					&& tof4_val >= NEW_CURVE_DETECT_DISTANCE) { // todo: can tof4 be ignored?
#else
			if (tof2_val >= NEW_CURVE_DETECT_DISTANCE) {
#endif
				parcour_state = 3;
				WAIT1_Waitms(NEW_CURVE_DRIVE_OVER_TIME);
				break;
			}
			/* drive straight */
#if NEW_DIFF_CORR_ENABLED
			/*if (tof1_val != 0xFFFF && tof2_val != 0xFFFF) {
			 if (diff < (0 - NEW_DIFF_MAX)) {
			 if (type == PARCOUR_A) {
			 loop_corrRight();
			 } else {
			 loop_corrLeft();
			 }
			 } else if (diff > NEW_DIFF_MAX) {
			 if (type == PARCOUR_A) {
			 loop_corrLeft();
			 } else {
			 loop_corrRight();
			 }
			 }
			 }*/
			loop_pidDiffCorr(tof1_val, tof2_val);
#endif
			/* check distance to wall */
#if NEW_DIST_CORR_ENABLED
			/*if (tof2_val < NEW_DIST_TO_WALL_MIN) {
			 if (type == PARCOUR_A) {
			 loop_corrRight();
			 } else {
			 loop_corrLeft();
			 }
			 }
			 if (tof2_val > NEW_DIST_TO_WALL_MAX && tof2_val < 0xFFFF) {
			 if (type == PARCOUR_A) {
			 loop_corrLeft();
			 } else {
			 loop_corrRight();
			 }
			 }*/
			loop_pidDistCorr(tof2_val);
#endif
#if NEW_DOUBLE_DIST_CORR_ENABLED
			loop_pidDoubleDistCorr(tof2_val, tof4_val);
#endif
#if NEW_BOTH_CORR_ENABLED
			if (tof1_val < NEW_CURVE_DETECT_DISTANCE
					|| tof5_val < NEW_CURVE_DETECT_DISTANCE) { // todo
				loop_pidBoth(tof1_val, tof2_val);
			} else {
				loop_setServosStraight();
			}
#endif
			break;
		case 3: /* drive sideways blind */
			loop_setMotorStop();
#if NEW_CENT_WITHOUT_SWITCH_ENABLED
			setBrushless(BRUSHLESS_OFF);
			WAIT1_Waitms(4000);
#endif
			loop_setServosSideways();
			if (type == PARCOUR_A) {
				loop_setMotorDirLeft();
			} else {
				loop_setMotorDirRight();
			}
			loop_setMotorMaxSpeed();
			serialSend(CURVE, RasPi);
			serialSend(CURVE, PC);
			WAIT1_Waitms(NEW_CURVE_BLIND_TIME);
			loop_pidReset();
			parcour_state = 4;
			break;
		case 4: /* drive sideways with corr */
			/* get tof values */
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			/* get tof diff */
			diff = tof1_val - tof2_val;
			/* check if curve end dist is reached */
			if (tof2_val < NEW_CURVE_DIST) {
				parcour_state = 5;
				break;
			}
			/* drive straight */
#if NEW_CURVE_CORR_ENABLED
			/*if (diff < (0 - NEW_DIFF_MAX)) {
			 loop_corrFront();
			 } else if (diff > NEW_DIFF_MAX) {
			 loop_corrRear();
			 }*/
			loop_pidDiffCorr(tof1_val, tof2_val);
#endif
			break;
		case 5: /* drive backwards blind */
			loop_setMotorStop();
			loop_setServosStraight();
			loop_setMotorDirBackward();
			loop_setMotorMaxSpeed();
#if NEW_SERIAL_PAUSE_ENABLED
			for (uint8_t i = 0; i < 10; i++) {
				while (loop_paused) {
					WAIT1_Waitms(10);
				}
				WAIT1_Waitms(NEW_BLIND_TIME_BACK / 10);
			}
#else
			WAIT1_Waitms(NEW_BLIND_TIME);
#endif
			loop_pidReset();
			parcour_state = 6;
			break;
		case 6: /* drive backwards with corr */
#if NEW_CENT_WITHOUT_SWITCH_ENABLED
			WAIT1_Waitms(1000);
			setBrushless(BRUSHLESS_ON);
#endif
			/* get tof values */
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof3, &tof3_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof4, &tof4_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			/* get tof diff */
			diff = tof1_val - tof2_val;
			/* check if end reached */
			if (tof3_val < NEW_DIST_END && tof4_val >= NEW_CURVE_DETECT_DISTANCE) {
				parcour_state = 7;
				break;
			}
#if NEW_DIFF_CORR_ENABLED
			/*if (tof1_val != 0xFFFF && tof2_val != 0xFFFF) {
			 if (diff < (0 - NEW_DIFF_MAX)) {
			 if (type == PARCOUR_A) {
			 loop_corrLeft();
			 } else {
			 loop_corrRight();
			 }
			 } else if (diff > NEW_DIFF_MAX) {
			 if (type == PARCOUR_A) {
			 loop_corrRight();
			 } else {
			 loop_corrLeft();
			 }
			 }
			 }*/
			loop_pidDiffCorr(tof1_val, tof2_val);
#endif
#if NEW_DIST_CORR_ENABLED
			/*if (tof2_val < NEW_DIST_TO_WALL_MIN) {
			 if (type == PARCOUR_A) {
			 loop_corrRight();
			 } else {
			 loop_corrLeft();
			 }
			 }
			 if (tof2_val > NEW_DIST_TO_WALL_MAX && tof2_val < 0xFFFF) {
			 if (type == PARCOUR_A) {
			 loop_corrLeft();
			 } else {
			 loop_corrRight();
			 }
			 }*/
			loop_pidDistCorr(tof2_val);
#endif
#if NEW_DOUBLE_DIST_CORR_ENABLED
			loop_pidDoubleDistCorr(tof2_val, tof4_val);
#endif
#if NEW_BOTH_CORR_ENABLED
			loop_pidBoth(tof1_val, tof2_val);
#endif
			break;
		case 7: /* stop, get roman number */
			if (state7_initialized == 0) {
				loop_setMotorStop();
#if NEW_SECOND_ROUND_ENABLED
				// todo: check, if dist to wall big enough
				loop_secondRound();
				loop_setMotorStop();
#endif
				loop_setServosSideways();
				if (type == PARCOUR_A) {
					loop_setMotorDirRight();
				} else {
					loop_setMotorDirLeft();
				}
				setBrushless(BRUSHLESS_OFF);
				WAIT1_Waitms(4000);
				serialSend(ROMAN_NUMERAL_REQUEST, RasPi);
				serialSend(ROMAN_NUMERAL_REQUEST, PC);
				state7_initialized = 1;
#if NEW_SERIAL_INT_ENABLED==0
				WAIT1_Waitms(1000);
				parcour_state = 8;
#endif
			}
			break;
		case 8: /* drive sideways for button pressing */
			/* get tof value */
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			/* start motors and get button dist */
			if (state8_initialized == 0) {
				switch (button) {
				case BUTTON1:
					if (type == PARCOUR_A) {
						button_dist_val = NEW_BUTTON1_A;
					} else {
						button_dist_val = NEW_BUTTON1_B;
					}
					break;
				case BUTTON2:
					if (type == PARCOUR_A) {
						button_dist_val = NEW_BUTTON2_A;
					} else {
						button_dist_val = NEW_BUTTON2_B;
					}
					break;
				case BUTTON3:
					if (type == PARCOUR_A) {
						button_dist_val = NEW_BUTTON3_A;
					} else {
						button_dist_val = NEW_BUTTON3_B;
					}
					break;
				case BUTTON4:
					if (type == PARCOUR_A) {
						button_dist_val = NEW_BUTTON4_A;
					} else {
						button_dist_val = NEW_BUTTON4_B;
					}
					break;
				case BUTTON5:
					if (type == PARCOUR_A) {
						button_dist_val = NEW_BUTTON5_A;
					} else {
						button_dist_val = NEW_BUTTON5_B;
					}
					break;
				}
				if (button_dist_val < tof2_val) {
					if (type == PARCOUR_A) {
						loop_setMotorDirLeft();
					} else {
						loop_setMotorDirRight();
					}
					state8_neg_drv_dir = 1;
				}
				loop_setMotorButtonSpeed();
				state8_initialized = 1;
			}
			if (state8_neg_drv_dir) {
				if (tof2_val <= button_dist_val) {
					loop_setMotorStop();
					parcour_state = 9;
					break;
				}
			} else {
				if (tof2_val >= button_dist_val) {
					loop_setMotorStop();
					parcour_state = 9;
					break;
				}
			}
			break;
		case 9: /* drive into button */
			loop_setServosStraight();
			loop_setMotorDirBackward();
			loop_setMotorButtonSpeed2();
			WAIT1_Waitms(NEW_DRIVE_INTO_BUTTON_TIME);
			loop_setMotorStop();
			parcour_state = 10;
			break;
		case 10:
			// todo: do sth. stupid
			return;
			break;
		}
	}
}
#endif
