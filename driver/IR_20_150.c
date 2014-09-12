/****************************************************************/
/* Driver for IR Sensor GP2Y0A02YK (20-150cm)                   */
/* File : IR_20-150.c                                           */
/* Description :                                                */
/*   Function use to get data from NearIR Sensor                */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "../includes.h"

/****************************************************************/
/* GetDistancefromNearIR()                                      */
/* Description :                                                */
/*   Calculate distance value from voltage value                */
/*                                                              */
/* Input:                                                       */
/*   voltage - voltage in millivot                              */
/*                                                              */
/* Output:                                                      */
/*   none                                                       */
/* Return:                                                      */
/*   distance in cm                                             */
/*                                                              */
/****************************************************************/
CPU_INT16U GetDistancefromNearIR(CPU_INT16U voltage)
{
    CPU_INT32U distance;

    distance = voltage *2;


    return (CPU_INT16U)distance;
}
