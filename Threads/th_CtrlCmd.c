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
    while(1) /* Boucle infinie */
    {
        m_sSleep(5);
        //TODO : Send command to both motors by setting value in Params.*MotorCommand.Delay / Params.*MotorCommand.Steps
    Params.CommandReg.MoveDirection = 0;
    Params.CommandReg.MoveDuration = 0;
    }

    pthread_exit(NULL); /* Fin du thread */
}
