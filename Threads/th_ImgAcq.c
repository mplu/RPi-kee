#include "../includes.h"


void* threadImgAcq (void* arg)
{
	CPU_CHAR tampon1[250];
    FILE *sortie;
	
    
	while(1) /* Boucle infinie */
    {
        m_msSleep(CAPTURE_PERIOD);
		memset (tampon1,0,sizeof(tampon1));
		//test if running
		if ((sortie = popen (IMG_TEST_DAEMON, "r")) == NULL) {
                fprintf (stderr, "erreur");
                //return EXIT_FAILURE;
        }
		while (fgets (tampon1, sizeof tampon1, sortie) != NULL) {}
		
		if(strcmp(tampon1,ERROR_NOTRUNNING)==0)
		{
			printf("daemon not running\n");
			printf("Image capture daemon starting...\n");
			system(IMG_START);
			m_sSleep(CAPTURE_WARMUP);
		}else
		{
			printf("daemon running\n");
			if ((sortie = popen (IMG_CAPTURE, "r")) == NULL) 
			{
				fprintf (stderr, "erreur");
				//return EXIT_FAILURE;
			}
			printf("capture ok\n");
		}
    }
    pthread_exit(NULL); /* Fin du thread */
}
