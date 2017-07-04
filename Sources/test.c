#include "test.h"

#if TEST_SET_PID_VALUES
/* set pid vars */
volatile uint8_t pid_dist_p_mult, pid_dist_p_div, pid_dist_i_mult,
pid_dist_i_div, pid_dist_d_mult, pid_dist_d_div;
volatile uint8_t pid_diff_p_mult, pid_diff_p_div, pid_diff_i_mult,
pid_diff_i_div, pid_diff_d_mult, pid_diff_d_div;
volatile uint8_t pid_set_val_mode;
volatile uint8_t tmp_val;
uint8_t tof1, tof2, tof4, tof5;
uint16_t tof1_val, tof2_val, tof4_val, tof5_val;
uint8_t reset_pid, parcours_state;
enum parcourType type;
#endif

#if TEST_SET_BUTTON_DIST
uint8_t tof1, tof2;
uint16_t tof1_val, tof2_val;
uint8_t state8_neg_drv_dir;
volatile uint16_t button_dist_val, tmp_val;
volatile enum parcourType type;
#endif

uint8_t testSerialInt(uint8_t ch) {
#if ENABLE_TEST
#if TEST_SET_PID_VALUES
	switch (ch) {
		case 'p': // pid dist
		pid_set_val_mode = 1;
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('p', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend('s', PC);
		WAIT1_Waitms(1);
		serialSend('t', PC);
		WAIT1_Waitms(1);
		serialSend(':', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend(pid_dist_p_div / 100 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_dist_p_div % 100) / 10 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_dist_p_div % 10) + 48, PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case 'i':
		pid_set_val_mode = 2;
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend('s', PC);
		WAIT1_Waitms(1);
		serialSend('t', PC);
		WAIT1_Waitms(1);
		serialSend(':', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend(pid_dist_i_div / 100 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_dist_i_div % 100) / 10 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_dist_i_div % 10) + 48, PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case 'd':
		pid_set_val_mode = 3;
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend('s', PC);
		WAIT1_Waitms(1);
		serialSend('t', PC);
		WAIT1_Waitms(1);
		serialSend(':', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend(pid_dist_d_div / 100 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_dist_d_div % 100) / 10 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_dist_d_div % 10) + 48, PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case 'P':// pid diff
		pid_set_val_mode = 4;
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('p', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend('f', PC);
		WAIT1_Waitms(1);
		serialSend('f', PC);
		WAIT1_Waitms(1);
		serialSend(':', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend(pid_diff_p_div / 100 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_diff_p_div % 100) / 10 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_diff_p_div % 10) + 48, PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case 'I':
		pid_set_val_mode = 5;
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend('f', PC);
		WAIT1_Waitms(1);
		serialSend('f', PC);
		WAIT1_Waitms(1);
		serialSend(':', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend(pid_diff_i_div / 100 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_diff_i_div % 100) / 10 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_diff_i_div % 10) + 48, PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case 'D':
		pid_set_val_mode = 6;
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend('d', PC);
		WAIT1_Waitms(1);
		serialSend('i', PC);
		WAIT1_Waitms(1);
		serialSend('f', PC);
		WAIT1_Waitms(1);
		serialSend('f', PC);
		WAIT1_Waitms(1);
		serialSend(':', PC);
		WAIT1_Waitms(1);
		serialSend(' ', PC);
		WAIT1_Waitms(1);
		serialSend(pid_diff_d_div / 100 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_diff_d_div % 100) / 10 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((pid_diff_d_div % 10) + 48, PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case 'r':
		pid_set_val_mode = 0;
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('r', PC);
		WAIT1_Waitms(1);
		serialSend('e', PC);
		WAIT1_Waitms(1);
		serialSend('s', PC);
		WAIT1_Waitms(1);
		serialSend('e', PC);
		WAIT1_Waitms(1);
		serialSend('t', PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		tmp_val = (tmp_val * 10) + (ch - 48);
		break;
		case 's':
		switch (pid_set_val_mode) {
			case 1:
			pid_dist_p_div = tmp_val;
			break;
			case 2:
			pid_dist_i_div = tmp_val;
			break;
			case 3:
			pid_dist_d_div = tmp_val;
			break;
			case 4:
			pid_diff_p_div = tmp_val;
			break;
			case 5:
			pid_diff_i_div = tmp_val;
			break;
			case 6:
			pid_diff_d_div = tmp_val;
			break;
		}
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend(tmp_val / 100 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((tmp_val % 100) / 10 + 48, PC);
		WAIT1_Waitms(1);
		serialSend((tmp_val % 10) + 48, PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		tmp_val = 0;
		break;
	}
	return 1;
#endif
#if TEST_SET_BUTTON_DIST
	switch (ch) {
		case 'r':
		tmp_val = 0;
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		serialSend('r', PC);
		WAIT1_Waitms(1);
		serialSend('e', PC);
		WAIT1_Waitms(1);
		serialSend('s', PC);
		WAIT1_Waitms(1);
		serialSend('e', PC);
		WAIT1_Waitms(1);
		serialSend('t', PC);
		WAIT1_Waitms(1);
		serialSend('\r', PC);
		WAIT1_Waitms(1);
		serialSend('\n', PC);
		WAIT1_Waitms(1);
		break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		tmp_val = (tmp_val * 10) + (ch - 48);
		break;
		case 's':
		if (tmp_val > 0 && tmp_val < 400) {
			button_dist_val = tmp_val;
			serialSend('\r', PC);
			WAIT1_Waitms(1);
			serialSend('\n', PC);
			WAIT1_Waitms(1);
			serialSend(tmp_val / 100 + 48, PC);
			WAIT1_Waitms(1);
			serialSend((tmp_val % 100) / 10 + 48, PC);
			WAIT1_Waitms(1);
			serialSend((tmp_val % 10) + 48, PC);
			WAIT1_Waitms(1);
			serialSend('\r', PC);
			WAIT1_Waitms(1);
			serialSend('\n', PC);
			WAIT1_Waitms(1);
		} else {
			serialSend('\r', PC);
			WAIT1_Waitms(1);
			serialSend('\n', PC);
			WAIT1_Waitms(1);
			serialSend('e', PC);
			WAIT1_Waitms(1);
			serialSend('r', PC);
			WAIT1_Waitms(1);
			serialSend('r', PC);
			WAIT1_Waitms(1);
			serialSend('o', PC);
			WAIT1_Waitms(1);
			serialSend('r', PC);
			WAIT1_Waitms(1);
			serialSend('\r', PC);
			WAIT1_Waitms(1);
			serialSend('\n', PC);
			WAIT1_Waitms(1);
		}
		tmp_val = 0;
		break;
	}
	return 1;
#endif
#endif
	return 0;
}

void starttest(void) {
	/* exit if tests are not wanted */
	if (ENABLE_TEST == 0) {
		return;
	}

	if (DO_NOTHING) {
		doNothing();
	}

	/* wait */
	if (WAIT_BEFORE_TEST) {
		for (uint8_t i = 0; i < WAIT_MINUTES; i++) {
			WAIT1_Waitms(60000);
		}
		WAIT1_Waitms(10000);
	}

	if (TEST_SET_PID_VALUES) {
		testSetPIDValues();
	}

	if (TEST_SET_BUTTON_DIST) {
		testSetButtonDist();
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

	if (TEST_BRUSHLESS) {
		testBrushless();
	}

	if (SERVO_CALIB) {
		servoCalib();
	}

	if (TEST_SERVO_CORR) {
		testServoCorr();
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

	if (TEST_SERVO_CIRCLE) {
		testServoCircle();
	}

	if (TEST_TOF_SERVO) {
		testTofServo();
	}

	if (TEST_MOTOR_FEDER) {
		testMotorFeder();
	}

	if (TEST_MOTOR_FEDER_BLOCKING) {
		testMotorFederBlocking();
	}

	if (TEST_DRIVE_TO_START) {
		testDriveToStart();
	}

	if (DEMO_PRESI) {
		uint8_t servo_dir_old_flag = 0, demo_old_flag = 0;
		initToF();
		initServo();
		initMotor();
		WAIT1_Waitms(5000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
		}
		WAIT1_Waitms(2000);
		for (;;) {
			if (SW_Parc_GetVal() == PARCOUR_B && servo_dir_old_flag == 1) {
				for (uint8_t i = 0; i < 4; i++) {
					setServo(i, SERVO_SIDEWAYS);
				}
				servo_dir_old_flag = 0;
			} else if (SW_Parc_GetVal() == PARCOUR_A
					&& servo_dir_old_flag == 0) {
				for (uint8_t i = 0; i < 4; i++) {
					setServo(i, SERVO_STRAIGHT);
				}
				servo_dir_old_flag = 1;
			}
			if (SW_Zent_GetVal() == CENT_ON && demo_old_flag == 0) {
				demoPresi();
				demo_old_flag = 1;
			} else if (SW_Zent_GetVal() == CENT_OFF && demo_old_flag == 1) {
				setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
				setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
				setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
				setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
				for (uint8_t i = 0; i < 4; i++) {
					setMotorSpeed(i, 50);
				}
				WAIT1_Waitms(500);
				for (uint8_t i = 0; i < 4; i++) {
					setMotorSpeed(i, 10);
				}
				WAIT1_Waitms(5000);
				for (uint8_t i = 0; i < 4; i++) {
					setMotorSpeed(i, 0);
				}
				WAIT1_Waitms(500);
				demo_old_flag = 0;
			}
			WAIT1_Waitms(500);
		}
	}

	/* end loop */
	for (;;) {

	}
}

void doNothing(void) {
	//initServo();
	for (;;)
		;
}

#if TEST_SET_PID_VALUES
void test_loop_pidBoth(uint16_t val_front, uint16_t val_rear) {
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
		return;
	}

	dist_err = (int32_t) val_front - (int32_t) NEW_DIST_TO_WALL;
	dist_I_err += dist_err;
	dist_D_err = dist_err - dist_err_old;
	dist_pid_val = ((int32_t) pid_dist_p_mult * dist_err)
	/ (int32_t) pid_dist_p_div
	+ ((int32_t) pid_dist_i_mult * dist_I_err)
	/ (int32_t) pid_dist_i_div
	+ ((int32_t) pid_dist_d_mult * dist_D_err)
	/ (int32_t) pid_dist_d_div;
	dist_err_old = dist_err;

	if (dist_pid_val > PID_BOTH_MAX_CORR_VAL) {
		dist_pid_val = PID_BOTH_MAX_CORR_VAL;
	} else if ((0 - dist_pid_val) > PID_BOTH_MAX_CORR_VAL) {
		dist_pid_val = 0 - PID_BOTH_MAX_CORR_VAL;
	}

	diff_err = (int32_t) val_front - (int32_t) val_rear;
	diff_I_err += diff_err;
	diff_D_err = diff_err - diff_err_old;
	diff_pid_val = ((int32_t) pid_diff_p_mult * diff_err)
	/ (int32_t) pid_diff_p_div
	+ ((int32_t) pid_diff_i_mult * diff_I_err)
	/ (int32_t) pid_diff_i_div
	+ ((int32_t) pid_diff_d_mult * diff_D_err)
	/ (int32_t) pid_diff_d_div;
	diff_err_old = diff_err;

	if (diff_pid_val > PID_BOTH_MAX_CORR_VAL) {
		diff_pid_val = PID_BOTH_MAX_CORR_VAL;
	} else if ((0 - diff_pid_val) > PID_BOTH_MAX_CORR_VAL) {
		diff_pid_val = 0 - PID_BOTH_MAX_CORR_VAL;
	}

	setServoPidBoth(dist_pid_val, diff_pid_val, type, parcours_state);
}
#endif

void testSetPIDValues(void) {
#if TEST_SET_PID_VALUES
	uint8_t res;
	initMotor();
	initToF();
	initServo();
	WAIT1_Waitms(1000);
	pid_dist_p_mult = PID_BOTH_DIST_P_MULT;
	pid_dist_p_div = PID_BOTH_DIST_P_DIV;
	pid_dist_i_mult = PID_BOTH_DIST_I_MULT;
	pid_dist_i_div = PID_BOTH_DIST_I_DIV;
	pid_dist_d_mult = PID_BOTH_DIST_D_MULT;
	pid_dist_d_div = PID_BOTH_DIST_D_DIV;
	pid_diff_p_mult = PID_BOTH_DIFF_P_MULT;
	pid_diff_p_div = PID_BOTH_DIFF_P_DIV;
	pid_diff_i_mult = PID_BOTH_DIFF_I_MULT;
	pid_diff_i_div = PID_BOTH_DIFF_I_DIV;
	pid_diff_d_mult = PID_BOTH_DIFF_D_MULT;
	pid_diff_d_div = PID_BOTH_DIFF_D_DIV;
	pid_set_val_mode = 0;
	/* Parcour A: */
	tof1 = TOF_LEFT_FRONT;
	tof2 = TOF_LEFT_REAR;
	//tof3 = TOF_REAR;
	tof4 = TOF_RIGHT_REAR;
	tof5 = TOF_RIGHT_FRONT;
	type = PARCOUR_A;
	/* Parcour B: */
	/*tof1 = TOF_RIGHT_FRONT;
	 tof2 = TOF_RIGHT_REAR;
	 //tof3 = TOF_REAR;
	 tof4 = TOF_LEFT_REAR;
	 tof5 = TOF_LEFT_FRONT;
	 type=PARCOUR_B;*/
	reset_pid = 1;
	for (;;) {
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 0);
		}
		while (SW_Zent_GetVal() == CENT_OFF) {
			// do nothing
		}
		if (SW_Parc_GetVal() == PARCOUR_B) {
			for (uint8_t i = 0; i < 4; i++) {
				setMotorDirection(i, MOTOR_FORWARD);
			}
			parcours_state = 2;
		} else {
			for (uint8_t i = 0; i < 4; i++) {
				setMotorDirection(i, MOTOR_BACKWARD);
			}
			parcours_state = 6;
		}
		WAIT1_Waitms(50);
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 100);
		}
		WAIT1_Waitms(50);
		reset_pid = 1;
		while (SW_Zent_GetVal() == CENT_ON) {
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
			if (tof1_val < NEW_CURVE_DETECT_DISTANCE
					|| tof5_val < NEW_CURVE_DETECT_DISTANCE) {
				test_loop_pidBoth(tof1_val, tof2_val);
			} else {
				for (uint8_t i = 0; i < 4; i++) {
					res = setServo(i, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						serialDebugLite(DEBUG_ERROR_SET_SERVO);
					}
				}
			}
		}
	}
#endif
}

void testSetButtonDist(void) {
#if TEST_SET_BUTTON_DIST
	uint8_t res;
	button_dist_val = 0;
	initMotor();
	initToF();
	initServo();
	WAIT1_Waitms(1000);
	for (;;) {
		while (button_dist_val == 0) {
			// wait
		}
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_SIDEWAYS);
		}
		type = SW_Parc_GetVal();
		if (type == PARCOUR_A) {
			tof1 = TOF_LEFT_FRONT;
			tof2 = TOF_LEFT_REAR;
			//tof3 = TOF_REAR;
			//tof4 = TOF_RIGHT_REAR;
			//tof5 = TOF_RIGHT_FRONT;
		} else {
			tof1 = TOF_RIGHT_FRONT;
			tof2 = TOF_RIGHT_REAR;
			//tof3 = TOF_REAR;
			//tof4 = TOF_LEFT_REAR;
			//tof5 = TOF_LEFT_FRONT;
		}
		res = getToFValueMillimeters(tof2, &tof2_val);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
		}
		res = getToFValueMillimeters(tof1, &tof1_val);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
		}
		res = getToFValueMillimeters(tof2, &tof2_val);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
		}
		res = getToFValueMillimeters(tof1, &tof1_val);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
		}
		while (tof1_val > tof2_val + 3 || tof1_val < tof2_val - 3) {
			if (type == PARCOUR_A) {
				if (tof1_val < tof2_val) {
					setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
					setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
					setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
					setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
				} else {
					setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
					setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
					setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
					setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
				}
			} else {
				if (tof1_val < tof2_val) {
					setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
					setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
					setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
					setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
				} else {
					setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
					setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
					setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
					setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
				}
			}
			WAIT1_Waitms(100);
			for (uint8_t i = 0; i < 4; i++) {
				setMotorSpeed(i, 20);
			}
			WAIT1_Waitms(200); // todo
			for (uint8_t i = 0; i < 4; i++) {
				setMotorSpeed(i, 0);
			}
			WAIT1_Waitms(100);
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
			res = getToFValueMillimeters(tof1, &tof1_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
		}

		res = getToFValueMillimeters(tof2, &tof2_val);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
		}
		/* start motors and get button dist */
		if (button_dist_val < tof2_val) {
			if (type == PARCOUR_A) {
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
				WAIT1_Waitms(NEW_WAIT_TIME_DEFAULT);
			}
			state8_neg_drv_dir = 1;
		} else {
			if (type == PARCOUR_A) {
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
			} else {
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
			state8_neg_drv_dir = 0;
		}
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 10);
		}
		while (1) {
			if (state8_neg_drv_dir) {
				if (tof2_val <= button_dist_val) {
					for (uint8_t i = 0; i < 4; i++) {
						setMotorSpeed(i, 0);
					}
					break;
				}
			} else {
				if (tof2_val >= button_dist_val) {
					for (uint8_t i = 0; i < 4; i++) {
						setMotorSpeed(i, 0);
					}
					break;
				}
			}
			res = getToFValueMillimeters(tof2, &tof2_val);
			if (res != ERR_OK) {
				serialDebugLite(DEBUG_ERROR_GET_TOF_VALUE);
			}
		}

		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
		}
		for (uint8_t i = 0; i < 4; i++) {
			setMotorDirection(i, MOTOR_BACKWARD);
		}
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, NEW_MOTOR_BUTTON_SPEED_2);
		}
		WAIT1_Waitms(NEW_DRIVE_INTO_BUTTON_TIME);
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 0);
		}

		button_dist_val = 0;
	}
