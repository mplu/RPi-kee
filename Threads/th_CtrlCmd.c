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
    Params.CommandReg.MoveDirection = 0;
    Params.CommandReg.MoveDuration = 0;

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
            Params.CommandReg.MoveDirection = Params.Analog_Values.ImgMoveDirection;
            if(Params.Analog_Values.ShortIRDistance > 20)
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

        m_msSleep(100);
    }

    pthread_exit(NULL); /* Fin du thread */
}
