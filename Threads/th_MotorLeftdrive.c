#include "../includes.h"



void* threadMotorLeftdrive (void* arg)
{
    /*
	t_StepperMotor MotorLeft;
	MotorLeft.id = 'L';
    MotorLeft.Coil_A_1_pin = COIL_A_1_PIN_L ;
    MotorLeft.Coil_A_2_pin = COIL_A_2_PIN_L ;
    MotorLeft.Coil_B_1_pin = COIL_B_1_PIN_L ;
    MotorLeft.Coil_B_2_pin = COIL_B_2_PIN_L ;
    */

    DCMotorLeft.EN1_pin = PIN_M1_EN1;
    DCMotorLeft.EN2_pin = PIN_M1_EN2;
    DCMotorLeft.PWM_pin = PIN_M1_PWM;
    DCMotorGPIOInit(DCMotorLeft);

    while(1) /* Boucle infinie */
    {

        if(Params.LeftMotorCommand.Speed > 0)
		{
			DCturnClockwise(DCMotorLeft,Params.LeftMotorCommand.Speed);
		}else if (Params.LeftMotorCommand.Speed < 0)
		{
			DCturnCounterClockwise(DCMotorLeft,0 - Params.LeftMotorCommand.Speed);
		}else
		{
			DCturnCounterClockwise(DCMotorLeft,0);
		}
		m_msSleep(500);
    }

    pthread_exit(NULL); /* Fin du thread */
}
