/******************************************************************************
 *
 * Module: Timers
 *
 * Description: Header file for Timers
 *
 *******************************************************************************/

#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Timers Types definitions */
#define Timer0				0
#define Timer1				1
#define Timer2				2

/* Timers modes definitions */
#define T0_Ovf_Mode			0
#define T0_Compare_Mode		1
#define T1_Ovf_Mode			2
#define T1_CompareA_Mode	3
#define T1_CompareB_Mode	4
#define T2_Ovf_Mode			5
#define T2_Compare_Mode		6

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * enum to select the timer
 */
typedef enum
{
	Timer_0, Timer_1, Timer_2
}TIMER_Select;

/*
 * enum to define the Pre-scaler for Timer
 */
typedef enum
{
	Timer_Prescaler_0 = 1, Timer_Prescaler_8, Timer_Prescaler_64, Timer_Prescaler_256, Timer_Prescaler_1024
}Timer_Prescaler;

/*
 * enum to define for Timer Mode
 */
typedef enum
{
	Timer0_Ovf_Mode, Timer0_Compare_Mode, Timer1_Ovf_Mode, Timer1_CompareA_Mode, Timer1_CompareB_Mode, Timer2_Ovf_Mode, Timer2_Compare_Mode
}Timer_Mode;

/*
 * Timer Config. Parameters Structure:
 * - Timer(0, 1, 2) Select
 * - Timer Pre-scaler (0, 8, 64, 256, 1024)
 * - Timer Mode (Over-Flow mode, Compare mode)
 * - Set Timers Initial value
 * - Set Number of Over-Flow in case Over-Flow mode
 * - Set compare value in Compare mode
 */
typedef struct{
	TIMER_Select 		T_Select;
	Timer_Prescaler 	T_Prescaler;
	Timer_Mode 			T_Mode;
	uint8 				T0_T2_Initial_Value;
	uint16 				T1_Initial_Value;
	uint16				T_ovf_counter;
	uint8 				T0_T2_Comp_Value;
	uint16 				T1_Comp_Value;
}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initiate timer with configuration from structure & Enable it
 */
void Timer_init(const Timer_ConfigType * Timer_Config_Ptr);



/************************************************************************/
/*
 * Description :
 * Functions to disable Timers
 */
void Timer0_DeInit(void);
void Timer1_DeInit(void);
void Timer2_DeInit(void);
/************************************************************************/



/************************************************************************/
/*
 * Description :
 * Functions to set the Call Back function address for each timer
 */
void Timer0_setCallBack(void(*a_ptr)(void));
void Timer1_setCallBack(void(*a_ptr)(void));
void Timer2_setCallBack(void(*a_ptr)(void));
/************************************************************************/

#endif /* TIMERS_H_ */
