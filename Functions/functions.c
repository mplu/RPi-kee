/****************************************************************/
/* Functions                                                    */
/* File : functions.c                                           */
/* Description :                                                */
/*   Various functions                                          */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#include "../includes.h"

#if defined (RPi)
CPU_INT32S msSleepLinux( CPU_INT32U timeout_ms )
{
        struct timeval tv;
        tv.tv_sec = timeout_ms/1000;
        tv.tv_usec = (timeout_ms%1000) * 1000;
        select(0, NULL, NULL, NULL, &tv);
        return 0;
}
#endif
