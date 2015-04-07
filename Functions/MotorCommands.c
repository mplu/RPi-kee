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
 *	By reseting command and aborting ongoing rotation (valable when droven by stepper)
 ***********************************************/
CPU_VOID StepperMotorFullStop()
{
	sem_post(&sem_XMotorEmergencyStop);
	sem_post(&sem_YMotorEmergencyStop);
}

/********************************************//**
 * \brief Full stop the motor
 *
 * \return CPU_VOID
 *
 * By reseting command
 ***********************************************/
CPU_VOID DCMotorFullStop()
{
    Params.CommandReg.MoveDuration = 0;
	Params.LeftMotorCommand.Unused = 0;
	Params.LeftMotorCommand.Speed = 0;
	Params.RightMotorCommand.Unused = 0;
	Params.RightMotorCommand.Speed = 0;
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
	t_MOTOR_COMMAND right ={0};
	t_MOTOR_COMMAND left ={0};

    CPU_INT16S Forward = 1;
    CPU_INT16S Backward = -1;
    CPU_INT16S Sense = 0;
	CPU_INT16S Speed_min = 70;
	//CPU_INT16S Speed_nom = 2 * Speed_min;
	CPU_FP32 _ratio = 1;

    CPU_INT16S direction = p_inputCommands->MoveDirection % 360;

    if((direction > -360)&&(direction <= -270))
    {
        direction = direction + 360;
        //forward
        Sense = Forward;

    }else if((direction > -270)&&(direction < -90))
    {
        direction = direction + 180;
        //backward
        Sense = Backward;

    }else if((direction > -90)&&(direction < 90))
    {
        //forward
        Sense = Forward;
    }else if((direction > 90)&&(direction <= 270))
    {
        direction = direction - 180;
        //backward
        Sense = Backward;
    }else if((direction > 270)&&(direction < 360))
    {
        direction = direction - 360;
        //forward
        Sense = Forward;
    }else
    {
        // not possible
        Sense = Forward;
    }

    _ratio = (CPU_FP32)1 + (CPU_FP32)abs(direction) / (CPU_FP32)30;

    if(direction == 90)
    {
        right.Speed = Speed_min * Sense;
        left.Speed = (-Speed_min) * Sense;
    }else if (direction == -90)
    {
        right.Speed = (-Speed_min)*Sense;
        left.Speed = (Speed_min)*Sense;
    }else
    {

        if(direction>=0)
        {
            left.Speed = (Speed_min ) * Sense;
            right.Speed = ((CPU_FP32)Speed_min * _ratio )* (CPU_FP32)Sense;

        }else if(direction<0)
        {
            right.Speed = (Speed_min ) * Sense;
            left.Speed = ((CPU_FP32)Speed_min * _ratio )* Sense;
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


