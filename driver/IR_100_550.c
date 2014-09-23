/****************************************************************/
/* Driver for IR Sensor GP2Y0A710K0F (100-550cm)                */
/* File : IR_100_550.c                                          */
/* Description :                                                */
/*   Function use to get data from FarIR Sensor                 */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "../includes.h"

/********** PT100_Interpolation Table for voltage *******/
const CPU_FP32 InterpoVoltageTablefor100_550[] = {
//3.08,
//3.07,
3.08,
2.88,
2.67,
2.54,
2.40,
2.20,
2.01,
1.94,
1.87,
1.65,
1.54,
1.48,
1.43
} ;

/****** Distance Interpolation Table *******/
const CPU_FP32 InterpoDistanceTablefor100_550[] = {
//50,
//60,
70,
80,
90,
100,
110,
130,
150,
175,
200,
250,
300,
350,
400
} ;


/****************************************************************/
/* GetDistancefromFarIR()                                       */
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
CPU_INT16U GetDistancefromFarIR(CPU_INT16U voltage)
{
    CPU_INT32U distance;
    CPU_FP32 f_voltage = voltage/1000.0;
#if defined (Win32)
    f_voltage = 2.81;
#endif
    if(Dist_Volt_RangeCheck(f_voltage,(CPU_FP32*)&InterpoVoltageTablefor100_550,13) == RPIKEE_NO_ERR)
    {
        distance = (CPU_INT32U)Dist_Volt_Interpolation(f_voltage,(CPU_FP32*)&InterpoVoltageTablefor100_550,(CPU_FP32*)&InterpoDistanceTablefor100_550,13);
    }else
    {
        distance = 0xFFFF;
    }

    return (CPU_INT16U)distance;
}





