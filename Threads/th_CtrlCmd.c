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
        m_msSleep(100);
        //TODO : Send command to both motors by setting value in Params.*MotorCommand.Delay / Params.*MotorCommand.Steps
        if(Params.CommandReg.MoveDuration > 0)
        {
            MotorInputCommand(&Params.CommandReg,&Params.LeftMotorCommand,&Params.RightMotorCommand);
            Params.CommandReg.MoveDuration -= 100;
        }else
        {
            MotorFullStop();
        }
    }

    pthread_exit(NULL); /* Fin du thread */
}
