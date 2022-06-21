/**************************************************************************************************
 *
 * Author      : Mustafa Muhammad
 *
 * Description : Main file for Door Locker Security Systems (Control ECU)
 *
 **************************************************************************************************/

#include "uart.h"
#include "Buzzer.h"
#include "dc-motor.h"
#include <avr/io.h>
#include "Timers.h"
#include "Control_ECU.h"
#include "twi.h"
#include <avr/interrupt.h>
#include"common_macros.h"

/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/

int main(void)
{
	/* Init-ialize UART driver with:
	 * 8 Bit Data
	 * Baud-rate = 9600 Bits/Sec.
	 * One Stop Bit
	 * Disable Parity
	 */
	UART_ConfigType UART_Config = {Bits_8, BR_9600, Stop_1_Bit, Parity_Disable};
	UART_init(&UART_Config);

	/* Init-ialize the TWI/I2C Driver
	 * Bit Rate = 400.000 K-bps
	 * Slave Address = 0b00000010
	 * No Pre-scaler
	 */
	TWI_ConfigType TWI_Config = {0x02, 0b00000010, TWI_Pre_scaler_0};
	TWI_init(&TWI_Config);

	/* Init-ialize Buzzer Driver */
	buzzer_init();

	/* Enable global interrupts in MC by setting the I-Bit */
	SREG  |= (1<<7);

	/* Init-ialize Motor Driver */
	DcMotor_Init();

	/* Init-ialize call back function */
	Timer0_setCallBack(Timer0_DeInit);

	/* Wait until HMI-ECU is ready to receive */
	while(UART_recieveByte() != IAM_READY){}

	/* Create password in first use of application */
	create_pass_option();

	for(;;)
	{
		/* Go to HOME SCREEN to display orders after creating password */
		UART_sendByte(HOME_SCREEN);

		/* according to user input going to each option */
		if(home_screen() == '+')
		{
			open_door_option();
		}

		else
		{
			change_pass_option();
		}
	}
}

