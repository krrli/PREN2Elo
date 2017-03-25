#ifndef SOURCES_PROGRAM_H_
#define SOURCES_PROGRAM_H_

/*
 * External Includes
 */
#include "Events.h" // Used for indirect Includes of Hardware Components

/*
 * Declaration of Constants used for the serial Interfaces
 */
#define NUMBER_OF_SERIAL_PORTS 2
enum serialPort {
	PC = 0, RasPi = 1
};
enum serialResponse { // !!!ERROR!!! not every value may be used, serial Rx interrupt isn't called with every byte
	ACKNOWLEDGE = 0x20,
	ERROR = 0x10,
	BUTTON1 = 0x43,
	BUTTON2 = 0x45,
	BUTTON3 = 0x46,
	BUTTON4 = 0x49,
	BUTTON5 = 0x4A
};
enum serialCommands // !!!ERROR!!! not every value may be used, serial Rx interrupt isn't called with every byte
{
	START = 0x80, // RPi to FD
	ROMAN_NUMERAL_REQUEST = 0x40, // FD to RPi
	CURVE = 0x08, // FD to RPi
	PAUSE = 0xB0, // RPi to FD
	RESUME = 0x70 // RPi to FD
};

/*
 * Declaration of states for main loop
 */
enum parcoursState {
	DRIVE_FORWARD, DRIVE_BACKWARD, DRIVE_LEFT, DRIVE_RIGHT, STOPPED
};
enum parcourType { // Values given by switch
	PARCOUR_A = 0, PARCOUR_B = 1
};
enum centrifugeState { // Values given by switch
	CENT_OFF = 0, CENT_ON = 1
};
enum buttonChecked {
	BUTTON_CHECKED, BUTTON_UNCHECKED
};
enum wheelPosition {
	STRAIGHT, SIDEWAYS
};
enum parcourEnd {
	REACHED, NOT_REACHED
};
enum driveDistance {
	CURVE_DIST = 0xA0, // todo: change values
	BUTTON1_A = 0xA0,
	BUTTON2_A = 0xA0,
	BUTTON3_A = 0xA0,
	BUTTON4_A = 0xA0,
	BUTTON5_A = 0xA0,
	BUTTON1_B = 0xA0,
	BUTTON2_B = 0xA0,
	BUTTON3_B = 0xA0,
	BUTTON4_B = 0xA0,
	BUTTON5_B = 0xA0
};

/*
 * declarations for the tof sensors
 */