#endif
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

void testBrushless() {
	initServo();
	for (;;) {
		WAIT1_Waitms(5000);
		setBrushless(BRUSHLESS_ON);
		WAIT1_Waitms(5000);
		setBrushless(BRUSHLESS_OFF);
	}
}

void servoCalib(void) {
	initServo();
	WAIT1_Waitms(2000);
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_STRAIGHT);
	}
	for (;;) {
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_SIDEWAYS);
		}
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
		}
	}
	for (;;)
		;
}

void testServoCorr(void) {
	initServo();
	WAIT1_Waitms(2000);
	for (;;) {
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
		}
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_CORR_LEFT);
		}
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_CORR_RIGHT);
		}
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_SIDEWAYS);
		}
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_CORR_FRONT);
		}
		WAIT1_Waitms(2000);
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_CORR_REAR);
		}
		WAIT1_Waitms(2000);
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

void testServoCircle() {
	uint8_t res;
	initServo();
	initMotor();
	for (uint8_t i = 0; i < 4; i++) {
		res = setServo(i, SERVO_CIRCLE);
		if (res != ERR_OK) {
			serialDebugLite(DEBUG_ERROR_SET_SERVO);
		}
		WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	}
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
	WAIT1_Waitms(NEW_WAIT_TIME_SERVO);
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
	WAIT1_Waitms(NEW_SECOND_ROUND_TURN_TIME);
	for (;;) {
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
		WAIT1_Waitms(NEW_SECOND_ROUND_TURN_TIME);
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
		WAIT1_Waitms(NEW_SECOND_ROUND_TURN_TIME);
	}
}

