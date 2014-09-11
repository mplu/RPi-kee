/****************************************************************/
/* Global Variables                                             */
/* File : global_var.h                                          */
/* Description :                                                */
/*   Variables shared between processes                         */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "includes.h"


/*** Mutex and Condition ***/
pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Cr�ation de la condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Cr�ation du mutex */
