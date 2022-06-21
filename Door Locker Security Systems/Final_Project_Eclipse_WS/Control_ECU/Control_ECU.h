/**************************************************************************************************
 *
 * Author      : Mustafa Muhammad
 *
 * Description : Header file for Door Locker Security Systems (Control ECU)
 *
 **************************************************************************************************/

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

#include "std_types.h"
#include "Timers.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define IAM_READY			0
#define ENTER_PASS			1
#define CREATE_PASS			2
#define RE_ENTER_PASS		3
#define PASS_CREATED		4
#define PASS_CHANGED		5
#define PASS_UNMATCH		6
#define HOME_SCREEN			7
#define OPENING_DOOR		8
#define CLOSING_DOOR		9
#define BUZZER_ON			10

#define MATCH				1
#define NOT_MATCH			0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for send order to HMI_ECU to display HOME SCREEN on LCD and get user selection
 */
uint8 home_screen			(void);

/*
 * Description :
 * Function responsible for getting password from EEPROM and check it with entered password from user
 */
uint8 check_pass			(void);

/*
 * Description :
 * Function responsible for getting password from user till '='
 */
void enter_pass				(void);

/*
 * Description :
 * Function responsible for getting password from user till '='
 */
void create_pass			(void);

/*
 * Description :
 * Function responsible for getting password from user till '=' and check it,
 * if it match with the password, will store in EEPROM
 */
uint8 re_enter_pass			(void);

/*
 * Description :
 * Function responsible for storing password in EEPROM
 */
void store_pass				(void);

/*
 * Description :
 * Function responsible for creating password option
 */
void create_pass_option		(void);

/*
 * Description :
 * Function responsible for opening door option
 */
void open_door_option		(void);

/*
 * Description :
 * Function responsible for changing password option
 */
void change_pass_option		(void);

#endif /* CONTROL_ECU_H_ */
