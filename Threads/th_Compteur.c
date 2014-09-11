#include "../includes.h"



void* threadCompteur (void* arg)
{
    int compteur = 0, nombre = 0;

    srand(time(NULL));
    while(1) /* Boucle infinie */
    {
        nombre = rand()%10; /* On tire un nombre entre 0 et 10 */
        compteur += nombre; /* On ajoute ce nombre à la variable compteur */
        printf("\n%d", compteur);

        if(compteur >= 20) /* Si compteur est plus grand ou égal à 20 */
        {
            printf("\nThCpt : avant lock");
            pthread_mutex_lock (&mutex); /* On verrouille le mutex */
            printf("\nThCpt : apres lock");
            pthread_cond_signal (&condition); /* On délivre le signal : condition remplie */
            printf("\nThCpt : avant unlock");
            pthread_mutex_unlock (&mutex); /* On déverrouille le mutex */
            printf("\nThCpt : apres unlock");
            compteur = 0; /* On remet la variable compteur à 0 */
        }
        psleep (1); /* On laisse 1 seconde de repos */
    }

    pthread_exit(NULL); /* Fin du thread */
}
