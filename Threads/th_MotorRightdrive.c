#include "../includes.h"



void* threadMotorRightdrive (void* arg)
{
    
	MotorRight.id = 'R';
    MotorRight.Coil_A_1_pin = COIL_A_1_PIN_R ;
    MotorRight.Coil_A_2_pin = COIL_A_2_PIN_R ;
    MotorRight.Coil_B_1_pin = COIL_B_1_PIN_R ;
    MotorRight.Coil_B_2_pin = COIL_B_2_PIN_R ;

   
    while(1) /* Boucle infinie */
    {
        
        if(Params.RightMotorCommand.Steps < 0)
		{
			turnClockwise(MotorRight, Params.RightMotorCommand.Delay, 0-Params.RightMotorCommand.Steps, &sem_RightMotorEmergencyStop);
		}else if (Params.RightMotorCommand.Steps > 0)
		{
			turnCounterClockwise(MotorRight, Params.RightMotorCommand.Delay, Params.RightMotorCommand.Steps, &sem_RightMotorEmergencyStop);
		}else
		{
			turnClockwise(MotorRight, 0, 0, &sem_RightMotorEmergencyStop);
			m_msSleep(100);
		}
    }

    pthread_exit(NULL); /* Fin du thread */
}
