/****************************************************************/
/* Stepper Motor driver                                         */
/* File : StepperMotor.h                                        */
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

#define COIL_A_1_PIN_LR 1
#define COIL_A_2_PIN_LR 26
#define COIL_B_1_PIN_LR 27
#define COIL_B_2_PIN_LR 25

#define COIL_A_1_PIN_UD 23
#define COIL_A_2_PIN_UD 22
#define COIL_B_1_PIN_UD 21
#define COIL_B_2_PIN_UD 2

typedef struct
{
	CPU_CHAR id;
	CPU_INT08U Coil_A_1_pin;
	CPU_INT08U Coil_A_2_pin;
	CPU_INT08U Coil_B_1_pin;
	CPU_INT08U Coil_B_2_pin;
}t_StepperMotor;

CPU_VOID StepperMotorGPIOInit(t_StepperMotor M);
CPU_VOID StepperMotorGPIOStop(t_StepperMotor M);
CPU_VOID setStep(t_StepperMotor M,CPU_INT08U w1, CPU_INT08U w2, CPU_INT08U w3, CPU_INT08U w4);
CPU_VOID StepperTurnClockwise(t_StepperMotor M,CPU_INT16U delay, CPU_INT16U steps, sem_t * sem_Abort);
CPU_VOID StepperTurnCounterClockwise(t_StepperMotor M,CPU_INT16U delay, CPU_INT16U steps, sem_t * sem_Abort);


#endif


