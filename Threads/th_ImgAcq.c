#include "../includes.h"


void* threadImgAcq (void* arg)
{
	CPU_INT08S tampon1[250];
#if defined (Win32)
    CPU_BOOLEAN firstrun=TRUE;
#elif defined (RPi)
    FILE *sortie;
#endif // defined


	while(1) /* Boucle infinie */
    {
        m_msSleep(CAPTURE_PERIOD);
		memset (tampon1,0,sizeof(tampon1));
		//test if running
#if defined (Win32)
        if(firstrun == TRUE)
        {tampon1[0] = 0;}
        else
        {tampon1[0] = 1;}
#elif defined (RPi)
        if ((sortie = popen (IMG_TEST_DAEMON, "r")) == NULL) {
                fprintf (stderr, "erreur");
        }
		while (fgets ((char *)tampon1, sizeof tampon1, sortie) != NULL) {}
#endif

		if(strcmp((char *)tampon1,ERROR_NOTRUNNING)==0)
		{
			//printf("daemon not running\n");
			//printf("Image capture daemon starting...\n");
#if defined (Win32)
            firstrun = FALSE;
#elif defined (RPi)
            system(IMG_START);
#endif // defined
			m_sSleep(CAPTURE_WARMUP);
		}else
		{
			//printf("daemon running\n");
#if defined (RPi)
            if ((sortie = popen (IMG_CAPTURE, "r")) == NULL)
			{
				fprintf (stderr, "erreur");
			}
#endif // defined
			//printf("capture ok\n");
			system("cp my_capture.bmp my_capture_1.bmp");
			sem_post(&sem_Img_available);
		}
    }
    pthread_exit(NULL); /* Fin du thread */
}
