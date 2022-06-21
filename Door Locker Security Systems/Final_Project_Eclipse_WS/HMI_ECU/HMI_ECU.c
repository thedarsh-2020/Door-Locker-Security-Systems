/**************************************************************************************************
 *
 * Author      : Mustafa Muhammad
 *
 * Description : Source file for Door Locker Security Systems (HMI ECU)
 *
 **************************************************************************************************/

#include "uart.h"
#include "HMI_ECU.h"
#include "lcd.h"
#include "keypad.h"
#include "std_types.h"
#include <util/delay.h>

/*******************************************************************************
 *                                Static Variables                             *
 *******************************************************************************/

/*
 * Variables Declaration
 * key : returned character from Keypad
 */
static volatile uint8 key;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for take a password from user
 * then send it byte by byte to Control_ECU by UART and display '*' on LCD
 */
void take_pass(void)
{
	for(;;)
	{
		/* get pressed button from keypad */
		key = KEYPAD_getPressedKey();

		/* send pressed buttons to Control-ECU */
		UART_sendByte(key);

		/* check if user finished password entering or not */
		if(key == '=')
		{
			return;
		}

		/* display the pressed keypad switch as '*' */
		LCD_displayCharacter('*');

		/* Press time */
		_delay_ms(500);
	}
}

/*
 * Description :
 * Function responsible for take selected option from user
 */
void home_screen(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "+ : Open Door");
	LCD_displayStringRowColumn(1, 0, "- : Change Pass");
	key = KEYPAD_getPressedKey();
	UART_sendByte(key);
}