void testTofServo() {
	uint8_t res;
	uint16_t tof_val, val = 0;
	initToF();
	initServo();
	/*initMotor();
	 WAIT1_Waitms(500);
	 for (uint8_t i = 0; i < 4; i++) {
	 res=setMotorDirection(i, MOTOR_FORWARD);
	 res=setMotorSpeed(i, 100);
	 }*/
	for (;;) {
		getToFValueMillimeters(0, &tof_val);
		getToFValueMillimeters(1, &tof_val);
		getToFValueMillimeters(2, &tof_val);
		getToFValueMillimeters(3, &tof_val);
		getToFValueMillimeters(4, &tof_val);
		val += 1;
		if (val >= 30) {
			val = 0;
		}
		setServoPID(SERVO_STRAIGHT, 0, val);
		WAIT1_Waitms(50);
	}
}

void testMotorFeder() {
	initMotor();
	WAIT1_Waitms(1000);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	WAIT1_Waitms(1000);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 30);
	setMotorSpeed(MOTOR_REAR_RIGHT, 30);
	setMotorSpeed(MOTOR_FRONT_LEFT, 30);
	setMotorSpeed(MOTOR_REAR_LEFT, 30);
	//for (uint8_t i = 0; i < 10; i++) {
	for (;;) {
		WAIT1_Waitms(300);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
		WAIT1_Waitms(300);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	}
}

