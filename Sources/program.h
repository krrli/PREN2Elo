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
#include "test.h"

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
enum serialCommands {
	START = 0x80, // RPi to FD
	ROMAN_NUMERAL_REQUEST = 0x40, // FD to RPi
	CURVE = 0x08, // FD to RPi
	SECOND_ROUND = 0x09, // FD to RPi
	PAUSE = 0xB0, // RPi to FD
	RESUME = 0x70, // RPi to FD
};
enum serialDebugLite {
	DEBUG_ERROR_INIT_MOTOR = 0xC1,
	DEBUG_ERROR_INIT_SERVO = 0xC2,
	DEBUG_ERROR_INIT_TOF = 0xC3,
	DEBUG_ERROR_END_LOOP_REACHED = 0xC4,
	DEBUG_ERROR_SET_MOTOR_SPEED = 0xC5,
	DEBUG_ERROR_SET_MOTOR_DIRECTION = 0xC6,
	DEBUG_ERROR_SET_BRUSHLESS = 0xC7,
	DEBUG_ERROR_SET_SERVO = 0xC8,
	DEBUG_ERROR_GET_TOF_VALUE = 0xC9,
	DEBUG_ERROR_WRONG_BUTTON_NUMBER = 0xCA,
	DEBUG_ERROR_STOPPING_BECAUSE_I2C_ERROR = 0xCB,
	DEBUG_ERROR_REINIT_I2C = 0xCD,
	DEBUG_TRY_INIT_MOTOR = 0xD1,
	DEBUG_TRY_INIT_SERVO_AND_TOF = 0xD2,
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
	CURVE_DIST = DISTANCE_TO_WALL, BUTTON1_A = 0xA0, // todo: change values
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
	MOTOR_CORRSPEED = 50, MOTOR_MAXSPEED = 100
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
#define TOF_MEASURE_CONTINUOUS 1
#define NUMBER_OF_SENSORS 5 // max 6
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
	SERVO_STRAIGHT,
	SERVO_SIDEWAYS,
	SERVO_CORR_LEFT,
	SERVO_CORR_RIGHT,
	SERVO_CORR_FRONT,
	SERVO_CORR_REAR,
	SERVO_CIRCLE
};
#define USE_SERVO_SHIELD 0

/*
 * declarations for the motor driver boards
 */
#define INIT_MOTOR_DIRECTION_1	0
#define INIT_MOTOR_DIRECTION_2	1
#define NUMBER_OF_MOTOR 4

