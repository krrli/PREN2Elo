/*
 * todo:
 * - error handling in general
 * - set wait times
 * - testing
 */

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
 * global variables for button pressing
 */
volatile uint8_t button;
volatile enum buttonChecked btnchk;

void start(void) {
	uint8_t res;

	/* init variables for serial communication */
	lastSentCmd[PC] = 0x00;
	lastSentCmd[RasPi] = 0x00;

	/* init variables for main loop */
	state = STOPPED;
	stateBak = STOPPED;
	stateCurr = STOPPED;
	wheelPos = STRAIGHT;
	type = SW_Parc_GetVal();
	endReached = NOT_REACHED;
	distance = CURVE_DIST;

	/* init variables for buttons */
	button = BUTTON3;
	btnchk = BUTTON_UNCHECKED;

	/* init motor */
	res = initMotor();
	if (res != ERR_OK) { // todo
		for (;;) {
			serialSend(ERROR, PC);
			WAIT1_Waitms(1);
			serialSend(ERROR, RasPi);
			WAIT1_Waitms(10);
		}
	}

	/* init servoshield, servos, brushless */
	res = initServo();
	if (res != ERR_OK) { // todo
		for (;;) {
			serialSend(ERROR, PC);
			WAIT1_Waitms(1);
			serialSend(ERROR, RasPi);
			WAIT1_Waitms(10);
		}
	}

	/* init tof sensors */
	res = initToF();
	if (res != ERR_OK) { // todo
		for (;;) {
			serialSend(ERROR, PC);
			WAIT1_Waitms(1);
			serialSend(ERROR, RasPi);
			WAIT1_Waitms(10);
		}
	}

	/* start mainloop */
	mainLoop();

	for (;;) {
		/* fallback loop, should never be reached */
	}
}

