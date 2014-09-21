/****************************************************************/
/* RPi-kee                                                      */
/* File : includes.h                                            */
/* Description :                                                */
/*   Global include file for RPi-kee project                    */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#ifndef __INCLUDES_H
#define __INCLUDES_H
/****************************************************************/
/**           Includes                                          */
/****************************************************************/
/* Standard include */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#if defined (Win32)
    #include <windows.h>
#elif defined (RPi)
    #include <unistd.h>
    #include <wiringPi.h>
	#include <mcp3004.h>
#else
    #error "No OS defined"
#endif

/* LLIPS include */
#include "llips/llips_includes.h"

/* RPi-kee configuration */
#include "app_cfg.h"

/* Global data */
#include "global_var.h"
#include "Parameters.h"

/* Hardware Layer Drivers */
#include "driver/ADC.h"
#include "driver/Motor.h"
#include "driver/IR_Common.h"
#include "driver/IR_100_550.h"
#include "driver/IR_20_150.h"

/* Sub Functions */
#include "Functions/functions.h"
#include "Functions/MotorCommands.h"

/* Thread Include */
#include "Threads/th_ADC_Acq.h"
#include "Threads/th_ADC_Data_Handle.h"
#include "Threads/th_CtrlCmd.h"
#include "Threads/th_debug.h"
#include "Threads/th_ImgAcq.h"
#include "Threads/th_ImgHandle.h"
#include "Threads/th_MotorLeftdrive.h"
#include "Threads/th_MotorRightdrive.h"
#include "Threads/th_OtherSensorHandle.h"
#include "Threads/th_Protections.h"
#include "Threads/th_TCPCom.h"


#endif
