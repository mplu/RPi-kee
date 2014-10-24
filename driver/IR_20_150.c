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

/********** PT100_Interpolation Table for voltage *******/
const CPU_FP32 InterpoVoltageTablefor20_150[] = {
//1.81,
//2.65,
2.72,
2.51,
2.20,
1.96,
1.51,
1.21,
1.00,
0.85,
0.76,
0.65,
0.60,
0.54,
0.50,
0.44,
0.36,
} ;

/****** Distance Interpolation Table *******/
const CPU_FP32 InterpoDistanceTablefor20_150[] = {
//5,
//10,
15,
20,
25,
30,
40,
50,
60,
70,
80,
90,
100,
110,
120,
133,
150
} ;



/********************************************//**
 * \brief Calculate distance value from voltage value
 *
 * \param voltage CPU_INT16U voltage in millivolt
 * \return CPU_INT16U distance in cm
 *
 ***********************************************/
CPU_INT16S GetDistancefromNearIR(CPU_INT16U voltage)
{
    CPU_INT16S distance;
    CPU_FP32 f_voltage = voltage/1000.0;
    CPU_INT08U check;

    check = Dist_Volt_RangeCheck(f_voltage,(CPU_FP32*)&InterpoVoltageTablefor20_150,15);

    switch(check)
    {
        case RPIKEE_NO_ERR:
            distance = (CPU_INT16S)Dist_Volt_Interpolation(f_voltage,(CPU_FP32*)&InterpoVoltageTablefor20_150,(CPU_FP32*)&InterpoDistanceTablefor20_150,15);
            break;
        case RPIKEE_ERR_OOB_TOO_CLOSE:
            distance = 0;
            break;
        case RPIKEE_ERR_OOB_TOO_FAR:
            distance = 0x7FFF;
            break;
        default:
            distance = 0xFFFF;
            break;
    }

    return distance;
}

