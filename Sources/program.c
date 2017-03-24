#include "program.h"

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
	/* init variables for main loop */
	state = STOPPED;
	stateBak = STOPPED;
	stateCurr = STOPPED;
	wheelPos = STRAIGHT; // todo: init servos for straight wheels
	type = PARCOUR_A; // todo: check switch: type = value of switch port
	endReached = NOT_REACHED;
	distance = CURVE_DIST;
	/* init variables for buttons */
	button = BUTTON3;
	btnchk = BUTTON_UNCHECKED;
	/* init tof sensors */
	//initToF();
	/* temporary simulation of parcour to test serial interface protocol */
	//simulateParcour();
	/* start mainloop */
	mainLoop();
	/* fallback loop, should never be reached */
	for (;;)
		;
}

void serialRxInt(uint8_t ch, uint8_t port) {
	switch (ch) {
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
	case ACKNOWLEDGE:
	case ERROR:
		break;
	case BUTTON1:
	case BUTTON2:
	case BUTTON3:
	case BUTTON4:
	case BUTTON5:
		serialSend(ACKNOWLEDGE, port);
		button = ch;
		btnchk = BUTTON_CHECKED;
		break;
	case ROMAN_NUMERAL_REQUEST:
	case CURVE:
	default:
		serialSend(ERROR, port);
	}
}

void serialSend(uint8_t ch, uint8_t port) {
	switch (port) {
	case PC:
		CLS1_SendChar(ch);
		break;
	case RasPi:
		CLS2_SendChar(ch);
		break;
	}
}

void simulateParcour(void) {
	WAIT1_Waitms(2000);
	serialSend(CURVE, PC);
	serialSend(CURVE, RasPi);
	WAIT1_Waitms(2000);
	serialSend(ROMAN_NUMERAL_REQUEST, PC);
	serialSend(ROMAN_NUMERAL_REQUEST, RasPi);
}

void mainLoop(void) {
	for (;;) {
		if (stateCurr != state) { // todo
			switch (state) {
			case STOPPED: /* do nothing */
				break;
			case DRIVE_FORWARD:
			case DRIVE_BACKWARD:
				// if wheelPos != STRAIGHT, turn servos, change wheelPos, wait
				// set motor directions (check forward/backwards) and speeds
				break;
			case DRIVE_LEFT:
			case DRIVE_RIGHT:
				// if wheelPos != SIDEWAYS, turn servos, change wheelPos, wait
				// set motor directions (check left/right) and speeds
				// set distance
				break;
			}
			stateCurr = state;
		} else { // todo
			switch (state) {
			case STOPPED: /* do nothing */
				break;
			case DRIVE_FORWARD:
				// right sensor front (?) to short distance, decrease motor speed left for defined time
				// detect end, change to drive left or right mode depending on parcour type
				//     send signal curve to raspi
				break;
			case DRIVE_BACKWARD:
				// if end reached, drive fixed distance into button, else:
				//     right sensor front (?) to short distance, decrease motor speed left for defined time
				//     detect end and change to drive left or right for button pressing depending on parcour type
				//         set endReached to reached
				//         ask raspi for roman number
				//         wait, to give raspi time to answer
				break;
			case DRIVE_LEFT:
				// right sensor front - right sensor back > 0 ==> decrease motor speed front for defined time
				// drive until target distance is reached
				//     change to drive backward mode
				break;
			case DRIVE_RIGHT:
				// left sensor front - left sensor back > 0 ==> decrease motor speed front for defined time
				// drive until target distance is reached
				//     change to drive backward mode
				break;
			}
		}
		WAIT1_Waitms(10);
	}
}
