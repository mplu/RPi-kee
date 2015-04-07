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

extern pthread_cond_t condition;    /* Cr�ation de la condition */
extern pthread_mutex_t mutex ;      /* Cr�ation du mutex */
extern pthread_mutex_t mtx_AccessRawAnalog ;//Protect Raw Analog data buffer
extern sem_t sem_Img_available; // Indicate new image to handle
extern sem_t sem_ADCData_available; // Indicate new IR data to handle
extern sem_t sem_XMotorEmergencyStop; // Indicate to abort rotation
extern sem_t sem_YMotorEmergencyStop; // Indicate to abort rotation

extern CPU_INT16U g_Raw_AdcValue[ADC_NUMBER_OF_CHANNEL];
extern CPU_CHAR g_nextIMGfilename[IMG_FILENAME_SIZE];
extern t_StepperMotor MotorY_UD;
extern t_StepperMotor MotorX_LR;
extern t_DCMotor DCMotorLeft;
extern t_DCMotor DCMotorRight;
#endif


