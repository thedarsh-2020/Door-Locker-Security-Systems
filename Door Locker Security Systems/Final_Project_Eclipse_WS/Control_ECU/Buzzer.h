/******************************************************************************
 *
 * Module: Buzzer
 *
 * Description: Header file for Buzzer
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initiate buzzer pin direction and its initial state
 */
void buzzer_init(void);

/*
 * Description :
 * Function responsible for turn on buzzer
 */
void buzzer_on(void);

/*
 * Description :
 * Function responsible for turn off buzzer
 */
void buzzer_off(void);

#endif /* BUZZER_H_ */
