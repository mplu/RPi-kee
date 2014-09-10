/****************************************************************/
/* RPi-kee                                                      */
/* File : includes.h                                            */
/* Description :                                                */
/*   Global include file for RPi-kee project                    */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

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
    #warning "Compile for Windows"
    #include <windows.h>
    #define psleep(sec) Sleep ((sec) * 1000)
#elif defined (Linux)
    #warning "Compile for Linux"
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

