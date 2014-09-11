/****************************************************************/
/* RPi-kee                                                      */
/* File : main.c                                                */
/* Description :                                                */
/*   Start Thread                                               */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#include "includes.h"

/* choose OS by adding -DLinux ou -DWin32 at compilation                                */
/* to install pthread on windows, copy pthreadGC2.dll in <CodeBlocks dir>\MinGW\bin     */
/*                                copy libpthreadGC2.a in <CodeBlocks dir>\MinGW\lib    */
/*                                copy the three .h in <CodeBlocks dir>\MinGW\include   */

/* under windows, add -lpthreadGC2 in link options  */
/* under linux, add -lpthread                       */



int main (void)
{
    pthread_t monThreadCompteur;
    pthread_t monThreadAlarme;
    pthread_create (&monThreadCompteur, NULL, threadCompteur, (void*)NULL);
    pthread_create (&monThreadAlarme, NULL, threadAlarme, (void*)NULL); /* Création des threads */
    pthread_join (monThreadCompteur, NULL);
    pthread_join (monThreadAlarme, NULL); /* Attente de la fin des threads */
    return 0;
}



