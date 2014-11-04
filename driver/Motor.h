/****************************************************************/
/* Stepper Motor driver                                         */
/* File : Motor.h                                               */
/* Description :                                                */
/*   Stepper Motor function                                     */
/*      Inspired by http://learn.adafruit.com/adafruits-raspberry-pi-lesson-10-stepper-motors?view=all */
/*      Modified to use wiringpi http://wiringpi.com/reference  */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#ifndef __MOTOR_H
#define __MOTOR_H

/* *** Motor GPIO Coil definition *** */

#define COIL_A_1_PIN_L 1
#define COIL_A_2_PIN_L 26
#define COIL_B_1_PIN_L 27
#define COIL_B_2_PIN_L 25

#define COIL_A_1_PIN_R 23
#define COIL_A_2_PIN_R 22
#define COIL_B_1_PIN_R 21
#define COIL_B_2_PIN_R 2

typedef struct
{
	CPU_CHAR id;
	CPU_INT08U Coil_A_1_pin;
	CPU_INT08U Coil_A_2_pin;
	CPU_INT08U Coil_B_1_pin;
	CPU_INT08U Coil_B_2_pin;
}t_Motor;

CPU_VOID MotorGPIOInit(t_Motor M);
CPU_VOID MotorGPIOStop(t_Motor M);
CPU_VOID setStep(t_Motor M,CPU_INT08U w1, CPU_INT08U w2, CPU_INT08U w3, CPU_INT08U w4);
CPU_VOID turnClockwise(t_Motor M,CPU_INT16U delay, CPU_INT16U steps, sem_t * sem_Abort);
CPU_VOID turnCounterClockwise(t_Motor M,CPU_INT16U delay, CPU_INT16U steps, sem_t * sem_Abort);


#endif


