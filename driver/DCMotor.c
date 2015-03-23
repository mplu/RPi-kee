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
// Pins used with WiringPi
    pinMode (M.EN1_pin, OUTPUT) ;
    pinMode (M.EN2_pin, OUTPUT) ;
	digitalWrite (M.EN1_pin, LOW);
	digitalWrite (M.EN2_pin, LOW);

// Pin used with PiGPIO
	gpioPWM(M.PWM_pin, 0);
#endif
}

CPU_VOID DCMotorGPIOStop(t_DCMotor M)
{
#if defined (RPi)
// Pins used with WiringPi
    pinMode (M.EN1_pin, INPUT) ;
    pinMode (M.EN2_pin, INPUT) ;

// Pin used with PiGPIO
    gpioSetMode(M.PWM_pin, PI_INPUT)
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
