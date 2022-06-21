/******************************************************************************
 *
 * Module: DC Motor
 *
 * Description: Source file for Door DC-Motor
 *
 *******************************************************************************/

#include "dc-motor.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for DC-Motor Init-ialization
 */
void DcMotor_Init(void)
{
	/* Set DC-Motor Pins as O/P */
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);

	/* Set Initial state for the motor to STOP state */
	GPIO_writePin(PORTD_ID, PIN6_ID, LOGIC_LOW);
	GPIO_writePin(PORTD_ID, PIN7_ID, LOGIC_LOW);

}

/*
 * Description :
 * Function responsible for DC-Motor state
 */
void DcMotor_Rotate(DcMotor_State state)
{
	/* Set DC-Motor pins according to its state (CW, A-CW & STOP) */
	PORTD = (PORTD & 0X3F) | ((state & 0X03) << 6);
}
