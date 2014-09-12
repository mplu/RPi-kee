/****************************************************************/
/* Driver for ADC MCP3008                                       */
/* File : ADC.h                                                 */
/* Description :                                                */
/*   Function use to get data from ADC                          */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "../includes.h"

//           1024 * VIN
//Val_adc  = -----------
//              VREF


/****************************************************************/
/* GetVoltage()                                                 */
/* Description :                                                */
/*   Calculate voltage value from numerical value return by adc */
/*                                                              */
/* Input:                                                       */
/*   val_adc - ten bits adc value                               */
/*                                                              */
/* Output:                                                      */
/*   none                                                       */
/* Return:                                                      */
/*   voltage in millivolt                                       */
/*                                                              */
/****************************************************************/
CPU_INT16U GetVoltage(CPU_INT16U val_adc)
{
    CPU_INT32U volt;

    volt = val_adc * ADC_V_REF;
    volt = volt / ADC_MAX_VALUE ;

    return (CPU_INT16U)volt;
}

