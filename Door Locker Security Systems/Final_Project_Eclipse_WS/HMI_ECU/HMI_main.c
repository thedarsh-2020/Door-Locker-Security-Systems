/**************************************************************************************************
 *
 * Author      : Mustafa Muhammad
 *
 * Description : Main file for Door Locker Security Systems (HMI ECU)
 *
 **************************************************************************************************/

#include "HMI_ECU.h"
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "std_types.h"

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

/*
 * Variables Declaration
 * received_temp : Receive order from Control ECU to
 * display orders on LCD & take inputs from user
 */
static uint8 received_temp;

/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/

int main(void)
{
	LCD_init();							/* Init-ialize LCD */

	/* Init-ialize UART driver with:
	 * 8 Bit Data
	 * Baud-rate = 9600 Bits/Sec
	 * One Stop Bit
	 * Disable Parity
	 */
	UART_ConfigType UART_Config = {Bits_8, BR_9600, Stop_1_Bit, Parity_Disable};
	UART_init(&UART_Config);

	/* Send IAM_READY byte to Control_ECU to ask it to send orders */
	UART_sendByte(IAM_READY);

	for(;;)
	{
		received_temp = UART_recieveByte();

		switch(received_temp)
		{
		case ENTER_PASS:
			/* Wait until Control-ECU is ready to receive */
			while(UART_recieveByte() != IAM_READY){}
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Please EnterPass");
			LCD_displayStringRowColumn(1, 0, "then = : ");
			take_pass();
			break;

		case CREATE_PASS:
			/* Wait until Control-ECU is ready to receive */
			while(UART_recieveByte() != IAM_READY){}
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Enter New Pass");
			LCD_displayStringRowColumn(1, 0, "then = : ");
			take_pass();
			break;

		case RE_ENTER_PASS:
			/* Wait until Control-ECU is ready to receive */
			while(UART_recieveByte() != IAM_READY){}
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Re-Enter Pass");
			LCD_displayStringRowColumn(1, 0, "then = : ");
			take_pass();
			break;

		case PASS_CREATED:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Pass Created");
			break;

		case PASS_CHANGED:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Pass Changed");
			break;

		case PASS_UNMATCH:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Pass not match");
			break;

		case HOME_SCREEN:
			/* Wait until Control-ECU is ready to receive */
			while(UART_recieveByte() != IAM_READY){}
			home_screen();
			break;

		case OPENING_DOOR:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Door is Opening.");
			break;

		case CLOSING_DOOR:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Door is Closing.");
			break;

		case BUZZER_ON:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "WARNING  WARNING");
			LCD_displayStringRowColumn(1, 0, "WARNING  WARNING");
			break;

		default:
			break;
		}
	}
}
