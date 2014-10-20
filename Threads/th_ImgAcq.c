#include "../includes.h"


void* threadImgAcq (void* arg)
{
	CPU_INT08S tampon1[250];
#if defined (Win32)
    CPU_BOOLEAN firstrun=TRUE;
#elif defined (RPi)
    FILE *sortie;
#endif // defined
    CPU_INT08S number_of_loop = 0;
    CPU_CHAR copy_img_cmd[IMG_FILENAME_SIZE + 10];

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
			sprintf((char *)g_nextIMGfilename,"%s%d%s",IMG_NAME,number_of_loop,IMG_NAME_EXT);
#if defined (Win32)
            sprintf((char *)copy_img_cmd,"copy ligne%d.bmp %s",number_of_loop,g_nextIMGfilename);
#elif defined (RPi)
            sprintf((char *)copy_img_cmd,"copy %s%s %s",IMG_NAME,IMG_NAME_EXT,g_nextIMGfilename);
            if ((sortie = popen (IMG_CAPTURE, "r")) == NULL)
			{
				fprintf (stderr, "erreur");
			}
			system("cp my_capture.bmp my_capture_1.bmp");
#endif // defined
            system((const char *)copy_img_cmd);
			sem_post(&sem_Img_available);
		}
		number_of_loop ++;
		number_of_loop = number_of_loop % 7;
    }
    pthread_exit(NULL); /* Fin du thread */
}
