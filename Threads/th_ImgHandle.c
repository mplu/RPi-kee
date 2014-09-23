#include "../includes.h"


void* threadImgHandle (void* arg)
{
    while(1) /* Boucle infinie */
    {
        sem_wait(&sem_Img_available); //waiting for new img to treat
    }

    pthread_exit(NULL); /* Fin du thread */
}
