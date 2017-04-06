#include "program.h"

/* init motor */
uint8_t initMotor(void) {
	/*init motor direction forward*/
	MT1_IN1_PutVal(INIT_MOTOR_DIRECTION_1);
	MT1_IN2_PutVal(INIT_MOTOR_DIRECTION_2);
	MT1_IN3_PutVal(INIT_MOTOR_DIRECTION_1);
	MT1_IN4_PutVal(INIT_MOTOR_DIRECTION_2);
	MT2_IN1_PutVal(INIT_MOTOR_DIRECTION_2);
	MT2_IN2_PutVal(INIT_MOTOR_DIRECTION_1);
	MT2_IN3_PutVal(INIT_MOTOR_DIRECTION_2);
	MT2_IN4_PutVal(INIT_MOTOR_DIRECTION_1);

	/*set speed to 0*/
	MT1_PWM1_SetRatio16(0);
	MT1_PWM2_SetRatio16(0);
	MT2_PWM1_SetRatio16(0);
	MT2_PWM2_SetRatio16(0);

	return ERR_OK;
}

/* set motor direction */
uint8_t setMotorDirection(uint8_t motor, enum MotorDirection val) {
	if (motor >= 0 && motor < NUMBER_OF_MOTOR && (val == 0 || val == 1)) {
		switch (motor) {
		case 0:
			if (val == MOTOR_FORWARD) {
				MT1_IN1_PutVal(INIT_MOTOR_DIRECTION_1);
				MT1_IN2_PutVal(INIT_MOTOR_DIRECTION_2);
			} else {
				MT1_IN1_PutVal(INIT_MOTOR_DIRECTION_2);
				MT1_IN2_PutVal(INIT_MOTOR_DIRECTION_1);
			}
			break;
		case 1:
			if (val == MOTOR_FORWARD) {
				MT1_IN3_PutVal(INIT_MOTOR_DIRECTION_1);
				MT1_IN4_PutVal(INIT_MOTOR_DIRECTION_2);
			} else {
				MT1_IN3_PutVal(INIT_MOTOR_DIRECTION_2);
				MT1_IN4_PutVal(INIT_MOTOR_DIRECTION_1);
			}
			break;
		case 2:
			if (val == MOTOR_FORWARD) {
				MT2_IN1_PutVal(INIT_MOTOR_DIRECTION_2);
				MT2_IN2_PutVal(INIT_MOTOR_DIRECTION_1);
			} else {
				MT2_IN1_PutVal(INIT_MOTOR_DIRECTION_1);
				MT2_IN2_PutVal(INIT_MOTOR_DIRECTION_2);
			}
			break;
		case 3:
			if (val == MOTOR_FORWARD) {
				MT2_IN3_PutVal(INIT_MOTOR_DIRECTION_2);
				MT2_IN4_PutVal(INIT_MOTOR_DIRECTION_1);
			} else {
				MT2_IN3_PutVal(INIT_MOTOR_DIRECTION_1);
				MT2_IN4_PutVal(INIT_MOTOR_DIRECTION_2);
			}
			break;
		}
		return ERR_OK;
	} else
		return ERR_RANGE;
}

/* set motor speed */
uint8_t setMotorSpeed(uint8_t motor, uint16_t val) {
	if (motor >= 0 && motor < NUMBER_OF_MOTOR && (val >= 0 && val <= 0xFFFF)) {
		switch (motor) {
		case 0:
			MT1_PWM1_SetRatio16(val);
			break;
		case 1:
			MT1_PWM2_SetRatio16(val);
			break;
		case 2:
			MT2_PWM1_SetRatio16(val);
			break;
		case 3:
			MT2_PWM2_SetRatio16(val);
			break;
		}
		return ERR_OK;
	} else
		return ERR_RANGE;
}
