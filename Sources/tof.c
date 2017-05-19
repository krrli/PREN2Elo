#include "program.h"

uint8_t last_status; // status of last I2C transmission
uint8_t scaling;
uint8_t default_address = 0x29;
uint8_t address[] = { 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
static uint16_t const ScalerValues[] = { 0, 253, 127, 84 };
uint8_t ptp_offset;

/* init tof sensors */
uint8_t initToF(void) {
	uint8_t i, res;

	/* disable all sensors */
	for (i = 0; i < NUMBER_OF_SENSORS; i++) {
		res = disableToF(i);
		if (res != ERR_OK) {
			return res;
		}
	}

	WAIT1_Waitms(100);

	for (i = 0; i < NUMBER_OF_SENSORS; i++) {
		/* enable sensor i */
		res = enableToF(i);
		if (res != ERR_OK) {
			return res;
		}

		WAIT1_Waitms(100);

		/* write new address */
		res = setToFAddress(i);
		if (res != ERR_OK) {
			return res;
		}

		WAIT1_Waitms(1);

		/* read part-to-part range offset */
		res = readRegister8bit(address[i], SYSRANGE__PART_TO_PART_RANGE_OFFSET,
				&ptp_offset);
		if (res != ERR_OK) {
			return res;
		}

		WAIT1_Waitms(1);
		/* write registers */
		res = writeRegister8bit(address[i], 0x207, 0x01);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x208, 0x01);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x096, 0x00);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x097, 0xFD); // RANGE_SCALER = 253
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0E3, 0x00);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0E4, 0x04);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0E5, 0x02);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0E6, 0x01);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0E7, 0x03);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0F5, 0x02);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0D9, 0x05);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0DB, 0xCE);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0DC, 0x03);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0DD, 0xF8);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x09F, 0x00);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0A3, 0x3C);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0B7, 0x00);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0BB, 0x3C);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0B2, 0x09);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0CA, 0x09);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x198, 0x01);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x1B0, 0x17);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x1AD, 0x00);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x0FF, 0x05);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x100, 0x05);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x199, 0x05);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x1A6, 0x1B);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x1AC, 0x3E);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x1A7, 0x1F);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], 0x030, 0x00);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], SYSTEM__FRESH_OUT_OF_RESET, 0);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
	}

	/* configure default values */
	for (i = 0; i < NUMBER_OF_SENSORS; i++) {
		res = configureToFDefault(i);
		if (res != ERR_OK) {
			return res;
		}
	}

	/* set scaling to 3 (60cm) */
	for (i = 0; i < NUMBER_OF_SENSORS; i++) {
		res = setToFScaling(i, 3);
		if (res != ERR_OK) {
			return res;
		}
	}

#if TOF_MEASURE_CONTINUOUS
	for (i = 0; i < NUMBER_OF_SENSORS; i++) {
		res = writeRegister8bit(address[i], SYSRANGE__INTERMEASUREMENT_PERIOD,
				3); // todo
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
		res = writeRegister8bit(address[i], SYSRANGE__START, 0x03);
		if (res != ERR_OK) {
			return res;
		}
		WAIT1_Waitms(1);
	}
#else
	// nothing
#endif
	return ERR_OK;
}

/* get value of sensor in mm */
uint8_t getToFValueMillimeters(uint8_t sens, uint16_t * val) {
	uint8_t res;

	/* check if sens is a valid sensor number */
	if (sens < 0 || sens >= NUMBER_OF_SENSORS) {
		return ERR_RANGE;
	}
	WAIT1_Waitms(1);

	/* start measurement */
#if TOF_MEASURE_CONTINUOUS
	// nothing
#else
	res = writeRegister8bit(address[sens], SYSRANGE__START, 0x01);
	if (res != ERR_OK) {
		return res;
	}
	WAIT1_Waitms(1);
#endif

	/* wait until measurement finished */
	uint8_t timeoutms = 100;
	uint8_t tmp;
	do {
		/* check if measurement has finished */
		res = readRegister8bit(address[sens], RESULT__INTERRUPT_STATUS_GPIO,
				&tmp);
		if (res != ERR_OK) {
			return res;
		}

		/* make sure it doesn't end in an endless loop */
		if (timeoutms == 0) {
			return ERR_NOTAVAIL;
		}
		WAIT1_Waitms(1);
		timeoutms--;
	} while ((tmp & 0x04) == 0);

	/* read range */
	uint8_t range;
	res = readRegister8bit(address[sens], RESULT__RANGE_VAL, &range);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* clear interrupt */
	res = writeRegister8bit(address[sens], SYSTEM__INTERRUPT_CLEAR, 0x01);
	if (res != ERR_OK) {
		return res;
	}

	/* return value */
	if (range != 0xff) {
		*val = (uint16_t) scaling * (uint16_t) range;
	} else {
		*val = 0xffff;
	}

	return ERR_OK;
}

