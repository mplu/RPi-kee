#include "../includes.h"



void* threadADCAcq (void* arg)
{
    CPU_INT16U i;
    CPU_INT16U SPI_combuffer[ADC_NUMBER_OF_CHANNEL];
    CPU_CHAR tampon[32];

#if defined (Win32)
    srand(time(NULL));
    CPU_INT16U temp;

#elif defined (RPi)
	mcp3004Setup (ADCBASE_WIRINGPI, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels
	FILE *sortie;
    CPU_INT08U erreur;
#endif

    while(1) /* Boucle infinie */
    {

#if defined (Win32)
        // simulation d'acquisition via ADC
        for(i=0;i<ADC_NUMBER_OF_CHANNEL;i++)
        {
            SPI_combuffer[i] = rand()%ADC_MAX_VALUE;
        }
        SPI_combuffer[Ch0_Vbat] = 900 + (rand()%(100));
        SPI_combuffer[Ch1_Vmot] = 800 + (rand()%(100));
        SPI_combuffer[Ch2_NearIR] = 122 + (rand()%(25));
        SPI_combuffer[Ch3_FarIR] = 500 + (rand()%(50));

        // simulation d'acquisition CPU temp
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
        // acquisition via ADC
        for(i=0;i<ADC_NUMBER_OF_CHANNEL;i++)
        {
                SPI_combuffer[i] = analogRead (ADCBASE_WIRINGPI + i) ;
        }

        // acquisition CPU temp
        erreur = FALSE;
							//opt/vc/bin/vcgencmd measure_temp
							//cat /sys/class/thermal/thermal_zone0/temp
        if ((sortie = popen ("cat /sys/class/thermal/thermal_zone0/temp", "r")) == NULL)
		{
            fprintf (stderr, "erreur");
            printf("err:reading cpu temp\n");
            erreur = TRUE;
        }else
        {
            while (fgets ((char *)tampon, sizeof tampon, sortie) != NULL){}
            pclose (sortie);
		erreur = FALSE;
        }
        if(erreur == TRUE)
        {
            printf("errer during temperature file read\n");
        }
#endif

        Params.Analog_Values.VoltageBattery     = GetVoltage(SPI_combuffer[Ch0_Vbat]);
        Params.Analog_Values.Voltage12V         = _12V_VOLTAGE_DIVIDER * GetVoltage(SPI_combuffer[Ch1_Vmot]);
        Params.Analog_Values.ShortIRDistance    = GetDistancefromNearIR(GetVoltage(SPI_combuffer[Ch2_NearIR]));
        Params.Analog_Values.LongIRDistance     = GetDistancefromFarIR(GetVoltage(SPI_combuffer[Ch3_FarIR]));

        Params.Analog_Values.CPUTemperature =
				+(tampon[3]-0x30)*1
				+(tampon[2]-0x30)*10
				+(tampon[1]-0x30)*100
				+(tampon[0]-0x30)*1000;

        m_msSleep(1000);
    }

    pthread_exit(NULL); /* Fin du thread */
}
