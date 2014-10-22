#include "../includes.h"



void* threadMotorLeftdrive (void* arg)
{
    t_Motor MotorLeft;
	MotorLeft.id = 'L';
    MotorLeft.Coil_A_1_pin = COIL_A_1_PIN_L ;
    MotorLeft.Coil_A_2_pin = COIL_A_2_PIN_L ;
    MotorLeft.Coil_B_1_pin = COIL_B_1_PIN_L ;
    MotorLeft.Coil_B_2_pin = COIL_B_2_PIN_L ;

    MotorGPIOInit(MotorLeft);
    while(1) /* Boucle infinie */
    {
    	m_msSleep(100);
        if(Params.LeftMotorCommand.Steps > 0)
		{
			turnClockwise(MotorLeft, Params.LeftMotorCommand.Delay, Params.LeftMotorCommand.Steps, &sem_LeftMotorEmergencyStop);
		}else if (Params.LeftMotorCommand.Steps < 0)
		{
			turnCounterClockwise(MotorLeft, Params.LeftMotorCommand.Delay, 0-Params.LeftMotorCommand.Steps, &sem_LeftMotorEmergencyStop);
		}else
		{
			turnClockwise(MotorLeft, 0, 0, &sem_LeftMotorEmergencyStop);
		}
    }

    pthread_exit(NULL); /* Fin du thread */
}
