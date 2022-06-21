/******************************************************************************
 *
 * Module: Buzzer
 *
 * Description: Source file for Buzzer
 *
 *******************************************************************************/

#include "Buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initiate buzzer pin direction and its initial state
 */
void buzzer_init(void)
{
	/* setup pin direction as output */
	GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);

	/* set buzzer initial state as turn it off */
	GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_LOW);
}

/*
 * Description :
 * Function responsible for turn on buzzer
 */
void buzzer_on(void)
{
	GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_HIGH);
}

/*
 * Description :
 * Function responsible for turn off buzzer
 */
void buzzer_off(void)
{
	GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_LOW);
}