/* set tof address */
uint8_t setToFAddress(uint8_t sens) {
	/* check if sens is a valid sensor number */
	if (sens < 0 || sens >= NUMBER_OF_SENSORS) {
		return ERR_RANGE;
	}

	WAIT1_Waitms(1);
	/* write address to register */
	return writeRegister8bit(default_address, I2C_SLAVE__DEVICE_ADDRESS,
			address[sens] & 0x7F);
}

/* set default values */
uint8_t configureToFDefault(uint8_t sens) {
	uint8_t res;

	/* check if sens is a valid sensor number */
	if (sens < 0 || sens >= NUMBER_OF_SENSORS) {
		return ERR_RANGE;
	}

	/* "Recommended : Public registers" */

	WAIT1_Waitms(1);
	/* readout__averaging_sample_period = 48 */
	res = writeRegister8bit(address[sens], READOUT__AVERAGING_SAMPLE_PERIOD,
			0x30);
	if (res != ERR_OK) {
		return res;
	}

	/* sysals__analogue_gain_light = 6 (ALS gain = 1 nominal, actually 1.01 according to Table 14 in datasheet) */
	WAIT1_Waitms(1);
	res = writeRegister8bit(address[sens], SYSALS__ANALOGUE_GAIN, 0x46);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* sysrange__vhv_repeat_rate = 255 (auto Very High Voltage temperature recalibration after every 255 range measurements) */
	res = writeRegister8bit(address[sens], SYSRANGE__VHV_REPEAT_RATE, 0xFF);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* sysals__integration_period = 99 (100 ms) */
	/* AN4545 incorrectly recommends writing to register 0x040; 0x63 should go in the lower byte, which is register 0x041. */
	res = writeRegister16bit(address[sens], SYSALS__INTEGRATION_PERIOD, 0x0063);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* sysrange__vhv_recalibrate = 1 (manually trigger a VHV recalibration) */
	res = writeRegister8bit(address[sens], SYSRANGE__VHV_RECALIBRATE, 0x01);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* "Optional: Public registers" */

	/* sysrange__intermeasurement_period = 9 (100 ms) */
	res = writeRegister8bit(address[sens], SYSRANGE__INTERMEASUREMENT_PERIOD,
			0x09);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* sysals__intermeasurement_period = 49 (500 ms) */
	res = writeRegister8bit(address[sens], SYSALS__INTERMEASUREMENT_PERIOD,
			0x31);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* als_int_mode = 4 (ALS new sample ready interrupt); range_int_mode = 4 (range new sample ready interrupt) */
	res = writeRegister8bit(address[sens], SYSTEM__INTERRUPT_CONFIG_GPIO, 0x24);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* Reset other settings to power-on defaults */

	/* sysrange__max_convergence_time = 49 (49 ms) */
	res = writeRegister8bit(address[sens], SYSRANGE__MAX_CONVERGENCE_TIME,
			0x31);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* disable interleaved mode */
	res = writeRegister8bit(address[sens], INTERLEAVED_MODE__ENABLE, 0);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* reset range scaling factor to 1x */
	res = setToFScaling(sens, 1);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	return ERR_OK;
}

