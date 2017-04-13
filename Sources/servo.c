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
	switch (state) {
	case BRUSHLESS_ON:
		return setServoPwm(brushlessChannel, 0, brushlessValueOn);
	case BRUSHLESS_OFF:
		return setServoPwm(brushlessChannel, 0, brushlessValueOff);
	case BRUSHLESS_INIT:
		return setServoPwm(brushlessChannel, 0, brushlessValueInit);
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
	default:
		return ERR_VALUE;
	}
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
	/* write to bus */
	return GenI2C_ToF_ReadAddress(ad, &reg, sizeof(reg), val, 1);
}
uint8_t servoWrite8(uint8_t ad, uint8_t reg, uint8_t val) {
	/* write to bus */
	return GenI2C_ToF_WriteAddress(ad, &reg, sizeof(reg), &val, sizeof(val));
}
uint8_t servoRead32(uint8_t ad, uint8_t reg, uint32_t * val) {
	/* write to bus */
	return GenI2C_ToF_ReadAddress(ad, &reg, sizeof(reg), (uint8_t *) val, 1);
}
uint8_t servoWrite32(uint8_t ad, uint8_t reg, uint32_t val) {
	/* copy address and value in 8bit arrays */
	uint8_t v[4];
	v[0] = val & 0xff;
	v[1] = (val >> 8) & 0xff;
	v[2] = (val >> 16) & 0xff;
	v[3] = val >> 24;

	/* write to bus */
	return GenI2C_ToF_WriteAddress(ad, &reg, sizeof(reg), &v[0], sizeof(v));
}
