 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 *******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * enum to define the Pres-caler for TWI
 * Pre-scaler 0    = 0
 * Pre-scaler 4    = 1
 * Pre-scaler 16   = 2
 * Pre-scaler 64   = 3
 */
typedef enum
{
	TWI_Pre_scaler_0, TWI_Pre_scaler_4, TWI_Pre_scaler_16, TWI_Prescaler_64
}TWI_Prescaler;

/*
 * TWI(I2C) Config. Parameters Structure:
 * - Bit Rate
 * - MC address in case it's slave device
 * - TWI Pre-scaler (0, 4, 16, 64)
 */
typedef struct{
	uint8 Bit_Rate;
	uint8 Slave_Address;
	TWI_Prescaler Prescaler;
}TWI_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Init-ialize the TWI device with configuration from structure
 */
void TWI_init						(const TWI_ConfigType * TWI_Config_Ptr);

/*
 * Description :
 * Function responsible for Enable TWI & send start bit
 */
void TWI_start						(void);

/*
 * Description :
 * Function responsible to send stop bit
 */
void TWI_stop						(void);

/*
 * Description :
 * Function responsible to send data
 */
void TWI_writeByte					(uint8 data);

/*
 * Description :
 * Function responsible to receive ACK from slave after sending data
 */
uint8 TWI_readByteWithACK			(void);

/*
 * Description :
 * Function responsible to receive NACK from slave after sending data
 */
uint8 TWI_readByteWithNACK			(void);

/*
 * Description :
 * Function responsible to get status bits
 */
uint8 TWI_getStatus					(void);

#endif /* TWI_H_ */
