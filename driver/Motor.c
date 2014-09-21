/****************************************************************/
/* Stepper Motor driver                                         */
/* File : Motor.c                                               */
/* Description :                                                */
/*   Variables shared between processes                         */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "../includes.h"

CPU_VOID MotorGPIOInit(t_Motor M)
{
#if defined (RPi)
    pinMode (M.Coil_A_1_pin, OUTPUT) ;
    pinMode (M.Coil_A_2_pin, OUTPUT) ;
    pinMode (M.Coil_B_1_pin, OUTPUT) ;
    pinMode (M.Coil_B_2_pin, OUTPUT) ;
#endif
}

CPU_VOID setStep(t_Motor M,CPU_INT08U w1, CPU_INT08U w2, CPU_INT08U w3, CPU_INT08U w4)
{
#if defined (RPi)
        digitalWrite (M.Coil_A_1_pin, w1) ;
        digitalWrite (M.Coil_A_2_pin, w2) ;
        digitalWrite (M.Coil_B_1_pin, w3) ;
        digitalWrite (M.Coil_B_2_pin, w4) ;
#endif
}

CPU_VOID turnClockwise(t_Motor M,CPU_INT16U delay, CPU_INT16U steps, sem_t * sem_Abort)
{
        CPU_INT16U i;
        for (i = 0 ; i < steps; i++)
        {
                setStep(M,HIGH, LOW, HIGH, LOW);
				m_msSleep(delay); // msec
                setStep(M,LOW, HIGH, HIGH, LOW);
				m_msSleep(delay); // msec
                setStep(M,LOW, HIGH, LOW, HIGH);
				m_msSleep(delay); // msec
                setStep(M,HIGH, LOW, LOW, HIGH);
				m_msSleep(delay); // msec
				if(sem_trywait(sem_Abort)!=SEM_EMPTY)
				{
					i = steps; // Immedialty exit the for loop
				}
        }
}

CPU_VOID turnCounterClockwise(t_Motor M,CPU_INT16U delay, CPU_INT16U steps, sem_t * sem_Abort)
{
        CPU_INT16U i;
        for (i = 0 ; i < steps; i++)
        {
                setStep(M,HIGH, LOW, LOW, HIGH);
				m_msSleep(delay); // msec
                setStep(M,LOW, HIGH, LOW, HIGH);
				m_msSleep(delay); // msec
                setStep(M,LOW, HIGH, HIGH, LOW);
				m_msSleep(delay); // msec
                setStep(M,HIGH, LOW, HIGH, LOW);
				m_msSleep(delay); // msec
				if(sem_trywait(sem_Abort)!=SEM_EMPTY)
				{
					i = steps; // Immedialty exit the for loop
				}
        }
}
