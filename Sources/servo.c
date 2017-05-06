/*
 * todo:
 * - init brushless
 * - servo values
 */

#include "program.h"

/*
 * variables
 */

/*
 * T=1/f=1/60=0.016667
 * tick=T/4095=4.0700e-06
 * ticksperms=0.001/tick=245.70 --> 0°
 * 2*ticksperms=491.40 --> 180°
 */
// todo values: 100..630, 90°: 246,491
uint16_t servoValuesStraight[] = { 200, 500, 500, 200 }; // 0...4095; 246 --> 0°; 491 --> 180°
uint16_t servoValuesSideways[] = { 455, 260, 245, 450 }; // 0...4095; 246 --> 0°; 491 --> 180°
uint16_t servoValuesCorrLeft[] = { 185, 515, 485, 215 };
uint16_t servoValuesCorrRight[] = { 215, 485, 515, 185 };
uint16_t servoValuesCorrFront[] = { 470, 275, 230, 435 };
uint16_t servoValuesCorrRear[] = { 440, 245, 260, 465 };
uint16_t servoValuesCircle[] = { 342, 365, 357, 340 };
uint8_t servoChannels[] = { 0, 1, 2, 3 }; // 0...15
uint16_t brushlessValueOff = 246;
uint16_t brushlessValueOn = 300; //min 300
uint16_t brushlessValueInit = 491; // todo
uint8_t brushlessChannel = 4;

/*
 * VL,HL,VR,HR
 */

/*
 * external functions
 */

/* init servos and brushless */
uint8_t initServo(void) {
	uint8_t res;

	/* reset servo board */
	res = resetServo();
	if (res != ERR_OK) {
		return res;
	}

	/* set frequency */
	res = setServoPwmFreq();
	if (res != ERR_OK) {
		return res;
	}

	/* init brushless */
	res = setBrushless(BRUSHLESS_OFF);
	if (res != ERR_OK) {
		return res;
	}
	WAIT1_Waitms(3000);

	/* init servos */
	for (int i = 0; i < 4; i++) {
		res = setServo(i, SERVO_STRAIGHT);
		if (res != ERR_OK) {
			return res;
		}
	}

	return ERR_OK;
}

/* set brushless */
uint8_t setBrushless(enum BrushlessState state) {
	uint8_t res;
	switch (state) {
	case BRUSHLESS_ON:
		for (uint8_t i = 0; i < 2; i++) {
			res = setServoPwm(brushlessChannel, 0, brushlessValueOn);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(50);
			res = setServoPwm(brushlessChannel, 0, brushlessValueOff);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(200);
		}
		for (uint8_t i = 0; i < 2; i++) {
			res = setServoPwm(brushlessChannel, 0, brushlessValueOn);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(100);
			res = setServoPwm(brushlessChannel, 0, brushlessValueOff);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(150);
		}
		for (uint8_t i = 0; i < 2; i++) {
			res = setServoPwm(brushlessChannel, 0, brushlessValueOn);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(150);
			res = setServoPwm(brushlessChannel, 0, brushlessValueOff);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(100);
		}
		for (uint8_t i = 0; i < 2; i++) {
			res = setServoPwm(brushlessChannel, 0, brushlessValueOn);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(200);
			res = setServoPwm(brushlessChannel, 0, brushlessValueOff);
			if (res != ERR_OK) {
				setServoPwm(brushlessChannel, 0, brushlessValueOff);
				return res;
			}
			WAIT1_Waitms(50);
		}
		res = setServoPwm(brushlessChannel, 0, brushlessValueOn);
		if (res != ERR_OK) {
			setServoPwm(brushlessChannel, 0, brushlessValueOff);
		}
		return res;
	case BRUSHLESS_OFF:
		return setServoPwm(brushlessChannel, 0, brushlessValueOff);
	case BRUSHLESS_INIT:
		//return setServoPwm(brushlessChannel, 0, brushlessValueInit);
		return ERR_VALUE;
	default:
		return ERR_VALUE;
	}
}

/* set servos */
uint8_t setServo(uint8_t ser, enum ServoDirection dir) { // ser = 0...3
	switch (dir) {
	case SERVO_STRAIGHT:
		return setServoPwm(servoChannels[ser], 0, servoValuesStraight[ser]);
	case SERVO_SIDEWAYS:
		return setServoPwm(servoChannels[ser], 0, servoValuesSideways[ser]);
	case SERVO_CORR_LEFT:
		return setServoPwm(servoChannels[ser], 0, servoValuesCorrLeft[ser]);
	case SERVO_CORR_RIGHT:
		return setServoPwm(servoChannels[ser], 0, servoValuesCorrRight[ser]);
	case SERVO_CORR_FRONT:
		return setServoPwm(servoChannels[ser], 0, servoValuesCorrFront[ser]);
	case SERVO_CORR_REAR:
		return setServoPwm(servoChannels[ser], 0, servoValuesCorrRear[ser]);
	case SERVO_CIRCLE:
		return setServoPwm(servoChannels[ser], 0, servoValuesCircle[ser]);
	default:
		return ERR_VALUE;
	}
}

