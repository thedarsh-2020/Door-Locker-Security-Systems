 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * Description: Header file for the External EEPROM Memory
 *
 *******************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for send address of memory to write data in it
 */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);

/*
 * Description :
 * Function responsible for send address of memory to read data from it
 */
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);
 
#endif /* EXTERNAL_EEPROM_H_ */
