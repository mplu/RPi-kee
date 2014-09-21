#include "../includes.h"


void* threadProtections (void* arg)
{
    while(1) /* Boucle infinie */
    {


        pthread_mutex_lock(&mutex); /* On verrouille le mutex */
        pthread_cond_wait (&condition, &mutex); /* On attend que la condition soit remplie */
        DEBUG_LOG("\nLe compteur a depasse 20.");
        pthread_mutex_unlock(&mutex); /* On déverrouille le mutex */

    }

    pthread_exit(NULL); /* Fin du thread */
}
