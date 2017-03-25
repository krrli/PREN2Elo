#include "program.h"

/*
 * global variables for serial communication
 */
volatile uint8_t lastSentCmd[NUMBER_OF_SERIAL_PORTS];

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
	/* init variables for serial communication */
	lastSentCmd[PC] = 0x00;
	lastSentCmd[RasPi] = 0x00;

	/* init variables for main loop */
	state = STOPPED;
	stateBak = STOPPED;
	stateCurr = STOPPED;
	wheelPos = STRAIGHT;
	type = SW_Parc_GetVal();
	endReached = NOT_REACHED;
	distance = CURVE_DIST;

	/* init variables for buttons */
	button = BUTTON3;
	btnchk = BUTTON_UNCHECKED;

	/* temporary simulation of parcour to test serial interface protocol */
	simulateParcour();

	/* init motor */
	// todo: set direction like drive forward, set speed to 0

	/* init servoshield, servos, brushless */
	// todo: init brushless
	// todo: init servos for straight wheels

	/* init tof sensors */
	initToF();

	/* start mainloop */
	mainLoop();

	for (;;) {
		/* fallback loop, should never be reached */
	}
}

void serialRxInt(uint8_t ch, uint8_t port) {
	switch (ch) {
	/* commands from raspi */
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

	/* answers from raspi */
	case ACKNOWLEDGE:
		break;
	case ERROR:
		serialSend(lastSentCmd[port], port);
		break;
	case BUTTON1:
	case BUTTON2:
	case BUTTON3:
	case BUTTON4:
	case BUTTON5:
		if (lastSentCmd[port] == ROMAN_NUMERAL_REQUEST) {
			serialSend(ACKNOWLEDGE, port);
			button = ch;
			btnchk = BUTTON_CHECKED;
		} else {
			serialSend(ERROR, port);
		}
		break;

	/* illegal commands from raspi */
	case ROMAN_NUMERAL_REQUEST:
	case CURVE:
	default:
		serialSend(ERROR, port);
	}
}

void serialSend(uint8_t ch, uint8_t port) {
	/* send char ch to port port */
	switch (port) {
	case PC:
		CLS1_SendChar(ch);
		break;
	case RasPi:
		CLS2_SendChar(ch);
		break;
	}

	/* save char ch as last sent command */
	lastSentCmd[port] = ch;
}

void simulateParcour(void) {
	/* wait 5 seconds */
	WAIT1_Waitms(5000);

	/* send CURVE signal to raspi */
	serialSend(CURVE, PC);
	serialSend(CURVE, RasPi);

	/* wait 5 seconds */
	WAIT1_Waitms(5000);

	/* send ROMAN_NUMERAL_REQUEST to raspi */
	serialSend(ROMAN_NUMERAL_REQUEST, PC);
	serialSend(ROMAN_NUMERAL_REQUEST, RasPi);

	/* end loop */
	for (;;) {
	}
}

void mainLoop(void) {
	for (;;) {
		/* check centrifuge state */
		// todo: check state of SW_Zent, set brushless to fixed value or off

		/* if state changed, set servo and motor outputs */
		if (stateCurr != state) {
			switch (state) {
			case STOPPED:
				/* do nothing */
				break;
			case DRIVE_FORWARD:
			case DRIVE_BACKWARD:
				/* set servos */
				// todo: if wheelPos != STRAIGHT, turn servos, change wheelPos, wait

				/* set motors */
				// todo: set motor directions (check forward/backwards) and speeds
				break;
			case DRIVE_LEFT:
			case DRIVE_RIGHT:
				/* set servo */
				// todo: if wheelPos != SIDEWAYS, turn servos, change wheelPos, wait

				/* set motor */
				// todo: set motor directions (check left/right) and speeds

				/* set distance */
				// todo: set distance and define to which wall
				break;
			}
			stateCurr = state;

		/* if state did not change */
		} else {
			switch (state) {
			case STOPPED:
				/* do nothing */
				break;
			case DRIVE_FORWARD:
				/* drive straight */
				// todo: right sensor front (?) to short distance, decrease motor speed left for defined time

				/* detect end */
				// todo: detect end, change to drive left or right mode depending on parcour type
				//     send signal curve to raspi
				break;
			case DRIVE_BACKWARD:
				/* if end reached: drive into button */
				// todo: if end reached, drive fixed distance into button

				/* else: drive straight */
				// todo: right sensor front (?) to short distance, decrease motor speed left for defined time

				/* detect end */
				// todo: detect end and change to drive left or right for button pressing depending on parcour type
				//     set endReached to reached
				//     ask raspi for roman number
				//     wait, to give raspi time to answer
				break;
			case DRIVE_LEFT:
				/* drive straight */
				// todo: right sensor front - right sensor back > 0 ==> decrease motor speed front for defined time

				/* detect end via fixed distance */
				// todo: drive until target distance is reached
				//     change to drive backward mode
				break;
			case DRIVE_RIGHT:
				/* drive straight */
				// todo: left sensor front - left sensor back > 0 ==> decrease motor speed front for defined time

				/* detect end via fixed distance */
				// todo: drive until target distance is reached
				//     change to drive backward mode
				break;
			}
		}
		/* give some time until next run */
		WAIT1_Waitms(10);
	}
}
