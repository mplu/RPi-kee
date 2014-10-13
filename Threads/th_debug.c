#include "../includes.h"



void* threadDebug (void* arg)
{

    /*e_RPK_Error rpk_err;
    CPU_INT08U buffer[RPK_MAX_DATA]={0};

    // header
    buffer[0] = RPK_RASPBERRY_PI_HANDLE;
    buffer[2] = RPK_VERSION;
    buffer[4] = 20 ;
    buffer[6] = 14;
    buffer[8] = 17;
    buffer[10] = 0;
    buffer[12] = 4;

    //data
    buffer[14] = 31;
    buffer[15] = 32;
    buffer[16] = 33;
    buffer[17] = 34;

    // chekcsum
    buffer[18] = 0x68;
    buffer[19] = 0xab;

    rpk_err = RPK_Frame_Manage(buffer, 20, &g_rpkframe_in);*/

    while(1) /* Boucle infinie */
    {
#if DEBUG_LOG_EN == DEF_ENABLED
        /*printf("Battery  %6d\n",Params.Analog_Values.VoltageBattery);
		printf("12V mes  %6d\n",Params.Analog_Values.Voltage12V);
		printf("CPU temp %6d\n",Params.Analog_Values.CPUTemperature);*/
#endif
        m_sSleep (1); /* On laisse 1 seconde de repos */
    }

    pthread_exit(NULL); /* Fin du thread */
}
