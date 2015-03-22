/****************************************************************/
/* DC Motor driver                                         		*/
/* File : DCMotor.c                                             */
/* Description :                                                */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "../includes.h"

CPU_VOID DCMotorGPIOInit(t_DCMotor M)
{
#if defined (RPi)
    pinMode (M.EN1_pin, OUTPUT) ;
    pinMode (M.EN2_pin, OUTPUT) ;
	digitalWrite (M.EN1_pin, LOW);
	digitalWrite (M.EN2_pin, LOW);
	gpioPWM(M.PWM_pin, 0);
#endif
}

CPU_VOID DCturnClockwise(t_DCMotor M,CPU_INT16U speed)
{
#if defined (RPi)
	digitalWrite (M.EN1_pin, HIGH);
	digitalWrite (M.EN2_pin, LOW);
	gpioPWM(M.PWM_pin, speed);
#endif
}

CPU_VOID DCturnCounterClockwise(t_DCMotor M,CPU_INT16U speed)
{
#if defined (RPi)
	digitalWrite (M.EN1_pin, LOW);
	digitalWrite (M.EN2_pin, HIGH);
	gpioPWM(M.PWM_pin, speed);
#endif
}
