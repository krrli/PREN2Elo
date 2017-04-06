/*
 * todo:
 * - set values
 */

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
enum serialResponse {
	ACKNOWLEDGE = 0x20,
	ERROR = 0x10,
	BUTTON1 = 0x01,
	BUTTON2 = 0x02,
	BUTTON3 = 0x03,
	BUTTON4 = 0x04,
	BUTTON5 = 0x05
};
enum serialCommands
{
	START = 0x80, // RPi to FD
	ROMAN_NUMERAL_REQUEST = 0x40, // FD to RPi
	CURVE = 0x08, // FD to RPi
	PAUSE = 0xB0, // RPi to FD
	RESUME = 0x70 // RPi to FD
};
enum serialDebugLite{
	DEBUG_ERROR_INIT_MOTOR=0xC1,
	DEBUG_ERROR_INIT_SERVO=0xC2,
	DEBUG_ERROR_INIT_TOF=0xC3,
	DEBUG_ERROR_END_LOOP_REACHED=0xC4,
	DEBUG_ERROR_SET_MOTOR_SPEED=0xC5,
	DEBUG_ERROR_SET_MOTOR_DIRECTION=0xC6,
	DEBUG_ERROR_SET_BRUSHLESS=0xC7,
	DEBUG_ERROR_SET_SERVO=0xC8,
	DEBUG_ERROR_GET_TOF_VALUE=0xC9,
	DEBUG_ERROR_WRONG_BUTTON_NUMBER=0xCA
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
#define DISTANCE_TO_WALL 100 // value in mm
#define DISTANCE_TO_WALL_VAR 10 // value in mm
#define DRIVE_SIDEWAYS_VAR 5 // value in mm
enum driveDistance {
	CURVE_DIST = DISTANCE_TO_WALL,
	BUTTON1_A = 0xA0, // todo: change values
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
enum MotorSpeed {
	MOTOR_CORRSPEED = 0xefff, MOTOR_MAXSPEED = 0xffff
};
#define CORR_ENABLED 1
#define CORR_TIME 500 // value in ms
#define BLIND_TIME 2000 // value in ms
#define CURVE_DRIVE_OVER_TIME 200 // value in ms
#define END_DRIVE_OVER_TIME 200 // value in ms
#define DRIVE_INTO_BUTTON_TIME 500 // value in ms
#define WAIT_TIME_DEFAULT 10 // value in ms
#define WAIT_TIME_SERVO 1000 // value in ms
#define WAIT_TIME_SERIAL_LOOP 1000 // value in ms
#define WAIT_TIME_SERIAL_ANSWER 100 // value in ms

/*
 * declarations for the tof sensors
 */
#define NUMBER_OF_SENSORS 1 // max 6
enum ToF_Sensors {
	TOF_LEFT_FRONT = 0,
	TOF_LEFT_REAR = 1,
	TOF_RIGHT_FRONT = 2,
	TOF_RIGHT_REAR = 3,
	TOF_REAR = 4,
	TOF_FRONT = 5
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
	RANGE_SCALER = 0x096, // 16-bit
	READOUT__AVERAGING_SAMPLE_PERIOD = 0x10A,
	FIRMWARE__BOOTUP = 0x119,
	FIRMWARE__RESULT_SCALER = 0x120,
	I2C_SLAVE__DEVICE_ADDRESS = 0x212,
	INTERLEAVED_MODE__ENABLE = 0x2A3,
};
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
 * declarations for the servo driver board
 */
#define PCA9685_ADDRESS 0x40
#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE
#define PCA9685_CH0_ON_L 0x6
#define PCA9685_CH0_ON_H 0x7
#define PCA9685_CH0_OFF_L 0x8
#define PCA9685_CH0_OFF_H 0x9
enum BrushlessState {
	BRUSHLESS_OFF, BRUSHLESS_ON, BRUSHLESS_INIT
};
enum ServoDirection {
	SERVO_STRAIGHT, SERVO_SIDEWAYS
};

/*
 * declarations for the motor driver boards
 */
#define INIT_MOTOR_DIRECTION_1	1
#define INIT_MOTOR_DIRECTION_2	0
#define NUMBER_OF_MOTOR 4

enum MotorDirection {
	MOTOR_FORWARD, MOTOR_BACKWARD
};
enum Motor {
	MOTOR_FRONT_RIGHT = 0,
	MOTOR_FRONT_LEFT = 2,
	MOTOR_REAR_RIGHT = 1,
	MOTOR_REAR_LEFT = 3
};

/*
 * method declarations
 */

/*
 * program.c
 */

/* called from main.c */

/* init method */
void start(void);

/* Interrupts */

/* called from Hardware Interrupt */
void serialRxInt(uint8_t ch, uint8_t port);

/* serial communication */

/* sends byte to serial port */
void serialSend(uint8_t ch, uint8_t port);

/* defines what happens at errors */
void serialDebugLite(uint8_t ch);

/* loops */

/* main loop for driving */
void mainLoop(void);

/*
 * tof.c
 */

/* external functions */

/* init tof sensors */
uint8_t initToF(void); // constructor + init

/* get value of sensor in mm */
uint8_t getToFValueMillimeters(uint8_t sens, uint16_t * val);

/* internal functions */

/* set tof address */
uint8_t setToFAddress(uint8_t sens);

/* set default values */
uint8_t configureToFDefault(uint8_t sens);

/* set scaling factor of tof */
uint8_t setToFScaling(uint8_t sens, uint8_t scaling);

/* enable / disable sensor sens via chip enable pin */
uint8_t enableToF(uint8_t sens);
uint8_t disableToF(uint8_t sens);

/* i2c stuff */
uint8_t writeRegister16bit(uint8_t ad, uint16_t reg, uint16_t val);
uint8_t writeRegister8bit(uint8_t ad, uint16_t reg, uint8_t val);
uint8_t readRegister16bit(uint8_t ad, uint16_t reg, uint16_t * val);
uint8_t readRegister8bit(uint8_t ad, uint16_t reg, uint8_t * val);

/*
 * servo.c
 */

/* external functions */

/* init servos and brushless */
uint8_t initServo(void);

/* set brushless */
uint8_t setBrushless(enum BrushlessState state);

/* set servos */
uint8_t setServo(uint8_t ser, enum ServoDirection dir); // ser = 0...3

/* internal functions */

/* reset */
uint8_t resetServo(void);

/* set pwm frequency */
uint8_t setServoPwmFreq(void);

/* set pwm value */
uint8_t setServoPwm(uint8_t ch, uint16_t on, uint16_t off);

/* i2c stuff */
uint8_t servoRead8(uint8_t ad, uint8_t reg, uint8_t * val);
uint8_t servoWrite8(uint8_t ad, uint8_t reg, uint8_t val);
uint8_t servoRead32(uint8_t ad, uint8_t reg, uint32_t * val);
uint8_t servoWrite32(uint8_t ad, uint8_t reg, uint32_t val);

/*
 * motor.c
 */

/* init motor */
uint8_t initMotor(void);

/* set motor direction */
uint8_t setMotorDirection(uint8_t motor, enum MotorDirection val);

/* set motor speed */
uint8_t setMotorSpeed(uint8_t motor, uint16_t val);

#endif /* SOURCES_PROGRAM_H_ */
