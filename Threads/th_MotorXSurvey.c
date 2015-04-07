#include "../includes.h"



void* threadMotorXSurvey (void* arg)
{

	MotorX_LR.id = 'X';
    MotorX_LR.Coil_A_1_pin = COIL_A_1_PIN_LR ;
    MotorX_LR.Coil_A_2_pin = COIL_A_2_PIN_LR ;
    MotorX_LR.Coil_B_1_pin = COIL_B_1_PIN_LR ;
    MotorX_LR.Coil_B_2_pin = COIL_B_2_PIN_LR ;


    while(1) /* Boucle infinie */
    {

        if(Params.XMotorCommand.Unused > 0)
		{
			StepperTurnCounterClockwise(MotorX_LR, Params.XMotorCommand.Speed, Params.XMotorCommand.Unused, &sem_XMotorEmergencyStop);
		}else if (Params.XMotorCommand.Unused < 0)
		{
			StepperTurnClockwise(MotorX_LR, Params.XMotorCommand.Speed, 0-Params.XMotorCommand.Unused, &sem_XMotorEmergencyStop);
		}else
		{
			StepperTurnClockwise(MotorX_LR, 0, 0, &sem_XMotorEmergencyStop);
			m_msSleep(100);
		}
    }

    pthread_exit(NULL); /* Fin du thread */
}
