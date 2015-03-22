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
	CPU_INT08U MotorPSEnable_1 = 0;
    Params.CommandReg.MoveDirection = 0;
    Params.CommandReg.MoveDuration = 0;
	Params.CommandReg.MotorPSEnable = 0;
	
    while(1) /* Boucle infinie */
    {
        if(Params.CommandReg.MotorPSEnable == 1)
        {
            Params.StatusReg.MotorPSEnable = 1;
            // Enable pin driving 12V
        }else
        {
            Params.StatusReg.MotorPSEnable = 0;
            // Disable pin driving 12V
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
            Params.StatusReg.Auto = 0;
        }else
        {
            Params.StatusReg.Manual = 0;
        }

        if((Params.CommandReg.Auto == 1) && (Params.StatusReg.Manual == 0))
        {
            Params.StatusReg.Auto = 1;
        }else
        {
            Params.StatusReg.Auto = 0;
        }
		
		
		
		if(Params.StatusReg.MotorPSEnable != MotorPSEnable_1)
		{
			if (Params.StatusReg.MotorPSEnable == 1)
			{
				MotorGPIOInit(MotorLeft);
				MotorGPIOInit(MotorRight);
			}else if (Params.StatusReg.MotorPSEnable == 0)
			{
				MotorGPIOStop(MotorLeft);
				MotorGPIOStop(MotorRight);
			}
			
		}
		
		
		
		MotorPSEnable_1 = Params.StatusReg.MotorPSEnable;

        // Manage Manual command case
        if(Params.StatusReg.Manual == 1)
        {
            if(Params.CommandReg.MoveDuration > 0)
            {
                MotorInputCommand(&Params.CommandReg,&Params.LeftMotorCommand,&Params.RightMotorCommand);
                Params.CommandReg.MoveDuration -= 100;
            }else
            {
                MotorFullStop();
            }
        }else if(Params.StatusReg.Auto == 1)
        {
            if(Params.Analog_Values.ImgMoveDirection != 32767)
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
                    MotorFullStop();
                }
            }else
            {
                MotorFullStop();
            }

        }else
        {
            MotorFullStop();
        }

        m_msSleep(100);
    }

    pthread_exit(NULL); /* Fin du thread */
}