void testMotorFederBlocking() {
	initMotor();
	WAIT1_Waitms(1000);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	WAIT1_Waitms(1000);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 30);
	setMotorSpeed(MOTOR_REAR_RIGHT, 30);
	setMotorSpeed(MOTOR_FRONT_LEFT, 30);
	setMotorSpeed(MOTOR_REAR_LEFT, 30);
	for (uint8_t i = 0; i < 5; i++) {
		WAIT1_Waitms(300);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
		WAIT1_Waitms(300);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	}
	for (uint8_t i = 0; i < 4; i++) {
		blockMotor(i);
	}
	WAIT1_Waitms(10000);
	for (uint8_t i = 0; i < 4; i++) {
		unblockMotor(i);
	}
}

void testDriveToStart() {
	initMotor();
	initServo();
	initToF();
	WAIT1_Waitms(1000);
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_STRAIGHT);
	}
	WAIT1_Waitms(2000);
	for (;;) {
		setServoDriveBack(PARCOUR_A);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 10);
		}
		WAIT1_Waitms(5000);
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 0);
		}
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
		}
		WAIT1_Waitms(10000);
		setServoDriveBack(PARCOUR_B);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 10);
		}
		WAIT1_Waitms(5000);
		for (uint8_t i = 0; i < 4; i++) {
			setMotorSpeed(i, 0);
		}
		for (uint8_t i = 0; i < 4; i++) {
			setServo(i, SERVO_STRAIGHT);
		}
		WAIT1_Waitms(10000);
	}
}

