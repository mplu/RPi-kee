#include "../includes.h"


void* threadImgAcq (void* arg)
{
    while(1) /* Boucle infinie */
    {
        m_sSleep(5);
        sem_post(&sem_Img_available);
    }

    pthread_exit(NULL); /* Fin du thread */
}
