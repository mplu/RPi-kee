#include "../includes.h"

/********************************************//**
 * \brief Control Command thread
 *
 * \param arg : potential argument, not used
 *
 * \return none
 *
 * One thread to rule them all
 ***********************************************/

void* threadCtrlCmd (void* arg)
{
	CPU_INT08U MovementMotorEnable_1 = 0;
	CPU_INT08U TurretMotorEnable_1 = 0;
    Params.CommandReg.MoveDirection = 0;
    Params.CommandReg.MoveDuration = 0;
	Params.CommandReg.MovementMotorEnable = 0;
	Params.CommandReg.TurretMotorEnable = 0;
	Params.CommandReg.Survey = 1;


    while(1) /* Boucle infinie */
    {
        if(Params.CommandReg.MovementMotorEnable == 1)
        {
            Params.StatusReg.MovementMotorEnable = 1;
        }else
        {
            Params.StatusReg.MovementMotorEnable = 0;
        }

        if(Params.CommandReg.TurretMotorEnable == 1)
        {
            Params.StatusReg.TurretMotorEnable = 1;
        }else
        {
            Params.StatusReg.TurretMotorEnable = 0;
        }

        if(Params.CommandReg.UDPLiveFeed != 0)
        {
            Params.StatusReg.UDPLiveFeed = 1;
        }else
        {
            Params.StatusReg.UDPLiveFeed = 0;
        }

        if(Params.CommandReg.Manual == 1)
        {
            Params.StatusReg.Manual = 1;
            Params.StatusReg.LineFollow = 0;
        }else
        {
            Params.StatusReg.Manual = 0;
        }

        if(Params.CommandReg.Survey != 0)
        {
            Params.StatusReg.Survey = 1;
            Params.StatusReg.LineFollow = 0;
        }else
        {
            Params.StatusReg.Survey = 0;
        }

        if((Params.CommandReg.LineFollow == 1) && (Params.StatusReg.Manual == 0)&& (Params.StatusReg.Survey == 0))
        {
            Params.StatusReg.LineFollow = 1;
        }else
        {
            Params.StatusReg.LineFollow = 0;
        }




        // Manage On / Off for DC Motor
		if(Params.StatusReg.MovementMotorEnable != MovementMotorEnable_1)
		{
			if (Params.StatusReg.MovementMotorEnable == 1)
			{
				DCMotorGPIOInit(DCMotorLeft);
				DCMotorGPIOInit(DCMotorRight);
			}else if (Params.StatusReg.MovementMotorEnable == 0)
			{
				DCMotorGPIOStop(DCMotorLeft);
				DCMotorGPIOStop(DCMotorRight);
			}
		}
		MovementMotorEnable_1 = Params.StatusReg.MovementMotorEnable;

        // Manage On / Off for Stepper Motor
        if(Params.StatusReg.TurretMotorEnable != TurretMotorEnable_1)
		{
			if (Params.StatusReg.TurretMotorEnable == 1)
			{
				StepperMotorGPIOInit(MotorY_UD);
				StepperMotorGPIOInit(MotorX_LR);
			}else if (Params.StatusReg.TurretMotorEnable == 0)
			{
				StepperMotorGPIOStop(MotorY_UD);
				StepperMotorGPIOStop(MotorX_LR);
			}
		}
		TurretMotorEnable_1 = Params.StatusReg.TurretMotorEnable;

        // Manage Manual command case
        if(Params.StatusReg.Manual == 1)
        {
            // Process Input Data to DCMotorCommand
            if(Params.CommandReg.MoveDuration > 0)
            {
                MotorInputCommand(&Params.CommandReg,&Params.LeftMotorCommand,&Params.RightMotorCommand);
                Params.CommandReg.MoveDuration -= 100;
            }else
            {
                DCMotorFullStop();
            }

            // Send Processed Command to motor
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






        }else if(Params.StatusReg.LineFollow == 1)
        {
            /*if(Params.Analog_Values.ImgMoveDirection != 32767)
            {
                Params.CommandReg.MoveDirection = Params.Analog_Values.ImgMoveDirection;
                //if(Params.FailureReg.global_1.bit.IRDistance == TRUE)
                {
                    Params.CommandReg.MoveDuration = 500;
                }
                if(Params.CommandReg.MoveDuration > 0)
                {
                    MotorInputCommand(&Params.CommandReg,&Params.LeftMotorCommand,&Params.RightMotorCommand);
                    Params.CommandReg.MoveDuration -= 100;
                }else
                {
                    DCMotorFullStop();
                }
            }else
            {
                DCMotorFullStop();
            }
            */

        }else
        {
            DCMotorFullStop();
        }

        m_msSleep(100);
    }

    pthread_exit(NULL); /* Fin du thread */
}