void serialRxInt(uint8_t ch, uint8_t port) {
	switch (ch) {
	/* commands from raspi */
	case START:
		serialSend(ACKNOWLEDGE, port);
		if (state == STOPPED)
			state = DRIVE_FORWARD;
		break;
	case PAUSE:
		serialSend(ACKNOWLEDGE, port);
		stateBak = state;
		state = STOPPED;
		break;
	case RESUME:
		serialSend(ACKNOWLEDGE, port);
		state = stateBak;
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
		if (lastSentCmd[port] == ROMAN_NUMERAL_REQUEST) {
			serialSend(ACKNOWLEDGE, port);
			button = ch;
			btnchk = BUTTON_CHECKED;
		} else {
			serialSend(ERROR, port);
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

void mainLoop(void) {
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
		cent_switch = SW_Zent_GetVal();
		if (cent_switch != cent_switch_old) {
			if (cent_switch == CENT_ON) {
				setBrushless(BRUSHLESS_ON);
				cent_switch_old = cent_switch;
			} else if (cent_switch == CENT_OFF) {
				setBrushless(BRUSHLESS_OFF);
				cent_switch_old = cent_switch;
			} else {
				// todo: error
			}
		}

		/* if state changed, set servo and motor outputs */
		if (stateCurr != state) {
			switch (state) {
			case STOPPED:
				/* stop */
				res = setMotorSpeed(MOTOR_FRONT_LEFT, 0);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_FRONT_RIGHT, 0);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_REAR_LEFT, 0);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_REAR_RIGHT, 0);
				if (res != ERR_OK) {
					// todo
				}
				WAIT1_Waitms(10); // todo
				break;
			case DRIVE_FORWARD:
			case DRIVE_BACKWARD:
				/* set servos */
				if (wheelPos != STRAIGHT) {
					res = setServo(0, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						// todo
					}
					res = setServo(1, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						// todo
					}
					res = setServo(2, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						// todo
					}
					res = setServo(3, SERVO_STRAIGHT);
					if (res != ERR_OK) {
						// todo
					}
					wheelPos = STRAIGHT;
					WAIT1_Waitms(1000); // todo
				}

				/* set motors */
				if (state == DRIVE_FORWARD) {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
				} else {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
				}
				WAIT1_Waitms(10); // todo
				res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				WAIT1_Waitms(10); // todo

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
				/* set servo */
				if (wheelPos != SIDEWAYS) {
					res = setServo(0, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						// todo
					}
					res = setServo(1, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						// todo
					}
					res = setServo(2, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						// todo
					}
					res = setServo(3, SERVO_SIDEWAYS);
					if (res != ERR_OK) {
						// todo
					}
					wheelPos = SIDEWAYS;
					WAIT1_Waitms(1000); // todo
				}

				/* set motor */
				if (state == DRIVE_LEFT) {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
				} else {
					res = setMotorDirection(MOTOR_FRONT_LEFT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_FRONT_RIGHT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_LEFT, MOTOR_BACKWARD);
					if (res != ERR_OK) {
						// todo
					}
					res = setMotorDirection(MOTOR_REAR_RIGHT, MOTOR_FORWARD);
					if (res != ERR_OK) {
						// todo
					}
				}
				WAIT1_Waitms(10); // todo
				res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
				if (res != ERR_OK) {
					// todo
				}
				WAIT1_Waitms(10); // todo

				/* set distance */
				if (endReached == NOT_REACHED) {
					/* curve */
					distance = CURVE_DIST;
				} else {
					/* button pressing */
					/* check if button checked, else ask raspi */
					while (btnchk == BUTTON_UNCHECKED) {
						serialSend(ROMAN_NUMERAL_REQUEST, PC);
						WAIT1_Waitms(1);
						serialSend(ROMAN_NUMERAL_REQUEST, RasPi);
						WAIT1_Waitms(1000); // todo
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
							//default:
							// todo: error
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
							//default:
							// todo: error
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
					// todo: error
				}
				res = getToFValueMillimeters(tof2_tmp, &tof2_tmp_val);
				if (res != ERR_OK) {
					// todo: error
				}
				if ((tof1_tmp_val > (DISTANCE_TO_WALL + DISTANCE_TO_WALL_VAR))
						&& (tof1_tmp_val != 0xffff)) {
					/* to far from wall */
					if (type == PARCOUR_A) {
						/* parcour a */
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
					} else {
						/* parcour b */
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
					}
				} else if (tof1_tmp_val
						< (DISTANCE_TO_WALL - DISTANCE_TO_WALL_VAR)) {
					/* to near to wall */
					if (type == PARCOUR_B) {
						/* parcour b */
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
					} else {
						/* parcour a */
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
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
						WAIT1_Waitms(1);
						serialSend(CURVE, RasPi);
						WAIT1_Waitms(1);
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
						WAIT1_Waitms(1);
						serialSend(ROMAN_NUMERAL_REQUEST, RasPi);
						WAIT1_Waitms(100); // todo: give raspi time to answer
					}
				}
				break;
			case DRIVE_LEFT:
			case DRIVE_RIGHT:
				/* drive straight */
				res = getToFValueMillimeters(tof1_tmp, &tof1_tmp_val);
				if (res != ERR_OK) {
					// todo: error
				}
				res = getToFValueMillimeters(tof2_tmp, &tof2_tmp_val);
				if (res != ERR_OK) {
					// todo: error
				}
				tof_diff = (int32_t) tof1_tmp_val - (int32_t) tof2_tmp_val; // front - rear
				if (((type == PARCOUR_A) && (state == DRIVE_LEFT))
						|| ((type == PARCOUR_B) && (state == DRIVE_RIGHT))) {
					/* drive towards wall */
					if (tof_diff > DRIVE_SIDEWAYS_VAR) {
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
					} else if (tof_diff < (0 - DRIVE_SIDEWAYS_VAR)) {
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
					}
				} else {
					/* drive away from wall */
					if (tof_diff > DRIVE_SIDEWAYS_VAR) {
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_FRONT_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_FRONT_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
					} else if (tof_diff < (0 - DRIVE_SIDEWAYS_VAR)) {
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_CORRSPEED);
						if (res != ERR_OK) {
							// todo
						}
						WAIT1_Waitms(CORR_TIME);
						res = setMotorSpeed(MOTOR_REAR_LEFT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
						}
						res = setMotorSpeed(MOTOR_REAR_RIGHT, MOTOR_MAXSPEED);
						if (res != ERR_OK) {
							// todo
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
}