enum MotorDirection {
	MOTOR_FORWARD, MOTOR_BACKWARD
};
enum Motor {
	MOTOR_FRONT_RIGHT = 2,
	MOTOR_FRONT_LEFT = 0,
	MOTOR_REAR_RIGHT = 3,
	MOTOR_REAR_LEFT = 1
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

/* new main loop */
void mainLoop2(void);

#define NEW_SERIAL_INT_ENABLED 1
#define NEW_SERIAL_RASPI_ENABLED 1
#define NEW_SERIAL_PAUSE_ENABLED 0
#define NEW_SERIAL_INT_DEBUG_ENABLED 0

#define NEW_MAIN_LOOP 1

#define NEW_DIFF_MAX 10
#define NEW_DIST_TO_WALL 132
#define NEW_DIST_TO_WALL_MIN 122
#define NEW_DIST_TO_WALL_MAX 142

enum newDriveDistance {
	NEW_CURVE_DIST_A = 290,
	NEW_CURVE_DIST_B=290,
	NEW_DIST_END = 350,
	NEW_BUTTON1_A = 345,
	NEW_BUTTON2_A = 294,
	NEW_BUTTON3_A = 243,
	NEW_BUTTON4_A = 182,
	NEW_BUTTON5_A = 136,
	NEW_BUTTON1_B = 121,
	NEW_BUTTON2_B = 165,
	NEW_BUTTON3_B = 220,
	NEW_BUTTON4_B = 274,
	NEW_BUTTON5_B = 325
};

enum NewMotorSpeed {
	NEW_MOTOR_CORRSPEED = 25,
	NEW_MOTOR_MAXSPEED = 100,
	NEW_MOTOR_HALFSPEED = 50,
	NEW_MOTOR_BUTTON_SPEED = 10,
	NEW_MOTOR_BUTTON_SPEED_2 = 30
};

#define NEW_CORR_ENABLED 1

#define NEW_DIFF_CORR_ENABLED 0
#define NEW_DIST_CORR_ENABLED 0
#define NEW_DOUBLE_DIST_CORR_ENABLED 0
#define NEW_BOTH_CORR_ENABLED 1
#define NEW_CURVE_CORR_ENABLED 1

#define NEW_CORR_EXPERIMANTAL_ENABLED 0

#define NEW_CENT_ENABLED 1 // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define NEW_CENT_WITHOUT_SWITCH_ENABLED 0 // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define NEW_CORR_TIME 100 // value in ms

#define NEW_BLIND_TIME 700 // value in ms
#define NEW_BLIND_TIME_BACK 0
#define NEW_CURVE_BLIND_TIME 100

#define NEW_CURVE_DRIVE_OVER_TIME 350 // value in ms
#define NEW_CURVE_DETECT_DISTANCE 250
#define NEW_CURVE_DETECT_TOF5_ENABLED 1 // todo

#define NEW_SECOND_ROUND_ENABLED 0
#define NEW_SECOND_ROUND_TURN_TIME 2000
#define NEW_SECOND_ROUND_DRIVE_TO_START_TIME 2000

#define NEW_FEDER_ENABLED 1
#define NEW_FEDER_SPEED 30
#define NEW_FEDER_TIME 600

#define NEW_DRIVE_INTO_BUTTON_TIME 500 // value in ms

#define NEW_WAIT_TIME_DEFAULT 0 // value in ms

#define NEW_WAIT_TIME_SERVO 200 // value in ms

// chose only one!
#define PID_CORR_SPEED 0 // regulated over time
#define PID_CORR_SERVO 0 // regulated over time
#define PID_CORR_DIRECTION 0 // regulated over time
#define PID_CORR_SERVO_DIRECTION 1 // regulated over servo angle
#define PID_CORR_SIMPLE 0 // drive away from wall, if too near, else drive towards wall
#define PID_CORR_SET_SPEED 0 // regulate motor speed directly

#define PID_WAIT_TIME_SERVO_CORR 0
#define PID_STOP_ON_I2C_ERROR 1

#define PID_CORR_SIMPLE_CORR_PERCENT 30
#define PID_CORR_SIMPLE_MIN_PID_VAL 5

#define PID_P 1 // PID diff
#define PID_P_DIV 2
#define PID_I 1
#define PID_I_DIV 10
#define PID_D 1
#define PID_D_DIV 10
#define PID_MAX_CORR_TIME 30 // max corr time in ms / max servo corr val / max speed difference in %

#define PID_DIST_P 1 // PID dist
#define PID_DIST_P_DIV 20
#define PID_DIST_I 1
#define PID_DIST_I_DIV 1000
#define PID_DIST_D 1
#define PID_DIST_D_DIV 3
#define PID_DIST_MAX_CORR_TIME 30 // max corr time / max servo corr val

#define PID_BOTH_DIST_P_MULT 16//1
#define PID_BOTH_DIST_P_DIV 1
#define PID_BOTH_DIST_I_MULT 0
#define PID_BOTH_DIST_I_DIV 1
#define PID_BOTH_DIST_D_MULT 0
#define PID_BOTH_DIST_D_DIV 1

#define PID_BOTH_DIFF_P_MULT 16//1
#define PID_BOTH_DIFF_P_DIV 1
#define PID_BOTH_DIFF_I_MULT 0
#define PID_BOTH_DIFF_I_DIV 1
#define PID_BOTH_DIFF_D_MULT 0
#define PID_BOTH_DIFF_D_DIV 1

#define PID_BOTH_MAX_CORR_VAL 320

#define TOF1_A_OFFSET 0//(-6)
#define TOF1_B_OFFSET 0//(-6)

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

uint8_t setServoDriveBack(enum parcourType type);

uint8_t setServoPID(enum ServoDirection dir, uint8_t corr_dir,
		uint16_t corr_val);

void setServoPidBoth(int32_t pid_val_dist, int32_t pid_val_diff,
		enum parcourType type, uint8_t state);

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
uint8_t setMotorSpeed(uint8_t motor, uint8_t val);

uint8_t blockMotor(uint8_t motor);

uint8_t unblockMotor(uint8_t motor);

#endif /* SOURCES_PROGRAM_H_ */