uint8_t setServoDriveBack(enum parcourType type) {
	uint8_t res;
	if (type == PARCOUR_A) {
		res = setServoPwm(0, 0, 455 + 50); //FL
		if (res != ERR_OK) {
			return res;
		}
		res = setServoPwm(0, 0, 260 - 50); //RL
		if (res != ERR_OK) {
			return res;
		}
		res = setServoPwm(0, 0, 245 - 50); //FR
		if (res != ERR_OK) {
			return res;
		}
		res = setServoPwm(0, 0, 450 + 50); //RR
		if (res != ERR_OK) {
			return res;
		}
	} else {
		res = setServoPwm(0, 0, 455 - 50); //FL
		if (res != ERR_OK) {
			return res;
		}
		res = setServoPwm(0, 0, 260 + 50); //RL
		if (res != ERR_OK) {
			return res;
		}
		res = setServoPwm(0, 0, 245 + 50); //FR
		if (res != ERR_OK) {
			return res;
		}
		res = setServoPwm(0, 0, 450 - 50); //RR
		if (res != ERR_OK) {
			return res;
		}
	}
	return ERR_OK;
}

uint8_t setServoPID(enum ServoDirection dir, uint8_t corr_dir,
		uint16_t corr_val) {
	uint8_t res;
	// VL,HL,VR,HR
	// 200, 500, 500, 200
	// corr_dir: 0 right/front, 1 left/back
	switch (dir) {
	case SERVO_STRAIGHT:
		switch (corr_dir) {
		case 0: //right
			res = setServoPwm(servoChannels[0], 0,
					servoValuesStraight[0] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[1], 0,
					servoValuesStraight[1] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[2], 0,
					servoValuesStraight[2] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[3], 0,
					servoValuesStraight[3] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			break;
		case 1: //left
			res = setServoPwm(servoChannels[0], 0,
					servoValuesStraight[0] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[1], 0,
					servoValuesStraight[1] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[2], 0,
					servoValuesStraight[2] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[3], 0,
					servoValuesStraight[3] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			break;
		default:
			return ERR_VALUE;
		}
		return ERR_OK;
		// VL,HL,VR,HR
		// 455, 260, 245, 450
		// corr_dir: 0 right/front, 1 left/back
	case SERVO_SIDEWAYS:
		switch (corr_dir) {
		case 0: //front
			res = setServoPwm(servoChannels[0], 0,
					servoValuesSideways[0] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[1], 0,
					servoValuesSideways[1] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[2], 0,
					servoValuesSideways[2] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[3], 0,
					servoValuesSideways[3] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			break;
		case 1: //back
			res = setServoPwm(servoChannels[0], 0,
					servoValuesSideways[0] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[1], 0,
					servoValuesSideways[1] - corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[2], 0,
					servoValuesSideways[2] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			res = setServoPwm(servoChannels[3], 0,
					servoValuesSideways[3] + corr_val);
			if (res != ERR_OK) {
				return res;
			}
			WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
			break;
		default:
			return ERR_VALUE;
		}
		return ERR_OK;
	default:
		return ERR_VALUE;
	}
}

void setServoPidBoth(int32_t pid_val_dist, int32_t pid_val_diff,
		enum parcourType type, uint8_t state) {
	uint8_t parc_a_forw = 0, parc_a_back = 0, parc_b_forw = 0, parc_b_back = 0;
	if (type == PARCOUR_A) {
		if (state == 2) {
			parc_a_forw = 1;
		} else if (state == 6) {
			parc_a_back = 1;
		}
	} else {
		if (state == 2) {
			parc_b_forw = 1;
		} else if (state == 6) {
			parc_b_back = 1;
		}
	}

	int32_t servo_val_fl, servo_val_fr, servo_val_rl, servo_val_rr;
	if (parc_a_forw) {
		servo_val_fl = (int32_t) servoValuesStraight[0] - pid_val_dist
				- pid_val_diff;
		servo_val_fr = (int32_t) servoValuesStraight[2] - pid_val_dist
				- pid_val_diff;
		servo_val_rl = (int32_t) servoValuesStraight[1] - pid_val_dist;
		servo_val_rr = (int32_t) servoValuesStraight[3] - pid_val_dist;
	} else if (parc_a_back) {
		servo_val_fl = (int32_t) servoValuesStraight[0] + pid_val_dist;
		servo_val_fr = (int32_t) servoValuesStraight[2] + pid_val_dist;
		servo_val_rl = (int32_t) servoValuesStraight[1] + pid_val_dist
				- pid_val_diff;
		servo_val_rr = (int32_t) servoValuesStraight[3] + pid_val_dist
				- pid_val_diff;
	} else if (parc_b_forw) {
		servo_val_fl = (int32_t) servoValuesStraight[0] + pid_val_dist
				+ pid_val_diff;
		servo_val_fr = (int32_t) servoValuesStraight[2] + pid_val_dist
				+ pid_val_diff;
		servo_val_rl = (int32_t) servoValuesStraight[1] + pid_val_dist;
		servo_val_rr = (int32_t) servoValuesStraight[3] + pid_val_dist;
	} else if (parc_b_back) {
		servo_val_fl = (int32_t) servoValuesStraight[0] - pid_val_dist;
		servo_val_fr = (int32_t) servoValuesStraight[2] - pid_val_dist;
		servo_val_rl = (int32_t) servoValuesStraight[1] - pid_val_dist
				+ pid_val_diff;
		servo_val_rr = (int32_t) servoValuesStraight[3] - pid_val_dist
				+ pid_val_diff;
	}

	uint8_t res;
	res = setServoPwm(servoChannels[0], 0, servo_val_fl);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	res = setServoPwm(servoChannels[1], 0, servo_val_rl);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	res = setServoPwm(servoChannels[2], 0, servo_val_fr);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
	res = setServoPwm(servoChannels[3], 0, servo_val_rr);
	if (res != ERR_OK) {
		serialDebugLite(DEBUG_ERROR_SET_SERVO);
	}
	WAIT1_Waitms(PID_WAIT_TIME_SERVO_CORR);
}

/*
 * internal functions
 */

/* reset */
uint8_t resetServo(void) {
	uint8_t res;

	/* reset servo driver board */
	res = servoWrite8(PCA9685_ADDRESS, PCA9685_MODE1, 0x0);
	if (res != ERR_OK) {
		return res;
	}

	return ERR_OK;
}

/* set pwm frequency */
uint8_t setServoPwmFreq(void) {
	uint8_t res;

	/* calculate prescale value */
	/*uint8_t freq = 60; // 60 Hz
	 uint8_t prescale;
	 float f_freq, f_prescale;
	 f_freq = (float) freq;
	 f_freq *= 0.9;
	 f_prescale = 25000000;
	 f_prescale /= 4096;
	 f_prescale /= f_freq;
	 f_prescale -= 1;
	 prescale = (uint8_t) f_prescale;*/
	uint8_t prescale = 112; // value for 60 Hz

	/* write prescale value to board */
	uint8_t oldmode, newmode;
	res = servoRead8(PCA9685_ADDRESS, PCA9685_MODE1, &oldmode);
	if (res != ERR_OK) {
		return res;
	}
	newmode = (oldmode & 0x7F) | 0x10; // sleep
	res = servoWrite8(PCA9685_ADDRESS, PCA9685_MODE1, newmode); // go to sleep
	if (res != ERR_OK) {
		return res;
	}
	res = servoWrite8(PCA9685_ADDRESS, PCA9685_PRESCALE, prescale); // set prescaler
	if (res != ERR_OK) {
		return res;
	}
	res = servoWrite8(PCA9685_ADDRESS, PCA9685_MODE1, oldmode);
	if (res != ERR_OK) {
		return res;
	}
	WAIT1_Waitms(5);
	res = servoWrite8(PCA9685_ADDRESS, PCA9685_MODE1, oldmode | 0xa1); // turn on auto increment
	if (res != ERR_OK) {
		return res;
	}

	return ERR_OK;
}

/* set pwm value */
uint8_t setServoPwm(uint8_t ch, uint16_t on, uint16_t off) {
	uint8_t res;

	/* write values to register */
	uint32_t data = (off << 16) | on;
	res = servoWrite32(PCA9685_ADDRESS, PCA9685_CH0_ON_L + (4 * ch), data);
	if (res != ERR_OK) {
		return res;
	}

	return ERR_OK;
}

/* i2c stuff */
uint8_t servoRead8(uint8_t ad, uint8_t reg, uint8_t * val) {
	WAIT1_Waitms(1);
	/* write to bus */
	return GenI2C_ToF_ReadAddress(ad, &reg, sizeof(reg), val, 1);
}
uint8_t servoWrite8(uint8_t ad, uint8_t reg, uint8_t val) {
	WAIT1_Waitms(1);
	/* write to bus */
	return GenI2C_ToF_WriteAddress(ad, &reg, sizeof(reg), &val, sizeof(val));
}
uint8_t servoRead32(uint8_t ad, uint8_t reg, uint32_t * val) {
	WAIT1_Waitms(1);
	/* write to bus */
	return GenI2C_ToF_ReadAddress(ad, &reg, sizeof(reg), (uint8_t *) val, 1);
}
uint8_t servoWrite32(uint8_t ad, uint8_t reg, uint32_t val) {
	WAIT1_Waitms(1);
	/* copy address and value in 8bit arrays */
	uint8_t v[4];
	v[0] = val & 0xff;
	v[1] = (val >> 8) & 0xff;
	v[2] = (val >> 16) & 0xff;
	v[3] = val >> 24;

	/* write to bus */
	return GenI2C_ToF_WriteAddress(ad, &reg, sizeof(reg), &v[0], sizeof(v));
}
