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

#if defined (Win32)
    //#warning "Compile for Windows"
    #include <windows.h>
    #define psleep(sec) Sleep ((sec) * 1000)
#elif defined (RPi)
    //#warning "Compile for Raspberry Pi"
    #include <unistd.h>
    #include <wiringPi.h>
    #define psleep(sec) sleep ((sec))
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

/* Thread Include */
#include "Threads/th_Alarm.h"
#include "Threads/th_Compteur.h"
#include "Threads/th_CtrlCmd.h"
#include "Threads/th_ImgAcq.h"
#include "Threads/th_ImgHandle.h"
#include "Threads/th_MotorLeftdrive.h"
#include "Threads/th_MotorRightdrive.h"
#include "Threads/th_SensorAcq.h"
#include "Threads/th_SensorIRHandle.h"
#include "Threads/th_SensorOtherHandle.h"
#include "Threads/th_TCPCom.h"

#endif
