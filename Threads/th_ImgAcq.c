#include "..\includes.h"


void* threadImgAcq (void* arg)
{
    while(1) /* Boucle infinie */
    {
        psleep(5);
    }

    pthread_exit(NULL); /* Fin du thread */
}