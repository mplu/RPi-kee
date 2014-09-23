#include "../includes.h"



void* threadDebug (void* arg)
{
#if 0
    int compteur = 0, nombre = 0;
#endif
    srand(time(NULL));
    while(1) /* Boucle infinie */
    {
#if DEBUG_LOG_EN == DEF_ENABLED
        printf("Battery,12V %6d %6d\n",Params.Analog_Values.VoltageBattery,Params.Analog_Values.Voltage12V);
#endif
        m_sSleep (1); /* On laisse 1 seconde de repos */
    }

    pthread_exit(NULL); /* Fin du thread */
}
