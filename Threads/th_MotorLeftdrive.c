#include "../includes.h"



void* threadMotorLeftdrive (void* arg)
{
    while(1) /* Boucle infinie */
    {
        m_sSleep(5);
    }

    pthread_exit(NULL); /* Fin du thread */
}
