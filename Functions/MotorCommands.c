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
CPU_VOID MotorEmergencyFullStop()
{
    Params.CommandReg.MoveDuration = 0;
	Params.LeftMotorCommand.Delay = 0;
	Params.LeftMotorCommand.Steps = 0;
	Params.RightMotorCommand.Delay = 0;
	Params.RightMotorCommand.Steps = 0;
	sem_post(&sem_LeftMotorEmergencyStop);
	sem_post(&sem_RightMotorEmergencyStop);
}

/********************************************//**
 * \brief Full stop the motor
 *
 * \return CPU_VOID
 *
 * By reseting command
 ***********************************************/
CPU_VOID MotorFullStop()
{
    Params.CommandReg.MoveDuration = 0;
	Params.LeftMotorCommand.Delay = 0;
	Params.LeftMotorCommand.Steps = 0;
	Params.RightMotorCommand.Delay = 0;
	Params.RightMotorCommand.Steps = 0;
}

/********************************************//**
 * \brief Convert global direction command to motor order, for half second movement
 *
 * \param p_inputCommands : input pointer to command register
 * \param p_lmotor : output pointer to left individual command
 * \param p_rmotor : output pointer to right individual command
 * \return none
 *
 * Do stuff
 ***********************************************/
CPU_VOID MotorInputCommand(t_COMMAND_REG * p_inputCommands,t_MOTOR_COMMAND * p_lmotor,t_MOTOR_COMMAND * p_rmotor)
{
	t_MOTOR_COMMAND right,left;
	CPU_FP32 _ratio ;

	CPU_INT16S steps;

    CPU_INT16S direction = p_inputCommands->MoveDirection % 360;

    if((direction > -360)&&(direction <= -270))
    {
        direction = direction + 360;
        steps = 32;
    }else if((direction > -270)&&(direction < -90))
    {
        direction = direction + 180;
        steps = -32;
    }else if((direction > -90)&&(direction < 90))
    {
        steps = 32;
    }else if((direction > 90)&&(direction <= 270))
    {
        direction = direction - 180;
        steps = -32;
    }else if((direction > 270)&&(direction < 360))
    {
        direction = direction - 360;
        steps = 32;
    }else
    {
        // not possible
    }


    if(direction == 90)
    {
            left.Delay = 4;
            left.Steps = -32;

            right.Delay = 4;
            right.Steps = 32;
    }else if (direction == -90)
    {
            left.Delay = 4;
            left.Steps = 32;

            right.Delay = 4;
            right.Steps = -32;
    }else
    {
        _ratio = angleTOratio((CPU_FP32)direction  );
        if(_ratio <= 1)
        {
            left.Delay = 4;
            left.Steps = steps;

            right.Delay = (CPU_FP32)((CPU_FP32)left.Delay/_ratio);
            right.Steps = left.Delay * left.Steps /((CPU_FP32)left.Delay/_ratio);

        }else if(_ratio > 1)
        {
            right.Delay = 4;
            right.Steps = steps;
            _ratio = 1/_ratio;

            left.Delay = (CPU_FP32)((CPU_FP32)right.Delay/_ratio);
            left.Steps = right.Delay * right.Steps /((CPU_FP32)right.Delay/_ratio);
        }
    }



    *p_lmotor = left;
    *p_rmotor = right;

}

/********************************************//**
 * \brief Convert motor ratio in angle
 *
 * \param _ratio CPU_FP32 input motor ratio command
 * \return CPU_FP32 corresponding angle
 *
 ***********************************************/
CPU_FP32 ratioTOangle(CPU_FP32 _ratio)
{
    CPU_FP32 angle;
    //y = -0,181x3 + 1,2037x2 - 3,1392x + 2,11
    angle = 2.11 - (_ratio * _ratio * _ratio * 0.181) + (_ratio * _ratio * 1.2037) - 3.1392 * _ratio;
    return angle *180.0/PI;
}

/********************************************//**
 * \brief Convert angle in motor ratio
 *
 * \param angle CPU_FP32  input angle direction
 * \return CPU_FP32 corresponding motor ratio command
 *
 ***********************************************/
CPU_FP32 angleTOratio(CPU_FP32 angle)
{
    CPU_FP32 _ratio;
    angle = angle * PI / 180.0;
    //y = -0,2002x3 + 0,4262x2 - 0,7923x + 0,9817
    _ratio = 0.9817 - (0.2002 * angle * angle * angle ) + (0.4262 * angle * angle) - 0.7923 * angle;

    return _ratio;
}
