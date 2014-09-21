#include "../includes.h"

void* threadADCDataHandle (void* arg)
{
    CPU_INT16U LocalRawValue[ADC_NUMBER_OF_CHANNEL];
    CPU_INT16U i;

    while(1) /* Boucle infinie */
    {
        sem_wait(&sem_ADCData_available);
        DEBUG_LOG("ADC data treatment\n");
        pthread_mutex_lock(&mtx_AccessRawAnalog);
        for(i=0;i<ADC_NUMBER_OF_CHANNEL;i++)
        {
            LocalRawValue[i] = g_Raw_AdcValue[i];
        }
        pthread_mutex_unlock(&mtx_AccessRawAnalog);

        Params.Analog_Values.VoltageBattery     = GetVoltage(LocalRawValue[Ch0_Vbat]);
        Params.Analog_Values.Voltage12V         = _12V_VOLTAGE_DIVIDER * GetVoltage(LocalRawValue[Ch1_Vmot]);
        Params.Analog_Values.ShortIRDistance    = GetDistancefromNearIR(GetVoltage(LocalRawValue[Ch2_NearIR]));
        Params.Analog_Values.LongIRDistance     = GetDistancefromFarIR(GetVoltage(LocalRawValue[Ch3_FarIR]));

    }

    pthread_exit(NULL); /* Fin du thread */
}
