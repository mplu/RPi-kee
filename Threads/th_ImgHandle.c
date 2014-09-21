#include "../includes.h"


void* threadImgHandle (void* arg)
{
    while(1) /* Boucle infinie */
    {
        sem_wait(&sem_Img_available); //waiting for new img to treat
        DEBUG_LOG("Treatment of a new image\n");
    }

    pthread_exit(NULL); /* Fin du thread */
}
