 /******************************************************************************
 *
 * Module: UART
 *
 * Description: Header file for the UART AVR driver
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * enum to define Number of Bit Data
 */
typedef enum
{
	Bits_5, Bits_6, Bits_7, Bits_8
}UART_BitDataNum;

/*
 * enum to define Baud Rate
 */
typedef enum
{
	BR_4800 = 4800, BR_9600 = 9600, BR_14400 = 14400, BR_19200 = 19200, BR_38400 = 38400
}UART_BaudRate;

/*
 * enum to define Number of Stop Bits
 */
typedef enum
{
	Stop_1_Bit, Stop_2_Bit
}UART_StopBitsNum;

/*
 * enum to Enable(EVEN, ODD)/Disable Parity check
 */
typedef enum
{
	Parity_Disable, Parity_Enable_Even = 2, Parity_Enable_Odd
}UART_Parity;

/*
 * UART Config. Parameters Structure:
 * - Number of Bit Data
 * - Baud Rate
 * - Number of Stop Bits
 * - Parity Enable/Disable
 */
typedef struct{
	UART_BitDataNum Bit_Data;
	UART_BaudRate Baud_Rate;
	UART_StopBitsNum ST_Bit;
	UART_Parity Parity_En_Dis;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Init-ialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * UART_Config_Ptr);

/*
 * Description :
 * Function responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Function responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Function for sending the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Function for receiving the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
