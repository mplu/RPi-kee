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

extern pthread_cond_t condition;    /* Création de la condition */
extern pthread_mutex_t mutex ;      /* Création du mutex */


#endif


