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
#define GAUSS_SIZE 8
#define SIGMA 10

/*********** Semaphore and Thread define *****/
#define SHARED_ONLY_INSIDE      0
#define SHARED_WITH_OUTSIDE     1
#define PEND_BEFORE_POST        0
#define POST_BEFORE_PEND        1

#endif
