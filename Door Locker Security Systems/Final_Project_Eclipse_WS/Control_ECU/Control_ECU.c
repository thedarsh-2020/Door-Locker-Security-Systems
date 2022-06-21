/**************************************************************************************************
 *
 * Author      : Mustafa Muhammad
 *
 * Description : Source file for Door Locker Security Systems (Control ECU)
 *
 **************************************************************************************************/

#include "uart.h"
#include "Buzzer.h"
#include "dc-motor.h"
#include <avr/io.h>
#include "Timers.h"
#include "Control_ECU.h"
#include "external_eeprom.h"
#include <util/delay.h>
#include "std_types.h"

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

extern volatile uint8 timer_finish;

/*******************************************************************************
 *                                Static Variables                             *
 *******************************************************************************/

static volatile uint8 uart_rx;
static volatile uint16 current_password;
static volatile uint16 new_password;
static volatile uint16 re_enter_password;
static volatile uint16 eeprom_password;
static volatile uint16 check_password;
const static volatile uint16 eeprom_first_location = 0x0311;
static volatile uint16 eeprom_last_location;
static volatile uint8 pass_counter;

/*
 * Setting Timer Configurations with:
 * - Selecting Timer0
 * - Set Pre-Scaler to 1024
 * - Select Over-Flow Mode
 */
static Timer_ConfigType Timer_Config = {Timer_0, Timer_Prescaler_1024, Timer0_Ovf_Mode, 0, 0, 0, 0, 0};

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for send order to HMI_ECU to display HOME SCREEN on LCD and get user selection
 */
uint8 home_screen(void)
{
	uart_rx = 0;
	UART_sendByte(IAM_READY);				/* Send IAM_READY byte to HMI_ECU to ask it to send */
	for(;;)
	{
		uart_rx = UART_recieveByte();
		if((uart_rx == '+') || (uart_rx == '-'))
		{
			break;
		}
	}
	return uart_rx;
}

/*
 * Description :
 * Function responsible for getting password from user till '='
 */
void enter_pass(void)
{
	uart_rx = 0;
	current_password = 0;
	UART_sendByte(IAM_READY);				/* Send IAM_READY byte to HMI_ECU to ask it to send */
	for(;;)
	{
		uart_rx = UART_recieveByte();
		if(uart_rx == '=')
		{
			break;
		}
		else
		{
			current_password = (current_password * 10) + uart_rx;
		}
	}
}

/*
 * Description :
 * Function responsible for getting password from EEPROM and check it with entered password from user
 */
uint8 check_pass(void)
{
	uint8 temp = 0;
	uint16 i;
	check_password = 0;
	for(i = eeprom_last_location; i >= eeprom_first_location; i--)
	{
		EEPROM_readByte(i, &temp);
		check_password = (check_password * 10) + temp;
	}
	if(current_password == check_password)
	{
		return MATCH;
	}
	return NOT_MATCH;
}

/*
 * Description :
 * Function responsible for getting password from user till '='
 */
void create_pass(void)
{
	uart_rx = 0;
	new_password = 0;
	UART_sendByte(IAM_READY);				/* Send IAM_READY byte to HMI_ECU to ask it to send */
	for(;;)
	{
		uart_rx = UART_recieveByte();
		if(uart_rx == '=')
		{
			break;
		}
		else
		{
			new_password = (new_password * 10) + uart_rx;
		}
	}
}

/*
 * Description :
 * Function responsible for getting password from user till '=' and check it,
 * if it match with the password, will store in EEPROM
 */
uint8 re_enter_pass(void)
{
	uart_rx = 0;
	re_enter_password = 0;
	UART_sendByte(IAM_READY);					/* Send IAM_READY byte to HMI_ECU to ask it to send */
	for(;;)
	{
		uart_rx = UART_recieveByte();
		if(uart_rx == '=')
		{
			break;
		}
		else
		{
			re_enter_password = (re_enter_password * 10) + uart_rx;
		}
	}
	if(new_password == re_enter_password)
	{
		store_pass();										/* Getting password from EEPROM to check it*/
		return MATCH;
	}
	return NOT_MATCH;
}

/*
 * Description :
 * Function responsible for storing password in EEPROM
 */
void store_pass(void)
{
	eeprom_password = new_password;
	eeprom_last_location = eeprom_first_location;
	while(eeprom_password != 0)
	{
		EEPROM_writeByte(eeprom_last_location, (eeprom_password % 10));
		_delay_ms(10);
		eeprom_last_location++;
		eeprom_password = eeprom_password / 10;
	}
	eeprom_last_location--;
}

/*
 * Description :
 * Function responsible for creating password option
 */
void create_pass_option(void)
{
	for(;;)
	{
		UART_sendByte(CREATE_PASS);
		create_pass();

		UART_sendByte(RE_ENTER_PASS);
		if(re_enter_pass() == MATCH)
		{
			UART_sendByte(PASS_CREATED);
			Timer_Config.T_ovf_counter = 8;				/* Timer delay for 2 Second */
			Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
			while(timer_finish == 0){}					/* Waiting till timer is finished */
			timer_finish = 0;							/* Reset timer variable after delay is finished*/
			break;
		}
		else
		{
			UART_sendByte(PASS_UNMATCH);
			Timer_Config.T_ovf_counter = 8;				/* Timer delay for 2 Second */
			Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
			while(timer_finish == 0){}					/* Waiting till timer is finished */
			timer_finish = 0;							/* Reset timer variable after delay is finished*/
		}
	}
}

/*
 * Description :
 * Function responsible for opening door option
 */
