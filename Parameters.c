/****************************************************************/
/* Parameters list                                              */
/* File : Parameters.c                                          */
/* Description :                                                */
/*   Global Parameters list for internal and external com       */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/
#include "includes.h"

const char SOFT_VER[]   = "0.1.0";
const char PARAM_VER[]  = "1";

t_Param Params;

static t_paramblock const p_rec_Info =
{
                        1,  /* Parameter ID */
             &Params.Info,  /* Pointer to parameter value(s) in table 1 */
                       64,  /* Size in bytes */
                        0,  /* Security and storage flags */
};

static t_paramblock const p_rec_Analog_Values =
{
                        2,  /* Parameter ID */
    &Params.Analog_Values,  /* Pointer to parameter value(s) in table 1 */
                       12,  /* Size in bytes */
                        0,  /* Security and storage flags */
};

static t_paramblock const p_rec_LeftMotorCommand =
{
                        3,  /* Parameter ID */
 &Params.LeftMotorCommand,  /* Pointer to parameter value(s) in table 1 */
                        4,  /* Size in bytes */
                        0,  /* Security and storage flags */
};

static t_paramblock const p_rec_RightMotorCommand =
{
                        4,  /* Parameter ID */
 &Params.LeftMotorCommand,  /* Pointer to parameter value(s) in table 1 */
                        4,  /* Size in bytes */
                        0,  /* Security and storage flags */
};

static t_paramblock const p_rec_CommandReg =
{
                        5,  /* Parameter ID */
       &Params.CommandReg,  /* Pointer to parameter value(s) in table 1 */
                        64, /* Size in bytes */
                        0,  /* Security and storage flags */
};

static t_paramblock const p_rec_StatusReg =
{
                        6,  /* Parameter ID */
     &Params.StatusReg,  /* Pointer to parameter value(s) in table 1 */
                        6,  /* Size in bytes */
                        0,  /* Security and storage flags */
};

static t_paramblock const p_rec_FailureReg =
{
                        7,  /* Parameter ID */
       &Params.FailureReg,  /* Pointer to parameter value(s) in table 1 */
                        2,  /* Size in bytes */
                        0,  /* Security and storage flags */
};

static t_paramblock const p_rec_ProtectionConf =
{
                        8,  /* Parameter ID */
   &Params.ProtectionConf,  /* Pointer to parameter value(s) in table 1 */
                       40,  /* Size in bytes */
                        0,  /* Security and storage flags */
};


const t_paramblock* ParamMap[] = {
	&p_rec_Info,
	&p_rec_Analog_Values,
	&p_rec_LeftMotorCommand,
	&p_rec_RightMotorCommand,
	&p_rec_CommandReg,
	&p_rec_StatusReg,
	&p_rec_FailureReg,
	&p_rec_ProtectionConf,
    NULL
};



/*** Parameter Initializations ***/

CPU_VOID Init_Params()
{
	strcpy((char *)Params.Info.SoftVersion,SOFT_VER);
	strcpy((char *)Params.Info.ParamVersion,PARAM_VER);



    Params.Analog_Values.LongIRDistance = 0;
    Params.Analog_Values.ShortIRDistance = 0;
    Params.Analog_Values.VoltageBattery = 0;
    Params.Analog_Values.Voltage12V = 0;
    Params.Analog_Values.CPUTemperature = 0;
    Params.Analog_Values.AuxTemperature = 0;

    Params.LeftMotorCommand.Steps = 0;
    Params.LeftMotorCommand.Delay = 0;

    Params.RightMotorCommand.Steps = 0;
    Params.RightMotorCommand.Delay = 0;

    Params.CommandReg.Manual = 0;
    Params.CommandReg.Auto = 0;
    Params.CommandReg.MoveDirection = 0;
    Params.CommandReg.MoveDuration = 0;
    Params.CommandReg.UDPLiveFeed = 0;
    Params.CommandReg.MotorPSEnable = 0;

    Params.StatusReg.Manual = 0;
    Params.StatusReg.Auto = 0;
    Params.StatusReg.MoveDirection = 0;
    Params.StatusReg.MoveDuration = 0;
    Params.StatusReg.UDPLiveFeed = 0;
    Params.StatusReg.MotorPSEnable = 0;

    Params.FailureReg.global_1.all = 0;

    Params.ProtectionConf.IRDistanceDetect.DetectionThreshold = 0;
    Params.ProtectionConf.IRDistanceDetect.CompDirection = -1;
    Params.ProtectionConf.IRDistanceDetect.TimeWindow = 100;
    Params.ProtectionConf.IRDistanceDetect.ConfThreshold = 80;

    Params.ProtectionConf.VoltageBatteryDetect.DetectionThreshold = 4500;
    Params.ProtectionConf.VoltageBatteryDetect.CompDirection = -1;
    Params.ProtectionConf.VoltageBatteryDetect.TimeWindow = 100;
    Params.ProtectionConf.VoltageBatteryDetect.ConfThreshold = 80;

    Params.ProtectionConf.Voltage12VDetect.DetectionThreshold = 10000;
    Params.ProtectionConf.Voltage12VDetect.CompDirection = -1;
    Params.ProtectionConf.Voltage12VDetect.TimeWindow = 100;
    Params.ProtectionConf.Voltage12VDetect.ConfThreshold = 80;

    Params.ProtectionConf.CPUTemperatureDetect.DetectionThreshold = 80;
    Params.ProtectionConf.CPUTemperatureDetect.CompDirection = 1;
    Params.ProtectionConf.CPUTemperatureDetect.TimeWindow = 1000;
    Params.ProtectionConf.CPUTemperatureDetect.ConfThreshold = 800;

    Params.ProtectionConf.AuxTemperatureDetect.DetectionThreshold = 20;
    Params.ProtectionConf.AuxTemperatureDetect.CompDirection = 1;
    Params.ProtectionConf.AuxTemperatureDetect.TimeWindow = 1000;
    Params.ProtectionConf.AuxTemperatureDetect.ConfThreshold = 800;

}

CPU_INT16U* GetPointerFromParamID(CPU_INT16U paramID)
{
	const t_paramblock* param = NULL;
	CPU_INT16U  i;

	// Search for the parameter record
	for (i = 0; i < e_NumberOfParam; i++)
	{
		if (ParamMap[i]->id == paramID)
		{
			param = ParamMap[i];
			break;
		}
	}

//	AssertE(param != NULL, "Invalid paramID");


		return (CPU_INT16U*)param->pValue;

}

CPU_VOID SetValueFromParamID(CPU_INT16U paramID, const CPU_INT16U* paramValues)
{
	const t_paramblock* param = NULL;
	CPU_INT16U  i;

	// Search for the parameter record
	for (i = 0; i < e_NumberOfParam; i++)
	{
		if (ParamMap[i]->id == paramID)
		{
			param = ParamMap[i];
			break;
		}
	}

      memcpy((CPU_VOID*)param->pValue, paramValues, param->psize);

}

CPU_INT16U GetSizeFromParamID(CPU_INT16U paramID)
{
  const t_paramblock* param = NULL;
  CPU_INT16U  i;

  // Search for the parameter record
  for (i = 0; i < e_NumberOfParam; i++)
  {
    if (ParamMap[i]->id == paramID)
    {
      param = ParamMap[i];
      break;
    }
  }

  return param->psize;

}