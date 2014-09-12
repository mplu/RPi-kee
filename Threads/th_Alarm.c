#include "../includes.h"


void* threadAlarme (void* arg)
{
    while(1) /* Boucle infinie */
    {

        printf("\nThAlr : avant lock");
        pthread_mutex_lock(&mutex); /* On verrouille le mutex */
        printf("\nThAlr : apres lock");
        printf("\nThAlr : avant cond");
        pthread_cond_wait (&condition, &mutex); /* On attend que la condition soit remplie */
        printf("\nThAlr : apres cond");
        printf("\nLe compteur a depasse 20.");
        printf("\nThAlr : avant unlock");
        pthread_mutex_unlock(&mutex); /* On déverrouille le mutex */
        printf("\nThAlr : apres unlock");
    }

    pthread_exit(NULL); /* Fin du thread */
}
