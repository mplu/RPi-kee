/****************************************************************/
/* Global Variables                                             */
/* File : global_var.h                                          */
/* Description :                                                */
/*   Variables shared between processes                         */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#ifndef __GLOBAL_VAR_H
#define __GLOBAL_VAR_H

extern pthread_cond_t condition;    /* Création de la condition */
extern pthread_mutex_t mutex ;      /* Création du mutex */
extern pthread_mutex_t mtx_AccessRawAnalog ;//Protect Raw Analog data buffer
extern sem_t sem_Img_available; // Indicate new image to handle
extern sem_t sem_ADCData_available; // Indicate new IR data to handle
extern sem_t sem_LeftMotorEmergencyStop; // Indicate to abort rotation
extern sem_t sem_RightMotorEmergencyStop; // Indicate to abort rotation

extern CPU_INT16U g_Raw_AdcValue[ADC_NUMBER_OF_CHANNEL];

#endif