/* set scaling factor of tof */
uint8_t setToFScaling(uint8_t sens, uint8_t new_scaling) {
	uint8_t res;

	/* check if sens is a valid sensor number */
	if (sens < 0 || sens >= NUMBER_OF_SENSORS) {
		return ERR_RANGE;
	}

	WAIT1_Waitms(1);
	/* check for valid argument */
	if (new_scaling < 1 || new_scaling > 3) {
		return ERR_VALUE;
	}

	/* default value of SYSRANGE__CROSSTALK_VALID_HEIGHT */
	uint8_t const DefaultCrosstalkValidHeight = 20;

	/* set variable to new value */
	scaling = new_scaling;

	WAIT1_Waitms(1);
	/* write scaling value to sensor */
	res = writeRegister16bit(address[sens], RANGE_SCALER,
			ScalerValues[scaling]);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* apply scaling on part-to-part offset */
	res = writeRegister8bit(address[sens], SYSRANGE__PART_TO_PART_RANGE_OFFSET,
			ptp_offset / scaling);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* apply scaling on cross talk valid height */
	res = writeRegister8bit(address[sens], SYSRANGE__CROSSTALK_VALID_HEIGHT,
			DefaultCrosstalkValidHeight / scaling);
	if (res != ERR_OK) {
		return res;
	}

	WAIT1_Waitms(1);
	/* this function does not apply scaling to RANGE_IGNORE_VALID_HEIGHT */

	/* enable early convergence estimate only at 1x scaling */
	uint8_t rce;
	res = readRegister8bit(address[sens], SYSRANGE__RANGE_CHECK_ENABLES, &rce);
	if (res != ERR_OK) {
		return res;
	}
	WAIT1_Waitms(1);
	res = writeRegister8bit(address[sens], SYSRANGE__RANGE_CHECK_ENABLES,
			(rce & 0xFE) | (scaling == 1));
	if (res != ERR_OK) {
		return res;
	}

	return ERR_OK;
}

/* enable / disable sensor sens via chip enable pin */
uint8_t enableToF(uint8_t sens) {
	/* check if sens is a valid sensor number */
	if (sens < 0 || sens >= NUMBER_OF_SENSORS) {
		return ERR_RANGE;
	}

	switch (sens) {
	case 0:
		/* set direction of ce to input */
		ToF1_SetDir(0);
		break;
	case 1:
		/* set direction of ce to input */
		ToF2_SetDir(0);
		break;
	case 2:
		/* set direction of ce to input */
		ToF3_SetDir(0);
		break;
	case 3:
		/* set direction of ce to input */
		ToF4_SetDir(0);
		break;
	case 4:
		/* set direction of ce to input */
		ToF5_SetDir(0);
		break;
	case 5:
		/* set direction of ce to input */
		ToF6_SetDir(0);
		break;
	}

	return ERR_OK;
}
uint8_t disableToF(uint8_t sens) {
	/* check if sens is a valid sensor number */
	if (sens < 0 || sens >= NUMBER_OF_SENSORS) {
		return ERR_RANGE;
	}

	switch (sens) {
	case 0:
		/* set direction of ce to output and value to low */
		ToF1_SetDir(1);
		ToF1_PutVal(0);
		break;
	case 1:
		/* set direction of ce to output and value to low */
		ToF2_SetDir(1);
		ToF2_PutVal(0);
		break;
	case 2:
		/* set direction of ce to output and value to low */
		ToF3_SetDir(1);
		ToF3_PutVal(0);
		break;
	case 3:
		/* set direction of ce to output and value to low */
		ToF4_SetDir(1);
		ToF4_PutVal(0);
		break;
	case 4:
		/* set direction of ce to output and value to low */
		ToF5_SetDir(1);
		ToF5_PutVal(0);
		break;
	case 5:
		/* set direction of ce to output and value to low */
		ToF6_SetDir(1);
		ToF6_PutVal(0);
		break;
	}

	return ERR_OK;
}

/* i2c stuff */
uint8_t writeRegister16bit(uint8_t ad, uint16_t reg, uint16_t val) {
	/* copy address and value in 8bit arrays */
	uint8_t r[2], v[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;
	v[0] = val >> 8;
	v[1] = val & 0xff;

	/* write to bus */
	return GenI2C_ToF_WriteAddress(ad, &r[0], sizeof(r), &v[0], sizeof(v));
}
uint8_t writeRegister8bit(uint8_t ad, uint16_t reg, uint8_t val) {
	/* copy address in 8bit array */
	uint8_t r[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;

	/* write to bus */
	return GenI2C_ToF_WriteAddress(ad, &r[0], sizeof(r), &val, sizeof(val));
}
uint8_t readRegister16bit(uint8_t ad, uint16_t reg, uint16_t * val) {
	/* copy address in 8bit array */
	uint8_t r[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;

	/* write to bus */
	return GenI2C_ToF_ReadAddress(ad, &r[0], sizeof(r), (uint8_t *) val, 2);
}
uint8_t readRegister8bit(uint8_t ad, uint16_t reg, uint8_t * val) {
	/* copy address in 8bit array */
	uint8_t r[2];
	r[0] = reg >> 8;
	r[1] = reg & 0xff;

	/* write to bus */
	return GenI2C_ToF_ReadAddress(ad, &r[0], sizeof(r), val, 1);
}
