#include "../includes.h"



void* threadMotorRightdrive (void* arg)
{
	/*
    t_StepperMotor MotorRight;
	MotorRight.id = 'R';
	MotorRight.Coil_A_1_pin = COIL_A_1_PIN_R ;
    MotorRight.Coil_A_2_pin = COIL_A_2_PIN_R ;
    MotorRight.Coil_B_1_pin = COIL_B_1_PIN_R ;
    MotorRight.Coil_B_2_pin = COIL_B_2_PIN_R ;
    */


    DCMotorRight.EN1_pin = PIN_M2_EN1;
    DCMotorRight.EN2_pin = PIN_M2_EN2;
    DCMotorRight.PWM_pin = PIN_M2_PWM;
    DCMotorGPIOInit(DCMotorRight);

    while(1) /* Boucle infinie */
    {

        if(Params.RightMotorCommand.Steps < 0)
		{
			DCturnClockwise(DCMotorRight,70);
		}else if (Params.RightMotorCommand.Steps > 0)
		{
			DCturnCounterClockwise(DCMotorRight,70);
		}else
		{
			DCturnCounterClockwise(DCMotorRight,0);
		}
		m_msSleep(500);
    }

    pthread_exit(NULL); /* Fin du thread */
}
