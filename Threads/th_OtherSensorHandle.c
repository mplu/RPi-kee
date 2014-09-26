#include "../includes.h"

void* threadOtherSensorHandle (void* arg)
{
	CPU_CHAR tampon[32];
#if defined (RPi)
    FILE *sortie;
#endif
    while(1) /* Boucle infinie */
    {
        m_sSleep(1);
#if defined (Win32)
		tampon[3] = 0x32;
		tampon[2] = 0x37;
		tampon[1] = 0x31;
		tampon[0] = 0x34;
#elif defined (RPi)
							//opt/vc/bin/vcgencmd measure_temp
							//cat /sys/class/thermal/thermal_zone0/temp
        if ((sortie = popen ("cat /sys/class/thermal/thermal_zone0/temp", "r")) == NULL)
		{
                fprintf (stderr, "erreur");
        }
		while (fgets (tampon, sizeof tampon, sortie) != NULL){}
#endif

		Params.Analog_Values.CPUTemperature =
				+(tampon[3]-0x30)*1
				+(tampon[2]-0x30)*10
				+(tampon[1]-0x30)*100
				+(tampon[0]-0x30)*1000;
#if defined (RPi)
        pclose (sortie);
#endif
    }

    pthread_exit(NULL); /* Fin du thread */
}
