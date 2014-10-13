/****************************************************************/
/* RPi-kee                                                      */
/* File : app_cfg.h                                             */
/* Description :                                                */
/*   Configuration                                              */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#ifndef __APP_CFG_H
#define __APP_CFG_H

/****************************************************************/
/**           Define                                            */
/****************************************************************/

/* DEBUG *****/
#define DEBUG_LOG_EN    DEF_ENABLED

/* Image Processing ***/
#define GAUSS_SIZE          7
#define SIGMA               3.5
#define NUMBER_OF_SEGMENT   8
#define CONTRAST_TOLERANCE  2

#define CAPTURE_WARMUP		2	//in second
#define CAPTURE_PERIOD		500 //in millisecond
#define IMG_START 			"/usr/bin/raspistill -q 10 -o my_capture.bmp -w 320 -h 240 -s -t 3600000 &"
#define IMG_STOP			"sudo kill -9 `pgrep raspistill`"
#define IMG_TEST_DAEMON		"pgrep raspistill"
#define IMG_CAPTURE			"sudo kill -USR1 `pgrep raspistill`"
#define ERROR_NOTRUNNING	""
#define ERROR_START 		"* failed to open vchiq instance"
#define CAPTURE_OK			""

/* Motor driving */
#define ANGLE_COEF          0.2
#define FLOAT_INT_COEF      100

/* RPi Hardware Define ***/
#define _12V_VOLTAGE_DIVIDER    3
#define SPI_CHAN 				0
#define ADC_NUMBER_OF_CHANNEL   8

/* Semaphore and Thread define *****/
#define SHARED_ONLY_INSIDE      0
#define SHARED_WITH_OUTSIDE     1
#define PEND_BEFORE_POST        0
#define POST_BEFORE_PEND        1
#define SEM_EMPTY				-1
/* Error Management *****/
#define RPIKEE_NO_ERR           0   //  No error
#define RPIKEE_ERR_OOB          1   //  Error : Out of Bound

/* TCP Configuration */
#define DEF_PORT        6523
#define MAX_CLIENTS     1
#define MAX_TCP_DATA    250

#if defined (Win32)
/* Copy of WiringPi define (for Windows usage) */
    #define HIGH	        1
    #define LOW		        0
#elif defined (RPi)
/* Copy of WinSock define (for Rpi usage) */
    #define INVALID_SOCKET  -1
    #define SOCKET_ERROR    -1
#else
    #error "No OS defined"
#endif


/* Custom type used for portability */
typedef            void      CPU_VOID;
typedef  unsigned  char      CPU_CHAR;                          /*  8-bit character                                     */
typedef  unsigned  char      CPU_BOOLEAN;                       /*  8-bit boolean or logical                            */
typedef  unsigned  char      CPU_INT08U;                        /*  8-bit unsigned integer                              */
typedef    signed  char      CPU_INT08S;                        /*  8-bit   signed integer                              */
typedef  unsigned  short     CPU_INT16U;                        /* 16-bit unsigned integer                              */
typedef    signed  short     CPU_INT16S;                        /* 16-bit   signed integer                              */
typedef  unsigned  long      CPU_INT32U;                        /* 32-bit unsigned integer                              */
typedef    signed  long      CPU_INT32S;                        /* 32-bit   signed integer                              */
typedef            float     CPU_FP32;                          /* 32-bit floating point                                */
typedef            double    CPU_FP64;                          /* 64-bit floating point                                */

/* ****** MACRO ******** */
#if DEBUG_LOG_EN == DEF_ENABLED
#define DEBUG_LOG(x)            printf (x);
#else
#define DEBUG_LOG(x)            {};
#endif



#endif
