/* **************************************************************/
/* Functions                                                    */
/* File : functions.c                                           */
/* Description :                                                */
/*   Various functions                                          */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/* **************************************************************/

#include "../includes.h"

#if defined (RPi)
/********************************************//**
 * \brief Millisecon capable sleep function
 *
 * \param timeout_ms CPU_INT32U : timeout duration in millisecond
 * \return CPU_INT32S nothing
 *
 * RPi implemented only
 ***********************************************/
CPU_INT32S msSleepLinux( CPU_INT32U timeout_ms )
{
        struct timeval tv;
        tv.tv_sec = timeout_ms/1000;
        tv.tv_usec = (timeout_ms%1000) * 1000;
        select(0, NULL, NULL, NULL, &tv);
        return 0;
}
#endif

/********************************************//**
 * \brief Give a direction command calculated from angle and position of a line
 *
 * \param angle CPU_FP32 : angle of line line
 * \param x CPU_FP32 : position of the line on the upper half capture divided by img width
 * \return CPU_FP32 : ratio to apply on motors
 *
 * The ratio n returned considers that left motor should run n times faster than the right one
 ***********************************************/
CPU_FP32 CalculateMotorCommandFromLine(CPU_FP32 angle,CPU_FP32 x)
{
    CPU_FP32 n;
    n = (1.0 - ANGLE_COEF * angle)/(1.0 + ANGLE_COEF * angle) + x;
    return n;
}


/********************************************//**
 * \brief Calculate CRC16 on a given CPU_INT08U table
 *
 * \param ptrMessage CPU_INT08U* pointer to the table to process
 * \param NbMessage CPU_INT08U size of the table
 * \return CPU_INT16U calculated CRC value
 *
 ***********************************************/
CPU_INT16U CalculCRC(CPU_INT08U *ptrMessage, CPU_INT08U NbMessage)
{
    CPU_INT08U Calcul1, Calcul2 ;
    CPU_INT08U Decalage, Decal2 ;
    CPU_INT16U Calcul = 0xFFFF;
    CPU_INT08U j,i;

    for( j = 0 ; j < NbMessage; j++)
    {
        Calcul ^= *ptrMessage++  << 8;
        for (i = 0 ; i < 8; i++)
        {
            Decalage = 0;
            Decal2 = 0 ;
            if((Calcul & 0x0001) == 1)
            {
                Decalage = 1 ;
            }
            if((Calcul & 0x0100) != 0)
            {
                Decal2 = 1 ;
            }
            Calcul1 = (CPU_INT08U) Calcul;
            Calcul1 = (CPU_INT08U)(Calcul1 >>1) ;
            Calcul2 = (CPU_INT08U)(Calcul >> 8);
            Calcul2 = (CPU_INT08U)(Calcul2 >> 1) ;
            if(Decalage == 1 )
            {
                Calcul2 |= 0x80 ;
            }
            Calcul = (Calcul2 << 8) | Calcul1 ;
            if(Decal2 == 1)
            {
                Calcul ^= 0x01A0 ;
            }
        }
    }
    return(Calcul);
}
