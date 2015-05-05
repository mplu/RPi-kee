#include "../includes.h"



void* threadDebug (void* arg)
{



    while(1) /* Boucle infinie */
    {
        m_sSleep (2); /* On laisse 1 seconde de repos */
        //pthread_mutex_lock(&mtx_LockCamera);
        //m_sSleep (5); /* On laisse 5 seconde de repos */
        //pthread_mutex_unlock(&mtx_LockCamera);

    }

    pthread_exit(NULL); /* Fin du thread */
}
