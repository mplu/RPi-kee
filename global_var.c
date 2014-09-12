/****************************************************************/
/* Global Variables                                             */
/* File : global_var.h                                          */
/* Description :                                                */
/*   Variables shared between processes                         */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "includes.h"


/*** Mutex, Condition, Semaphore ***/
// Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_AccessRawAnalog = PTHREAD_MUTEX_INITIALIZER; //Protect Raw Analog data buffer

//Conditions
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

//Semaphore
sem_t sem_Img_available; // Indicate new image to handle
sem_t sem_ADCData_available; // Indicate new IR data to handle

/*** Shared Variable ***/
CPU_INT16U g_Raw_AdcValue[ADC_NUMBER_OF_CHANNEL];
