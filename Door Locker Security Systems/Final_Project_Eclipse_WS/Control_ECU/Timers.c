/******************************************************************************
 *
 * Module: Timers
 *
 * Description: Source file for Timers
 *
 *******************************************************************************/

#include "Timers.h"
#include "common_macros.h"
#include <avr/io.h> 		/* To use Timers Registers */
#include <avr/interrupt.h> 	/* For Timers ISR */
#include "std_types.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static void (*g_callBackPtr_Timer0)	(void) 	= NULL_PTR;
static void (*g_callBackPtr_Timer1)	(void) 	= NULL_PTR;
static void (*g_callBackPtr_Timer2)	(void) 	= NULL_PTR;

/* Variable to check delay time finish or not */
volatile uint8 timer_finish = 0;

/*******************************************************************************
 *                           Static Variables                                  *
 *******************************************************************************/

/* Timers Over_Flow Counters & flags */
static volatile uint16 T_ovf_counter;
static volatile uint16 T_ovf_flag;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr_Timer0 != NULL_PTR)
	{
		if(T_ovf_flag == T_ovf_counter)
		{
			/* Call the Call Back function in the application after Timer Over Flow */
			(*g_callBackPtr_Timer0)();
		}
		else
		{
			T_ovf_flag++;
		}
	}
}

ISR(TIMER1_OVF_vect)
{
	if(T_ovf_flag == T_ovf_counter)
	{
		if(g_callBackPtr_Timer1 != NULL_PTR)
		{
			/* Call the Call Back function in the application after Timer Over Flow */
			(*g_callBackPtr_Timer1)();
		}
	}
	else
	{
		T_ovf_flag++;
	}

}

ISR(TIMER2_OVF_vect)
{
	if(T_ovf_flag == T_ovf_counter)
	{
		if(g_callBackPtr_Timer2 != NULL_PTR)
		{
			/* Call the Call Back function in the application after Timer Over Flow */
			(*g_callBackPtr_Timer2)();
		}
	}
	else
	{
		T_ovf_flag++;
	}

}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr_Timer0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after Timer reach to Compare value */
		(*g_callBackPtr_Timer0)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr_Timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after Timer reach to Compare value */
		(*g_callBackPtr_Timer1)();
	}
}

