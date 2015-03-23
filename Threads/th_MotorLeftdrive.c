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

    t_DCMotor DCMotorLeft;
    DCMotorLeft.EN1_pin = PIN_M1_EN1;
    DCMotorLeft.EN2_pin = PIN_M1_EN2;
    DCMotorLeft.PWM_pin = PIN_M1_PWM;
    DCMotorGPIOInit(DCMotorLeft);
    while(1) /* Boucle infinie */
    {
		
        if(Params.LeftMotorCommand.Steps > 0)
		{
			//turnClockwise(MotorLeft, Params.LeftMotorCommand.Delay, Params.LeftMotorCommand.Steps, &sem_LeftMotorEmergencyStop);
			DCturnClockwise(DCMotorLeft,70);
			printf("step > 0\n");
		}else if (Params.LeftMotorCommand.Steps < 0)
		{
			//turnCounterClockwise(MotorLeft, Params.LeftMotorCommand.Delay, 0-Params.LeftMotorCommand.Steps, &sem_LeftMotorEmergencyStop);
			DCturnCounterClockwise(DCMotorLeft,70);
			printf("step < 0\n");
		}else
		{
			//turnClockwise(MotorLeft, 0, 0, &sem_LeftMotorEmergencyStop);
			DCturnCounterClockwise(DCMotorLeft,0);
			printf("step = 0\n");
			//m_msSleep(100);
		}
		//DCturnClockwise(DCMotorLeft,20);
		m_msSleep(1000);
    }

    pthread_exit(NULL); /* Fin du thread */
}
