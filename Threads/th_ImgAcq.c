#include "../includes.h"


void* threadImgAcq (void* arg)
{
	CPU_INT08S tampon1[250];
    CPU_INT08U erreur = FALSE;
    struct timespec m_timeout;
    CPU_INT32U m_error = 0;
	clock_t start, finish;
    double duration;

#if defined (Win32)
    CPU_BOOLEAN firstrun=TRUE;
#elif defined (RPi)
    FILE *sortie;

#endif // defined
    CPU_INT08S number_of_loop = 0;
    CPU_CHAR copy_img_cmd[IMG_FILENAME_SIZE + 10];
	
	m_timeout.tv_sec=  (time_t)(1);
    m_timeout.tv_nsec = 0;
	start = clock();
	while(1) /* Boucle infinie */
    {
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("Acq period  %.3f\n",duration);
        m_msSleep(CAPTURE_PERIOD);
		start = clock();
		
		
        m_error = pthread_mutex_timedlock(&mtx_LockCamera,&m_timeout);
        if(m_error != ETIMEDOUT)
        {
            memset (tampon1,0,sizeof(tampon1));
            erreur = FALSE;
            //test if running
#if defined (Win32)
            if(firstrun == TRUE)
            {tampon1[0] = 0;}
            else
            {tampon1[0] = 1;}
#elif defined (RPi)
            if ((sortie = popen (IMG_TEST_DAEMON, "r")) == NULL)
            {
                fprintf (stderr, "erreur");
                printf("err:reading img daemon state\n");
                erreur = TRUE;
            }else
            {
                erreur = FALSE;
                while (fgets ((char *)tampon1, sizeof tampon1, sortie) != NULL) {}
                pclose (sortie);
            }
            if(erreur == TRUE)
            {
                printf("log after error in popen or fgets\n");
            }
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
                sprintf((char *)copy_img_cmd,"cp %s%s %s",IMG_NAME,IMG_NAME_EXT,g_nextIMGfilename);
                if ((sortie = popen (IMG_CAPTURE, "r")) == NULL)
                {
                    fprintf (stderr, "erreur ");
                    printf("err:capturing img\n");
                    erreur = TRUE;
                }else
                {
                    sprintf((char *)copy_img_cmd,"cp %s%s %s",IMG_NAME,IMG_NAME_EXT,g_nextIMGfilename);
                    erreur = FALSE;
                    pclose (sortie);
                }
#endif // defined
                if(erreur == FALSE)
                {
                    system((const char *)copy_img_cmd);
                    sem_post(&sem_Img_available);
                }

            }
            number_of_loop ++;
            number_of_loop = number_of_loop % 7;
            pthread_mutex_unlock(&mtx_LockCamera);
        }else
        {
            printf("timeout acces camera\n");
        }
    }
    pthread_exit(NULL); /* Fin du thread */
}
