/****************************************************************/
/* Driver for ADC MCP3008                                       */
/* File : ADC.h                                                 */
/* Description :                                                */
/*   Function use to get data from ADC                          */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#ifndef __ADC_H
#define __ADC_H

/*** Define ***/
#define ADC_NUMBER_OF_CHANNEL   8
#define ADC_MAX_VALUE           1024    // ADC precision
#define ADC_V_REF               5000    // V_ref in millivolt

/*** Enum ***/
enum e_AdcChannel
{
    Ch0_Vbat,
    Ch1_Vmot,
    Ch2_NearIR,
    Ch3_FarIR,
    Ch4,
    Ch5,
    Ch6,
    Ch7,
    Ch8
};

/*** Prototypes ***/
CPU_INT16U GetVoltage(CPU_INT16U val_adc);

#endif


