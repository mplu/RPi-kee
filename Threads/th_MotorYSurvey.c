#include "../includes.h"



void* threadMotorYSurvey (void* arg)
{

	MotorY_UD.id = 'Y';
    MotorY_UD.Coil_A_1_pin = COIL_A_1_PIN_UD ;
    MotorY_UD.Coil_A_2_pin = COIL_A_2_PIN_UD ;
    MotorY_UD.Coil_B_1_pin = COIL_B_1_PIN_UD ;
    MotorY_UD.Coil_B_2_pin = COIL_B_2_PIN_UD ;
    StepperMotorGPIOInit(MotorX_LR);
    StepperMotorGPIOStop(MotorX_LR);

    while(1) /* Boucle infinie */
    {

        if(Params.RightMotorCommand.Unused < 0)
		{
			StepperTurnCounterClockwise(MotorY_UD, Params.RightMotorCommand.Speed, 0-Params.RightMotorCommand.Unused, &sem_YMotorEmergencyStop);
		}else if (Params.RightMotorCommand.Unused > 0)
		{
			StepperTurnClockwise(MotorY_UD, Params.RightMotorCommand.Speed, Params.RightMotorCommand.Unused, &sem_YMotorEmergencyStop);
		}else
		{
			StepperTurnClockwise(MotorY_UD, 0, 0, &sem_YMotorEmergencyStop);
			m_msSleep(100);
		}
    }

    pthread_exit(NULL); /* Fin du thread */
}
