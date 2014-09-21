/* **************************************************************/
/* MotorCommands                                                */
/* File : MotorCommands.h                                       */
/* Description :                                                */
/*   Functions for high level motor handling					*/
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/* **************************************************************/

/* Macro ***/

/* Prototypes ***/

CPU_VOID MotorInputCommand(t_COMMAND_REG * p_inputCommands,t_MOTOR_COMMAND * p_lmotor,t_MOTOR_COMMAND * p_rmotor);
CPU_VOID MotorFullStop();
