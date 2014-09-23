#include "../includes.h"



void* threadADCAcq (void* arg)
{
    CPU_INT16U i;
    CPU_INT16U SPI_combuffer[ADC_NUMBER_OF_CHANNEL];

#if defined (Win32)
    srand(time(NULL));
#elif defined (RPi)
	mcp3004Setup (ADCBASE_WIRINGPI, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels
#endif

    while(1) /* Boucle infinie */
    {
        // Communication with ADC through SPI
#if defined (Win32)
        for(i=0;i<ADC_NUMBER_OF_CHANNEL;i++)
        {
            SPI_combuffer[i] = rand()%ADC_MAX_VALUE;
        }
#elif defined (RPi)
        for(i=0;i<ADC_NUMBER_OF_CHANNEL;i++)
        {
                SPI_combuffer[i] = analogRead (ADCBASE_WIRINGPI + i) ;
        }
#endif
        // Writing data into shared buffer
        pthread_mutex_lock(&mtx_AccessRawAnalog);
        for(i=0;i<ADC_NUMBER_OF_CHANNEL;i++)
        {
            g_Raw_AdcValue[i] = SPI_combuffer[i];
        }
        pthread_mutex_unlock(&mtx_AccessRawAnalog);

        // indicate that data is available
        sem_post(&sem_ADCData_available);
        m_msSleep(1000);
    }

    pthread_exit(NULL); /* Fin du thread */
}
