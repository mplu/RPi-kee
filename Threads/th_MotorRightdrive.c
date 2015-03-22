#include "../includes.h"



void* threadMotorRightdrive (void* arg)
{
	/*
    t_StepperMotor MotorRight;
	MotorRight.id = 'R';    MotorRight.Coil_A_1_pin = COIL_A_1_PIN_R ;
    MotorRight.Coil_A_2_pin = COIL_A_2_PIN_R ;
    MotorRight.Coil_B_1_pin = COIL_B_1_PIN_R ;
    MotorRight.Coil_B_2_pin = COIL_B_2_PIN_R ;


    */
    t_DCMotor DCMotorRight;
    DCMotorRight.EN1_pin = PIN_M2_EN1;
    DCMotorRight.EN2_pin = PIN_M2_EN2;
    DCMotorRight.PWM_pin = PIN_M2_PWM;
    DCMotorGPIOInit(DCMotorRight);
    while(1) /* Boucle infinie */
    {

        if(Params.RightMotorCommand.Steps < 0)
		{
			//turnClockwise(MotorRight, Params.RightMotorCommand.Delay, Params.RightMotorCommand.Steps, &sem_RightMotorEmergencyStop);
			DCturnClockwise(DCMotorRight,10);
		}else if (Params.RightMotorCommand.Steps > 0)
		{
			//turnCounterClockwise(MotorRight, Params.RightMotorCommand.Delay, 0-Params.RightMotorCommand.Steps, &sem_RightMotorEmergencyStop);
			DCturnCounterClockwise(DCMotorRight,10);
		}else
		{
			//turnClockwise(MotorRight, 0, 0, &sem_RightMotorEmergencyStop);
			DCturnCounterClockwise(DCMotorRight,0);
			m_msSleep(100);
		}
    }

    pthread_exit(NULL); /* Fin du thread */
}
