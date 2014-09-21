/****************************************************************/
/* Common function for IR Sensor                                */
/* File : IR_Common.c                                           */
/* Description :                                                */
/*   Function use to get data from NearIR Sensor                */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "../includes.h"




/****************************************************************************/
/*	 CPU_INT32S Dist_Volt_RangeCheck(float x)						*/
/*--------------------------------------------------------------------------*/
/*	DESCRIPTION : Determine if x stays in the distance range				*/
/*							----------------								*/
/*	INPUT : 	x															*/
/*							----------------								*/
/*	OUTPUT:	  	RPIKEE_NO_ERR  	: measure is treatable				        */
/*				RPIKEE_ERR_OOB 	: measure is out of input range				*/
/****************************************************************************/
CPU_INT32S Dist_Volt_RangeCheck(CPU_FP32 x,CPU_FP32 * p_InterpoVoltageTable, CPU_INT16U size)
{
	CPU_INT16S index_max = size;
	CPU_INT32S ret;

	if (x > p_InterpoVoltageTable[0])
	{
		ret = RPIKEE_ERR_OOB;
	}
	else if (x < p_InterpoVoltageTable[index_max-1])
	{
		ret = RPIKEE_ERR_OOB;
	}
	else
	{
		ret = RPIKEE_NO_ERR;
	}
	return ret;

}


/********************************************************************************************************/
/*	 CPU_FP32 Dist_Volt_Interpolation()				                                                    */
/*------------------------------------------------------------------------------------------------------*/
/*	DESCRIPTION : Determine the parameters for calculating the distance based on a voltage on IR sensor	*/
/*							----------------															*/
/*	INPUT : 	x																						*/
/*																									    */
/*							----------------															*/
/*	OUTPUT:	  	distance																				*/
/********************************************************************************************************/
CPU_FP32 Dist_Volt_Interpolation(CPU_FP32 x,CPU_FP32 * p_InterpoVoltageTable,CPU_FP32 * p_InterpoDistanceTable,CPU_INT16U size)
{
	CPU_INT16S index_max = size;
    CPU_FP32 X1, X2, Y1, Y2;
	CPU_INT32S median = 0, start_ind = 0, end_ind = index_max - 1;

	{	// dichotomic research
		while(start_ind <= end_ind)
		{
		    median = (start_ind+end_ind)/2;
		    if((p_InterpoVoltageTable[median] <= x) && (p_InterpoVoltageTable[median+1] > x))
		    {
		    	start_ind = end_ind + 1;
		    }
		    else if(p_InterpoVoltageTable[median] < x)
		    {
		    	start_ind = median+1;
		    }

		    else if(p_InterpoVoltageTable[median] >= x)
		    {
		    	end_ind = median-1;
		    }

    	}

    	Y1 = p_InterpoDistanceTable[median];
		Y2 = p_InterpoDistanceTable[median+1];
		X1 = p_InterpoVoltageTable[median];
		X2 = p_InterpoVoltageTable[median+1];

		return ((( x - X1)*(Y2-Y1)/(X2-X1))+Y1);
	}
}
