/****************************************************************/
/* Functions                                                    */
/* File : functions.h                                           */
/* Description :                                                */
/*   Various functions                                          */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

/*** Macro ***/
#if defined (Win32)
    #define m_sSleep(sec)   Sleep ((sec) * 1000)
    #define m_msSleep(ms)   Sleep ((sec) * 1)
#elif defined (RPi)
    #define m_sSleep(sec)   sleep ((sec))
    #define m_msSleep(ms)   msSleepLinux ((ms) * 1)
#else
    #error "No OS defined"
#endif

/*** Prototypes ***/
#if defined (Win32)

#elif defined (RPi)
    CPU_INT32S msSleepLinux( CPU_INT32U timeout_ms );
#else
    #error "No OS defined"
#endif
