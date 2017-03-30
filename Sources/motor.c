#include "program.h"

#define INIT_MOTOR_DIRECTION_1	1
#define INIT_MOTOR_DIRECTION_2	0

/* init motor */
void initMotor(void) {
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

	// todo: set direction forward, set speed to 0
}

/* set motor direction */
void setMotorDirection(uint8_t motorIn, enum MotorDirection val) {
	switch (motor){
	case 0:{
		if (MotorDirection == MOTOR_FORWARD){
			MT1_IN1_PutVal(INIT_MOTOR_DIRECTION_1);
			MT1_IN2_PutVal(INIT_MOTOR_DIRECTION_2);
		}
		else{
			MT1_IN1_PutVal(INIT_MOTOR_DIRECTION_2);
			MT1_IN2_PutVal(INIT_MOTOR_DIRECTION_1);
		}
		break;
	}
	case 1:{
		if (MotorDirection == MOTOR_FORWARD){
			MT1_IN3_PutVal(INIT_MOTOR_DIRECTION_1);
			MT1_IN4_PutVal(INIT_MOTOR_DIRECTION_2);
		}
		else{
			MT1_IN3_PutVal(INIT_MOTOR_DIRECTION_2);
			MT1_IN4_PutVal(INIT_MOTOR_DIRECTION_1);
		}
		break;
	}
	case 2:{
		if (MotorDirection == MOTOR_FORWARD){
			MT2_IN1_PutVal(INIT_MOTOR_DIRECTION_2);
			MT2_IN2_PutVal(INIT_MOTOR_DIRECTION_1);
		}
		else{
			MT2_IN1_PutVal(INIT_MOTOR_DIRECTION_1);
			MT2_IN2_PutVal(INIT_MOTOR_DIRECTION_2);
		}
		break;
	}
	case 3:	{
		if (MotorDirection == MOTOR_FORWARD){
			MT2_IN3_PutVal(INIT_MOTOR_DIRECTION_2);
			MT2_IN4_PutVal(INIT_MOTOR_DIRECTION_1);
		}
		else{
			MT2_IN3_PutVal(INIT_MOTOR_DIRECTION_1);
			MT2_IN4_PutVal(INIT_MOTOR_DIRECTION_2);
		}
		break;
	}
	}
}

/* set motor speed */
void setMotorSpeed(uint8_t motor, uint8_t val) {
	switch (motor){
	case 0:{
		MT1_PWM1_SetRatio16(val);
		break;
	}
	case 1:{
		MT1_PWM2_SetRatio16(val);
		break;
	}
	case 2:{
		MT2_PWM1_SetRatio16(val);
		break;
	}
	case 3:{
		MT2_PWM2_SetRatio16(val);
		break;
	}
	}
}