#define NUMBER_OF_SENSORS 2
#define ERROR_WRONG_SENSOR_NUMBER 0xff
enum tofAddresses {
	TOF_DEFAULT = 0x29,
	TOF1 = 0x02,
	TOF2 = 0x03,
	TOF3 = 0x04,
	TOF4 = 0x05,
	TOF5 = 0x06,
	TOF6 = 0x07
};
enum regAddr {
	IDENTIFICATION__MODEL_ID = 0x000,
	IDENTIFICATION__MODEL_REV_MAJOR = 0x001,
	IDENTIFICATION__MODEL_REV_MINOR = 0x002,
	IDENTIFICATION__MODULE_REV_MAJOR = 0x003,
	IDENTIFICATION__MODULE_REV_MINOR = 0x004,
	IDENTIFICATION__DATE_HI = 0x006,
	IDENTIFICATION__DATE_LO = 0x007,
	IDENTIFICATION__TIME = 0x008, // 16-bit
	SYSTEM__MODE_GPIO0 = 0x010,
	SYSTEM__MODE_GPIO1 = 0x011,
	SYSTEM__HISTORY_CTRL = 0x012,
	SYSTEM__INTERRUPT_CONFIG_GPIO = 0x014,
	SYSTEM__INTERRUPT_CLEAR = 0x015,
	SYSTEM__FRESH_OUT_OF_RESET = 0x016,
	SYSTEM__GROUPED_PARAMETER_HOLD = 0x017,
	SYSRANGE__START = 0x018,
	SYSRANGE__THRESH_HIGH = 0x019,
	SYSRANGE__THRESH_LOW = 0x01A,
	SYSRANGE__INTERMEASUREMENT_PERIOD = 0x01B,
	SYSRANGE__MAX_CONVERGENCE_TIME = 0x01C,
	SYSRANGE__CROSSTALK_COMPENSATION_RATE = 0x01E, // 16-bit
	SYSRANGE__CROSSTALK_VALID_HEIGHT = 0x021,
	SYSRANGE__EARLY_CONVERGENCE_ESTIMATE = 0x022, // 16-bit
	SYSRANGE__PART_TO_PART_RANGE_OFFSET = 0x024,
	SYSRANGE__RANGE_IGNORE_VALID_HEIGHT = 0x025,
	SYSRANGE__RANGE_IGNORE_THRESHOLD = 0x026, // 16-bit
	SYSRANGE__MAX_AMBIENT_LEVEL_MULT = 0x02C,
	SYSRANGE__RANGE_CHECK_ENABLES = 0x02D,
	SYSRANGE__VHV_RECALIBRATE = 0x02E,
	SYSRANGE__VHV_REPEAT_RATE = 0x031,
	SYSALS__START = 0x038,
	SYSALS__THRESH_HIGH = 0x03A,
	SYSALS__THRESH_LOW = 0x03C,
	SYSALS__INTERMEASUREMENT_PERIOD = 0x03E,
	SYSALS__ANALOGUE_GAIN = 0x03F,
	SYSALS__INTEGRATION_PERIOD = 0x040,
	RESULT__RANGE_STATUS = 0x04D,
	RESULT__ALS_STATUS = 0x04E,
	RESULT__INTERRUPT_STATUS_GPIO = 0x04F,
	RESULT__ALS_VAL = 0x050, // 16-bit
	RESULT__HISTORY_BUFFER_0 = 0x052, // 16-bit
	RESULT__HISTORY_BUFFER_1 = 0x054, // 16-bit
	RESULT__HISTORY_BUFFER_2 = 0x056, // 16-bit
	RESULT__HISTORY_BUFFER_3 = 0x058, // 16-bit
	RESULT__HISTORY_BUFFER_4 = 0x05A, // 16-bit
	RESULT__HISTORY_BUFFER_5 = 0x05C, // 16-bit
	RESULT__HISTORY_BUFFER_6 = 0x05E, // 16-bit
	RESULT__HISTORY_BUFFER_7 = 0x060, // 16-bit
	RESULT__RANGE_VAL = 0x062,
	RESULT__RANGE_RAW = 0x064,
	RESULT__RANGE_RETURN_RATE = 0x066, // 16-bit
	RESULT__RANGE_REFERENCE_RATE = 0x068, // 16-bit
	RESULT__RANGE_RETURN_SIGNAL_COUNT = 0x06C, // 32-bit
	RESULT__RANGE_REFERENCE_SIGNAL_COUNT = 0x070, // 32-bit
	RESULT__RANGE_RETURN_AMB_COUNT = 0x074, // 32-bit
	RESULT__RANGE_REFERENCE_AMB_COUNT = 0x078, // 32-bit
	RESULT__RANGE_RETURN_CONV_TIME = 0x07C, // 32-bit
	RESULT__RANGE_REFERENCE_CONV_TIME = 0x080, // 32-bit
	READOUT__AVERAGING_SAMPLE_PERIOD = 0x10A,
	FIRMWARE__BOOTUP = 0x119,
	FIRMWARE__RESULT_SCALER = 0x120,
	I2C_SLAVE__DEVICE_ADDRESS = 0x212,
	INTERLEAVED_MODE__ENABLE = 0x2A3,
};
#define VL6180X_REG_IDENTIFICATION_MODEL_ID       0x000
#define VL6180X_REG_SYSTEM_INTERRUPT_CONFIG       0x014
#define VL6180X_REG_SYSTEM_INTERRUPT_CLEAR        0x015
#define VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET     0x016
#define VL6180X_REG_SYSRANGE_START                0x018
#define VL6180X_REG_SYSALS_START                  0x038
#define VL6180X_REG_SYSALS_ANALOGUE_GAIN          0x03F
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_HI  0x040
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_LO  0x041
#define VL6180X_REG_RESULT_ALS_VAL                0x050
#define VL6180X_REG_RESULT_RANGE_VAL              0x062
#define VL6180X_REG_RESULT_RANGE_STATUS           0x04d
#define VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO  0x04f
enum VL6180X_ALS_GAIN {
	VL6180X_ALS_GAIN_1 = 0x06,
	VL6180X_ALS_GAIN_1_25 = 0x05,
	VL6180X_ALS_GAIN_1_67 = 0x04,
	VL6180X_ALS_GAIN_2_5 = 0x03,
	VL6180X_ALS_GAIN_5 = 0x02,
	VL6180X_ALS_GAIN_10 = 0x01,
	VL6180X_ALS_GAIN_20 = 0x00,
	VL6180X_ALS_GAIN_40 = 0x07,
};
enum VL_Enum_Error {
	VL_ON_ERROR_INIT,
	VL_ON_ERROR_WRONG_DEVICE,
	VL_ON_ERROR_CONFIGURE_DEFAULT,
	VL_ON_ERROR_ENABLE_FAULT,
	VL_ON_ERROR_INIT_DEVICE,
	VL_ON_ERROR_ENABLE_DEVICE,
	VL_ON_ERROR_SET_I2C_ADDRESS,
};

/*
 * method declarations
 */

/*
 * program.c
 */

/* init method */
void start(void);

/* called from Hardware Interrupt */
void serialRxInt(uint8_t ch, uint8_t port);

/* sends byte to serial port */
void serialSend(uint8_t ch, uint8_t port);

/* method to simulate the serial communication of a complete parcour */
void simulateParcour(void);

/* main loop for driving */
void mainLoop(void);

/*
 * tof.c
 */

/* init tof sensors */
uint8_t initToF(void);

/* get value val of sensor sens */
uint8_t getToFValue(uint8_t sens, uint8_t * val);

/* enable / disable sensor sens via chip enable pin */
void enableToF(uint8_t sens);
void disableToF(uint8_t sens);

/* i2c stuff */
uint8_t writeRegister16bit(uint8_t ad, uint16_t reg, uint16_t val);
uint8_t writeRegister8bit(uint8_t ad, uint16_t reg, uint8_t val);
uint8_t readRegister16bit(uint8_t ad, uint16_t reg, uint16_t * val);
uint8_t readRegister8bit(uint8_t ad, uint16_t reg, uint8_t * val);

#endif /* SOURCES_PROGRAM_H_ */
