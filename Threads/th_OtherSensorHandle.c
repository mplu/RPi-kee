#include "../includes.h"

void* threadOtherSensorHandle (void* arg)
{
	CPU_CHAR tampon[32];
#if defined (Win32)
    CPU_INT16U temp;
    srand(time(NULL));

#elif defined (RPi)
    FILE *sortie;
#endif
    while(1) /* Boucle infinie */
    {
        m_sSleep(1);
#if defined (Win32)
        temp = 3800 + rand()%400;

		tampon[0] = (temp / 1000) ;//+ 0x30;
		tampon[1] = ((temp - tampon[0] * 1000)  / 100)  ;//+ 0x30;
		tampon[2] = ((temp - tampon[0] * 1000 - tampon[1] * 100)/ 10)  ;//+ 0x30;
		tampon[3] = ((temp - tampon[0] * 1000 - tampon[1] * 100 - tampon[2] * 10) / 1)  ;//+ 0x30;

        tampon[0] += 0x30;
		tampon[1] += 0x30;
		tampon[2] += 0x30;
		tampon[3] += 0x30;
#elif defined (RPi)
							//opt/vc/bin/vcgencmd measure_temp
							//cat /sys/class/thermal/thermal_zone0/temp
        if ((sortie = popen ("cat /sys/class/thermal/thermal_zone0/temp", "r")) == NULL)
		{
                fprintf (stderr, "erreur");
        }
		while (fgets ((char *)tampon, sizeof tampon, sortie) != NULL){}
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
