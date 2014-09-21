/****************************************************************/
/* Common function for IR Sensor                                */
/* File : IR_Common.h                                           */
/* Description :                                                */
/*   Function use to get data from NearIR Sensor                */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#ifndef __IR_COMMON_H
#define __IR_COMMON_H

/*** Define ***/


/*** Enum ***/


/*** Prototypes ***/
CPU_INT32S Dist_Volt_RangeCheck(CPU_FP32 x,CPU_FP32 * p_InterpoVoltageTable);
CPU_FP32 Dist_Volt_Interpolation(CPU_FP32 x,CPU_FP32 * p_InterpoVoltageTable,CPU_FP32 * p_InterpoDistanceTable);
#endif