void demoPresi() {
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_SIDEWAYS);
		WAIT1_Waitms(500);
	}
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_STRAIGHT);
		WAIT1_Waitms(500);
	}
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_CIRCLE);
		WAIT1_Waitms(500);
	}
	WAIT1_Waitms(200);
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	setMotorSpeed(MOTOR_FRONT_LEFT, 25);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 100);
	setMotorSpeed(MOTOR_REAR_LEFT, 100);
	setMotorSpeed(MOTOR_REAR_RIGHT, 25);
	WAIT1_Waitms(3000);
	setMotorSpeed(MOTOR_FRONT_LEFT, 0);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
	setMotorSpeed(MOTOR_REAR_LEFT, 0);
	setMotorSpeed(MOTOR_REAR_RIGHT, 0);
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_STRAIGHT);
	}
	WAIT1_Waitms(200);
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	for (uint8_t i = 0; i < 4; i++) {
		setMotorSpeed(i, 50);
	}
	for (uint8_t i = 0; i < 3; i++) {
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
		WAIT1_Waitms(500);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
		WAIT1_Waitms(500);
	}
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
	WAIT1_Waitms(400);
	setMotorSpeed(MOTOR_FRONT_LEFT, 0);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
	setMotorSpeed(MOTOR_REAR_LEFT, 0);
	setMotorSpeed(MOTOR_REAR_RIGHT, 0);
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_CIRCLE);
	}
	WAIT1_Waitms(400);
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
	setMotorSpeed(MOTOR_FRONT_LEFT, 100);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 25);
	setMotorSpeed(MOTOR_REAR_LEFT, 25);
	setMotorSpeed(MOTOR_REAR_RIGHT, 100);
	WAIT1_Waitms(3000);
	setMotorSpeed(MOTOR_FRONT_LEFT, 0);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
	setMotorSpeed(MOTOR_REAR_LEFT, 0);
	setMotorSpeed(MOTOR_REAR_RIGHT, 0);
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_STRAIGHT);
	}
	WAIT1_Waitms(200);
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
	for (uint8_t i = 0; i < 4; i++) {
		setMotorSpeed(i, 50);
	}
	for (uint8_t i = 0; i < 3; i++) {
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
		WAIT1_Waitms(500);
		setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
		setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
		setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
		WAIT1_Waitms(500);
	}
	setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
	setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
	setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
	WAIT1_Waitms(400);
	setMotorSpeed(MOTOR_FRONT_LEFT, 0);
	setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
	setMotorSpeed(MOTOR_REAR_LEFT, 0);
	setMotorSpeed(MOTOR_REAR_RIGHT, 0);
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_SIDEWAYS);
	}
	WAIT1_Waitms(1000);
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_CIRCLE);
		WAIT1_Waitms(500);
	}
	for (uint8_t i = 0; i < 4; i++) {
		setServo(i, SERVO_STRAIGHT);
		WAIT1_Waitms(500);
	}
}
