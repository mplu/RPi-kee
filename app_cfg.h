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

/*** Image Processing ***/
#define GAUSS_SIZE 8
#define SIGMA 10

/*** RPi Hardware Define ***/
#define _12V_VOLTAGE_DIVIDER    3
#define SPI_CHAN 				0

/*********** Semaphore and Thread define *****/
#define SHARED_ONLY_INSIDE      0
#define SHARED_WITH_OUTSIDE     1
#define PEND_BEFORE_POST        0
#define POST_BEFORE_PEND        1

#endif
