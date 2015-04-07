#include "../includes.h"



void* threadMotorRightdrive (void* arg)
{
	DCMotorRight.EN1_pin = PIN_M2_EN1;
    DCMotorRight.EN2_pin = PIN_M2_EN2;
    DCMotorRight.PWM_pin = PIN_M2_PWM;
    DCMotorGPIOInit(DCMotorRight);
    DCMotorGPIOStop(DCMotorRight);

    while(1) /* Boucle infinie */
    {

        if(Params.RightMotorCommand.Speed > 0)
		{
			DCturnClockwise(DCMotorRight,Params.RightMotorCommand.Speed);
		}else if (Params.RightMotorCommand.Speed < 0)
		{
			DCturnCounterClockwise(DCMotorRight,0 - Params.RightMotorCommand.Speed);
		}else
		{
			DCturnCounterClockwise(DCMotorRight,0);
		}
		m_msSleep(500);
    }

    pthread_exit(NULL); /* Fin du thread */
}
