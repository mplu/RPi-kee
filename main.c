/****************************************************************/
/* RPi-kee                                                      */
/* File : main.c                                                */
/* Description :                                                */
/*   Start Thread                                               */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#include "includes.h"

/* choose OS by adding -DLinux ou -DWin32 at compilation                                */
/* to install pthread on windows, copy pthreadGC2.dll in <CodeBlocks dir>\MinGW\bin     */
/*                                copy libpthreadGC2.a in <CodeBlocks dir>\MinGW\lib    */
/*                                copy the three .h in <CodeBlocks dir>\MinGW\include   */

/* under windows, add -lpthreadGC2 in link options  */
/* under linux, add -lpthread                       */



int main (void)
{
    pthread_t desc_ThreadACDAcq;
    pthread_t desc_ThreadACDDataHandle;
    pthread_t desc_ThreadCtrlCmd;
    pthread_t desc_ThreadDebug;
    pthread_t desc_ThreadImgAcq;
    pthread_t desc_ThreadImgHandle;
    pthread_t desc_ThreadMotorLeftdrive;
    pthread_t desc_ThreadMotorRightdrive;
    pthread_t desc_ThreadOtherSensorHandle;
    pthread_t desc_ThreadProtections;
    pthread_t desc_ThreadTCPCom;
    pthread_t desc_ThreadMotorXSurvey;
    pthread_t desc_ThreadMotorYSurvey;

	// Driver Initialization
#if defined (RPi)
	if (wiringPiSetup () == -1)
	{
		printf ("wiringPiSetup () failed \n") ;
		exit (1) ;
	}
	if (gpioInitialise() < 0)
	{
	   // pigpio initialisation failed.
	   printf("pigpio initialisation failed\n");
	}
	else
	{
	   // pigpio initialised okay.
	   printf("pigpio initialised okay\n");
	}
#endif

    // Data Initialization
    Init_Params();
    sem_init(&sem_Img_available,SHARED_ONLY_INSIDE,PEND_BEFORE_POST);
    sem_init(&sem_ADCData_available,SHARED_ONLY_INSIDE,PEND_BEFORE_POST);

    /* thread creation */
    pthread_create (&desc_ThreadACDAcq, NULL, threadADCAcq, (void*)NULL);
    pthread_create (&desc_ThreadACDDataHandle, NULL, threadADCDataHandle, (void*)NULL);
    pthread_create (&desc_ThreadCtrlCmd, NULL, threadCtrlCmd, (void*)NULL);
    pthread_create (&desc_ThreadDebug, NULL, threadDebug, (void*)NULL);
    pthread_create (&desc_ThreadImgAcq, NULL, threadImgAcq, (void*)NULL);
    pthread_create (&desc_ThreadImgHandle, NULL, threadImgHandle, (void*)NULL);
    pthread_create (&desc_ThreadMotorLeftdrive, NULL, threadMotorLeftdrive, (void*)NULL);
    pthread_create (&desc_ThreadMotorRightdrive, NULL, threadMotorRightdrive, (void*)NULL);
    pthread_create (&desc_ThreadOtherSensorHandle, NULL, threadOtherSensorHandle, (void*)NULL);
    pthread_create (&desc_ThreadProtections, NULL, threadProtections, (void*)NULL);
    pthread_create (&desc_ThreadTCPCom, NULL, threadTCPCom, (void*)NULL);
    pthread_create (&desc_ThreadMotorXSurvey, NULL, threadMotorXSurvey, (void*)NULL);
    pthread_create (&desc_ThreadMotorYSurvey, NULL, threadMotorYSurvey, (void*)NULL);


    /* Attente de la fin des threads */
    pthread_join (desc_ThreadACDAcq, NULL);
    pthread_join (desc_ThreadACDDataHandle, NULL);
    pthread_join (desc_ThreadCtrlCmd, NULL);
    pthread_join (desc_ThreadDebug, NULL);
    pthread_join (desc_ThreadImgAcq, NULL);
    pthread_join (desc_ThreadImgHandle, NULL);
    pthread_join (desc_ThreadMotorLeftdrive, NULL);
    pthread_join (desc_ThreadMotorRightdrive, NULL);
    pthread_join (desc_ThreadOtherSensorHandle, NULL);
    pthread_join (desc_ThreadProtections, NULL);
    pthread_join (desc_ThreadTCPCom, NULL);
    pthread_join (desc_ThreadMotorXSurvey, NULL);
    pthread_join (desc_ThreadMotorYSurvey, NULL);
    return 0;
}