ISR(TIMER1_COMPB_vect)
{
	if(g_callBackPtr_Timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after Timer reach to Compare value */
		(*g_callBackPtr_Timer1)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr_Timer2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after Timer reach to Compare value */
		(*g_callBackPtr_Timer2)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initiate timer with configuration from structure & Enable it
 */
void Timer_init(const Timer_ConfigType * Timer_Config_Ptr)
{
	if(Timer_Config_Ptr->T_Select == Timer0)
	{
		if(Timer_Config_Ptr->T_Mode == T0_Ovf_Mode)
		{
			T_ovf_flag = 0;												/* set over flow flag to zero */
			T_ovf_counter = Timer_Config_Ptr->T_ovf_counter;			/* set number of over flow */
			TCNT0 = Timer_Config_Ptr->T0_T2_Initial_Value; 				/* Set Timer0 initial value */
			SET_BIT(TIMSK, TOIE0);										/* Enable Timer0 Overflow Interrupt */
			TCCR0 = (1<<FOC0);											/* Non PWM mode */
			TCCR0 = (TCCR0 & 0XF8) | (Timer_Config_Ptr->T_Prescaler);	/* Configure Timer0 Pre-scaler */

		}
		else if(Timer_Config_Ptr->T_Mode == T0_Compare_Mode)
		{
			TCNT0 = Timer_Config_Ptr->T0_T2_Initial_Value;				/* Set Timer0 initial value */
			OCR0 = Timer_Config_Ptr->T0_T2_Comp_Value;					/* Set Compare Value */
			SET_BIT(TIMSK, OCIE0);										/* Enable Timer0 Compare Interrupt */
			TCCR0 = (1<<FOC0) | (1<<WGM01);								/* Non PWM mode and enable CTC Mode*/
			TCCR0 = (TCCR0 & 0XF8) | (Timer_Config_Ptr->T_Prescaler);	/* Configure Timer0 Pre-scaler */
		}
	}

	else if(Timer_Config_Ptr->T_Select == Timer1)
	{
		if(Timer_Config_Ptr->T_Mode == T1_Ovf_Mode)
		{
			T_ovf_flag = 0;												/* set over flow flag to zero */
			T_ovf_counter = Timer_Config_Ptr->T_ovf_counter;			/* set number of over flow */
			TCNT1 = Timer_Config_Ptr->T1_Initial_Value;					/* Set Timer1 initial value */
			SET_BIT(TIMSK, TOIE1);										/* Enable Timer1 Overflow Interrupt */
			TCCR1A = (1<<FOC1A) | (1<<FOC1B);							/* Non PWM mode */
			TCCR1B = (TCCR1B & 0XF8) | (Timer_Config_Ptr->T_Prescaler);	/* Configure Timer1 Pre-scaler */
		}
		else if(Timer_Config_Ptr->T_Mode == T1_CompareA_Mode)
		{
			TCNT1 = Timer_Config_Ptr->T1_Initial_Value;					/* Set Timer1 initial value */
			OCR1A = Timer_Config_Ptr->T1_Comp_Value;					/* Set Compare Value */
			SET_BIT(TIMSK, OCIE1A);										/* Enable Timer1 CompareA Interrupt */
			TCCR1A = (1<<FOC1A) | (1<<FOC1B);							/* Non PWM mode */
			TCCR1B = (1<<WGM12);										/* Enable CTC Mode */
			TCCR1B = (TCCR1B & 0XF8) | (Timer_Config_Ptr->T_Prescaler);	/* Configure Timer1 Pre-scaler */

		}
		else if(Timer_Config_Ptr->T_Mode == T1_CompareB_Mode)
		{
			TCNT1 = Timer_Config_Ptr->T1_Initial_Value;					/* Set Timer1 initial value */
			OCR1B = Timer_Config_Ptr->T1_Comp_Value;					/* Set Compare Value */
			SET_BIT(TIMSK, OCIE1B);										/* Enable Timer1 CompareB Interrupt */
			TCCR1B = (1<<WGM12);										/* Enable CTC Mode */
			TCCR1A = (1<<FOC1A) | (1<<FOC1B);							/* Non PWM mode */
			TCCR1B = (TCCR1B & 0XF8) | (Timer_Config_Ptr->T_Prescaler);	/* Configure Timer1 Pre-scaler */
		}
	}

	else if(Timer_Config_Ptr->T_Select == Timer2)
	{
		if(Timer_Config_Ptr->T_Mode == T2_Ovf_Mode)
		{
			T_ovf_flag = 0;													/* set over flow flag to zero */
			T_ovf_counter = Timer_Config_Ptr->T_ovf_counter;				/* set number of over flow */
			TCNT2 = Timer_Config_Ptr->T0_T2_Initial_Value;					/* Set Timer2 initial value */
			SET_BIT(TIMSK, TOIE2);											/* Enable Timer2 Overflow Interrupt */
			TCCR2 = (1<<FOC2);												/* Non PWM mode */
			TCCR2 = (TCCR1B & 0XF8) | (Timer_Config_Ptr->T_Prescaler);		/* Configure Timer2 Pre-scaler */
		}
		else if(Timer_Config_Ptr->T_Mode == T2_Compare_Mode)
		{
			TCNT2 = Timer_Config_Ptr->T0_T2_Initial_Value;					/* Set Timer2 initial value */
			OCR2 = Timer_Config_Ptr->T0_T2_Comp_Value;						/* Set Compare Value */
			SET_BIT(TIMSK, OCIE2);											/* Enable Timer2 Compare Interrupt */
			TCCR2 = (1<<FOC2) | (1<<WGM21);									/* Non PWM mode and enable CTC Mode */
			TCCR2 = (TCCR1B & 0XF8) | (Timer_Config_Ptr->T_Prescaler);		/* Configure Timer2 Pre-scaler */
		}
	}
}

/************************************************************************/

/*
 * Description :
 * Functions to Disable Timers
 */
void Timer0_DeInit(void)
{
	CLEAR_BIT(TIMSK, TOIE0);									/* Disable Timer0 Overflow Interrupt */
	CLEAR_BIT(TIMSK, OCIE0);									/* Disable Timer0 Compare Interrupt */
	timer_finish++;
}

void Timer1_DeInit(void)
{
	CLEAR_BIT(TIMSK, TOIE1);									/* Disable Timer1 Overflow Interrupt */
	CLEAR_BIT(TIMSK, OCIE1A);									/* Disable Timer1 CompareA Interrupt */
	CLEAR_BIT(TIMSK, OCIE1B);									/* Disable Timer1 CompareB Interrupt */
	timer_finish++;
}

void Timer2_DeInit(void)
{
	CLEAR_BIT(TIMSK, TOIE2);									/* Disable Timer2 Overflow Interrupt */
	CLEAR_BIT(TIMSK, OCIE2);									/* Disable Timer2 CompareA Interrupt */
	timer_finish++;
}

/************************************************************************/

/************************************************************************/

/*
 * Description :
 * Functions to set the Call Back function address for each timer
 */

void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr_Timer0 = a_ptr;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr_Timer1 = a_ptr;
}

void Timer2_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr_Timer2 = a_ptr;
}

/************************************************************************/
