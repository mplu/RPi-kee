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
	CPU_INT16S Steps;
	CPU_INT16U Delay;
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
}t_ANALOG_VALUES;

typedef struct
{
	CPU_INT08U Manual;
	CPU_INT08U Auto;
	CPU_INT16S MoveDirection;
	CPU_INT08U MoveDuration;
	CPU_INT08U UDPLiveFeed;
	CPU_INT08U MotorPSEnable;
}t_COMMAND_REG;

typedef struct
{
	CPU_INT08U Manual;
	CPU_INT08U Auto;
	CPU_INT08U MoveDirection;
	CPU_INT08U MoveDuration;
	CPU_INT08U UDPLiveFeed;
	CPU_INT08U MotorPSEnable;
}t_STATUS_REG;

typedef struct
{
	CPU_INT16S DetectionThreshold;
	CPU_INT16U CompDirection;
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
	unsigned short unused0:1;
	unsigned short unused1:1;
	unsigned short unused2:1;
	unsigned short unused3:1;
	unsigned short unused4:1;
	unsigned short unused5:1;
	unsigned short unused6:1;
	unsigned short unused7:1;
	unsigned short unused8:1;
	unsigned short unused9:1;
	unsigned short unused10:1;
	unsigned short unused11:1;
	unsigned short unused12:1;
	unsigned short unused13:1;
	unsigned short unused14:1;
	unsigned short unused15:1;
}t_GLOBAL1_BITS;

typedef union
{
	unsigned short all;
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
    e_ProtectionConf,
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
CPU_INT16U* GetPointerFromParamID(CPU_INT16U paramID);
CPU_VOID    SetValueFromParamID(CPU_INT16U paramID, const CPU_INT16U* paramValues);
CPU_INT16U  GetSizeFromParamID(CPU_INT16U paramID);
#endif
