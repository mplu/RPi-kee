/****************************************************************/
/* DC Motor driver                                         		*/
/* File : DCMotor.h                                             */
/* Description :                                                */
/*   DC Motor function                                     		*/
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#ifndef __DCMOTOR_H
#define __DCMOTOR_H

/* *** Motor GPIO Coil definition *** */

#define PIN_M1_EN1	24// 19 use wiringpi name
#define PIN_M1_EN2	28// 20 use wiringpi name
#define PIN_M1_PWM	21

#define PIN_M2_EN1	3// 22 use wiringpi name
#define PIN_M2_EN2	5// 24 use wiringpi name
#define PIN_M2_PWM	25

typedef struct
{
	CPU_INT08U EN1_pin;
	CPU_INT08U EN2_pin;
	CPU_INT08U PWM_pin;
}t_DCMotor;

CPU_VOID DCMotorGPIOInit(t_DCMotor M);
CPU_VOID DCturnClockwise(t_DCMotor M,CPU_INT16U speed);
CPU_VOID DCturnCounterClockwise(t_DCMotor M,CPU_INT16U speed);


#endif


