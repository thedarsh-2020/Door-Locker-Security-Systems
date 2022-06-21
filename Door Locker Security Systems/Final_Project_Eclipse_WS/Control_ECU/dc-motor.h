/******************************************************************************
 *
 * Module: DC Motor
 *
 * Description: Header file for Door DC-Motor
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * enum to define DC-Motor state
 */
typedef enum
{
	STOP, CW, A_CW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for DC-Motor Init-ialization
 */
void DcMotor_Init(void);

/*
 * Description :
 * Function responsible for DC-Motor state
 */
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
