/****************************************************************/
/* Parameters list                                              */
/* File : Parameters.h                                          */
/* Description :                                                */
/*   Global Parameters list for internal and external com       */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#ifndef __PARAMETERS_H
#define __PARAMETERS_H

typedef struct
{
	CPU_INT16S Speed;
	CPU_INT16S Steps;
}t_MOTOR_COMMAND;

typedef struct
{
	CPU_INT08S SoftVersion[32];
	CPU_INT08S ParamVersion[32];
}t_GENERAL_INFO;

typedef struct
{
	CPU_INT16S LongIRDistance;
	CPU_INT16S ShortIRDistance;
	CPU_INT16S VoltageBattery;
	CPU_INT16S Voltage12V;
	CPU_INT16S CPUTemperature;
	CPU_INT16S AuxTemperature;
	CPU_INT16S ImgMoveDirection;
}t_ANALOG_VALUES;

typedef struct
{
	CPU_INT08U Manual;
	CPU_INT08U LineFollow;
    CPU_INT08U Survey;
	CPU_INT08U UDPLiveFeed;
	CPU_INT08U MovementMotorEnable;
	CPU_INT08U TurretMotorEnable;
	CPU_INT16S MoveDirection;
	CPU_INT16U MoveDuration;
}t_COMMAND_REG;

typedef struct
{
	CPU_INT08U Manual;
	CPU_INT08U LineFollow;
    CPU_INT08U Survey;
	CPU_INT08U UDPLiveFeed;
	CPU_INT08U MovementMotorEnable;
	CPU_INT08U TurretMotorEnable;
	CPU_INT16S MoveDirection;
	CPU_INT16U MoveDuration;
}t_STATUS_REG;

typedef struct
{
	CPU_INT16S DetectionThreshold;
	CPU_INT16S CompDirection;
	CPU_INT16U TimeWindow;
	CPU_INT16U ConfThreshold;
}t_GENERIC_PROTECTION;

typedef struct
{
    t_GENERIC_PROTECTION IRDistanceDetect;
    t_GENERIC_PROTECTION VoltageBatteryDetect;
    t_GENERIC_PROTECTION Voltage12VDetect;
    t_GENERIC_PROTECTION CPUTemperatureDetect;
    t_GENERIC_PROTECTION AuxTemperatureDetect;
}t_PROTECTION_CONF;


typedef struct
{
	CPU_INT16U IRDistance:1;
	CPU_INT16U BatteryVoltageLow:1;
	CPU_INT16U MotorVoltageLow:1;
	CPU_INT16U CPU_Temp_High:1;
	CPU_INT16U Aux_Temp_High:1;
	CPU_INT16U unused5:1;
	CPU_INT16U unused6:1;
	CPU_INT16U unused7:1;
	CPU_INT16U unused8:1;
	CPU_INT16U unused9:1;
	CPU_INT16U unused10:1;
	CPU_INT16U unused11:1;
	CPU_INT16U unused12:1;
	CPU_INT16U unused13:1;
	CPU_INT16U unused14:1;
	CPU_INT16U unused15:1;
}t_GLOBAL1_BITS;

typedef union
{
	CPU_INT16U all;
	t_GLOBAL1_BITS bit;
} t_FR_GLOBAL1;

typedef struct
{
	t_FR_GLOBAL1 global_1;
}t_FAILURE_REG;

/****************************************************************************
*	Main Parameter Structure
****************************************************************************/
typedef struct
{
    t_GENERAL_INFO Info;
    t_ANALOG_VALUES Analog_Values;
    t_MOTOR_COMMAND LeftMotorCommand;
    t_MOTOR_COMMAND RightMotorCommand;
    t_COMMAND_REG CommandReg;
    t_STATUS_REG StatusReg;
    t_FAILURE_REG FailureReg;
    t_PROTECTION_CONF ProtectionConf;
    t_MOTOR_COMMAND XMotorCommand;
    t_MOTOR_COMMAND YMotorCommand;
} t_Param;

/****************************************************************************
* Parameter Index Enumeration
* This enumeration is used to index the parameters defined in ParamMap[]
****************************************************************************/
enum e_Params
{
    e_Info,
    e_Analog_Values,
    e_LeftMotorCommand,
    e_RightMotorCommand,
    e_CommandReg,
    e_StatusReg,
    e_FailureReg,
	e_PConfIRDistanceDetect,
	e_PConfVoltageBatteryDetect,
	e_PConfVoltage12VDetect,
	e_PConfCPUTemperatureDetect,
	e_PConfAuxTemperatureDetect,
    e_NumberOfParam
};






typedef struct s_paramblock
{

    CPU_INT16U  id;           /* Parameter identification number            */
    CPU_VOID*   pValue;      /* Pointer to parameter value(s) in table 1.  */
    CPU_INT08U  psize;        /* Parameter size in bytes                    */
    CPU_INT08U  flags;        /* Security and storage flags                 */
} t_paramblock;


extern const    t_paramblock*   ParamMap[];
extern          t_Param         Params;

CPU_VOID    Init_Params();
CPU_INT08U* GetPointerFromParamID(CPU_INT16U paramID);
CPU_VOID    SetValueFromParamID(CPU_INT16U paramID, const CPU_INT08U* paramValues);
CPU_INT16U  GetSizeFromParamID(CPU_INT16U paramID);
#endif
