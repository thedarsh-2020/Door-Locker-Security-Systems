/**************************************************************************************************
 *
 * Author      : Mustafa Muhammad
 *
 * Description : Header file for Door Locker Security Systems (HMI ECU)
 *
 **************************************************************************************************/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

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

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for take a password from user
 * then send it byte by byte to Control_ECU by UART and display '*' on LCD
 */
void take_pass				(void);

/*
 * Description :
 * Function responsible for take selected option from user
 */
void home_screen			(void);

#endif /* HMI_ECU_H_ */
