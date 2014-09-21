/* **************************************************************/
/* MotorCommands                                                */
/* File : MotorCommands.c                                       */
/* Description :                                                */
/*   Functions for high level motor handling					*/
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/* **************************************************************/

#include "../includes.h"

/********************************************//**
 * \brief Full stop the motor
 *
 *
 *
 * \return none
 *
 *	By reseting command and aborting ongoing rotation
 ***********************************************/
CPU_VOID MotorFullStop()
{
	Params.LeftMotorCommand.Delay = 0;
	Params.LeftMotorCommand.Steps = 0;
	Params.RightMotorCommand.Delay = 0;
	Params.RightMotorCommand.Steps = 0;
	sem_post(&sem_LeftMotorEmergencyStop);
	sem_post(&sem_RightMotorEmergencyStop);
}

/********************************************//**
 * \brief Convert global direction command to motor order
 *
 * \param p_inputCommands : input pointer to command register
 * \param p_lmotor/p_rmotor : output pointer to individual command
 *
 * \return none
 *
 * Do stuff
 ***********************************************/

CPU_VOID MotorInputCommand(t_COMMAND_REG * p_inputCommands,t_MOTOR_COMMAND * p_lmotor,t_MOTOR_COMMAND * p_rmotor)
{
	CPU_INT16S Direction = 	p_inputCommands->MoveDirection;
	CPU_INT08U Duration = 	p_inputCommands->MoveDuration;
	t_MOTOR_COMMAND right,left;
	Direction = Direction % 360;
	if(Direction < 180)
	{
		//right.Delay =
		//left.Delay = // plus petit >> moins de delai donc tourne plus vite
	}


}
