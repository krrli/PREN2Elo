#include "program.h"

uint8_t initToF(void) {
	uint8_t i;
	for (i = 0; i < NUMBER_OF_SENSORS; i++) {
		disableToF(i);
	}
	for (i = 0; i < NUMBER_OF_SENSORS; i++) {
		enableToF(i);
		// todo
	}
}

uint8_t getToFValue(uint8_t sens, uint8_t * val) {
	if (sens < 0 || sens > NUMBER_OF_SENSORS) {
		return ERROR_WRONG_SENSOR_NUMBER;
	}
	// todo
}

void enableToF(uint8_t sens) {
	switch (sens) {
	case 1:
		ToF1_SetDir(0);
		break;
	case 2:
		ToF2_SetDir(0);
		break;
	case 3:
		ToF3_SetDir(0);
		break;
	case 4:
		ToF4_SetDir(0);
		break;
	case 5:
		ToF5_SetDir(0);
		break;
	case 6:
		ToF6_SetDir(0);
		break;
	}
}

void disableToF(uint8_t sens) {
	switch (sens) {
	case 1:
		ToF1_SetDir(0);
		ToF1_PutVal(0);
		break;
	case 2:
		ToF2_SetDir(0);
		ToF2_PutVal(0);
		break;
	case 3:
		ToF3_SetDir(0);
		ToF3_PutVal(0);
		break;
	case 4:
		ToF4_SetDir(0);
		ToF4_PutVal(0);
		break;
	case 5:
		ToF5_SetDir(0);
		ToF5_PutVal(0);
		break;
	case 6:
		ToF6_SetDir(0);
		ToF6_PutVal(0);
		break;
	}
}

uint8_t writeRegister16bit(uint8_t ad, uint16_t reg, uint16_t val) {
	uint8_t r[2], v[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;
	v[0] = val >> 8;
	v[1] = val & 0xff;
	return GenI2C_ToF_WriteAddress(ad, &r[0], sizeof(r), &v, sizeof(v));
}

uint8_t writeRegister8bit(uint8_t ad, uint16_t reg, uint8_t val) {
	uint8_t r[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;
	return GenI2C_ToF_WriteAddress(ad, &r[0], sizeof(r), &val, sizeof(val));
}

uint8_t readRegister16bit(uint8_t ad, uint16_t reg, uint16_t * val) {
	uint8_t r[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;
	return GenI2C_ToF_ReadAddress(ad, &r[0], sizeof(r), (uint8_t *) val, 2);
}

uint8_t readRegister8bit(uint8_t ad, uint16_t reg, uint8_t * val) {
	uint8_t r[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;
	return GenI2C_ToF_ReadAddress(ad, &r[0], sizeof(r), val, 1);
}