void open_door_option(void)
{
	for(;;)
	{
		UART_sendByte(ENTER_PASS);
		enter_pass();

		if(check_pass() == MATCH)
		{
			pass_counter = 0;							/* Reset counter of wrong entered password */
			UART_sendByte(OPENING_DOOR);
			DcMotor_Rotate(CW);							/* Turn ON DC-Motor Clock-wise to open the Door */
			Timer_Config.T_ovf_counter = 57;			/* Timer delay for 15 Second */
			Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
			while(timer_finish == 0){}					/* Waiting till timer is finished */
			timer_finish = 0;							/* Reset timer variable after delay is finished*/

			DcMotor_Rotate(STOP);						/* Stop DC-Motor */
			Timer_Config.T_ovf_counter = 4;				/* Timer delay for 1 Second */
			Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
			while(timer_finish == 0){}					/* Waiting till timer is finished */
			timer_finish = 0;							/* Reset timer variable after delay is finished*/

			UART_sendByte(CLOSING_DOOR);
			DcMotor_Rotate(A_CW);						/* Turn ON DC-Motor Anti-Clock-wise to close the Door */
			Timer_Config.T_ovf_counter = 57;			/* Timer delay for 15 Second */
			Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
			while(timer_finish == 0){}					/* Waiting till timer is finished */
			timer_finish = 0;							/* Reset timer variable after delay is finished*/

			DcMotor_Rotate(STOP);
			Timer_Config.T_ovf_counter = 4;				/* Timer delay for 1 Second */
			Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
			while(timer_finish == 0){}					/* Waiting till timer is finished */
			timer_finish = 0;							/* Reset timer variable after delay is finished*/

			return;
		}
		else
		{
			UART_sendByte(PASS_UNMATCH);
			Timer_Config.T_ovf_counter = 8;				/* Timer delay for 2 Second */
			Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
			while(timer_finish == 0){}					/* Waiting till timer is finished */
			timer_finish = 0;							/* Reset timer variable after delay is finished*/

			pass_counter++;								/* increase counter of wrong entered password */

			/* In case user is entered wrong password 3 times, BUZZER will ON for 1 min */
			if(pass_counter == 3)
			{
				pass_counter = 0;						/* Reset counter of wrong entered password */

				UART_sendByte(BUZZER_ON);
				buzzer_on();							/* Turning ON Buzzer after 3 timer user entered wrong password */
				Timer_Config.T_ovf_counter = 229;		/* Timer delay for 1 Min */
				Timer_init(&Timer_Config);				/* Timer Init-ialization with structure */
				while(timer_finish == 0){}				/* Waiting till timer is finished */
				timer_finish = 0;						/* Reset timer variable after delay is finished*/

				buzzer_off();							/* Turning OFF Buzzer after 1 min */
				Timer_Config.T_ovf_counter = 4;			/* Timer delay for 1 Second */
				Timer_init(&Timer_Config);				/* Timer Init-ialization with structure */
				while(timer_finish == 0){}				/* Waiting till timer is finished */
				timer_finish = 0;						/* Reset timer variable after delay is finished*/

				return;
			}
		}
	}
}

/*
 * Description :
 * Function responsible for changing password option
 */
void change_pass_option(void)
{
	for(;;)
	{
		UART_sendByte(ENTER_PASS);
		enter_pass();
		if(check_pass() == MATCH)
		{
			pass_counter = 0;
			for(;;)
			{
				UART_sendByte(CREATE_PASS);
				create_pass();

				UART_sendByte(RE_ENTER_PASS);
				if(re_enter_pass() == MATCH)
				{
					UART_sendByte(PASS_CHANGED);
					Timer_Config.T_ovf_counter = 8;			/* Timer delay for 2 Second */
					Timer_init(&Timer_Config);				/* Timer Init-ialization with structure */
					while(timer_finish == 0){}				/* Waiting till timer is finished */
					timer_finish = 0;						/* Reset timer variable after delay is finished*/
					break;
				}
				else
				{
					UART_sendByte(PASS_UNMATCH);
					Timer_Config.T_ovf_counter = 8;			/* Timer delay for 2 Second */
					Timer_init(&Timer_Config);				/* Timer Init-ialization with structure */
					while(timer_finish == 0){}				/* Waiting till timer is finished */
					timer_finish = 0;						/* Reset timer variable after delay is finished*/
				}
			}
			return;
		}

		else
		{
			UART_sendByte(PASS_UNMATCH);
			Timer_Config.T_ovf_counter = 8;					/* Timer delay for 2 Second */
			Timer_init(&Timer_Config);						/* Timer Init-ialization with structure */
			while(timer_finish == 0){}						/* Waiting till timer is finished */
			timer_finish = 0;								/* Reset timer variable after delay is finished*/

			pass_counter++;									/* increase counter of wrong entered password */

			/* In case user is entered wrong password 3 times, BUZZER will ON for 1 min */
			if(pass_counter == 3)
			{
				pass_counter = 0;							/* Reset counter of wrong entered password */

				UART_sendByte(BUZZER_ON);
				buzzer_on();								/* Turning ON Buzzer after 3 timer user entered wrong password */
				Timer_Config.T_ovf_counter = 229;			/* Timer delay for 1 Min*/
				Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
				while(timer_finish == 0){}					/* Waiting till timer is finished */
				timer_finish = 0;							/* Reset timer variable after delay is finished*/

				buzzer_off();								/* Turning OFF Buzzer after 1 min */
				Timer_Config.T_ovf_counter = 4;				/* Timer delay for 11 Second */
				Timer_init(&Timer_Config);					/* Timer Init-ialization with structure */
				while(timer_finish == 0){}					/* Waiting till timer is finished */
				timer_finish = 0;							/* Reset timer variable after delay is finished*/

				return;
			}
		}
	}

}
