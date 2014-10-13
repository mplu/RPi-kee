/* **************************************************************/
/* RPi-kee Communication Protocol Definition                    */
/* Description :                                                */
/*                                                              */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/* **************************************************************/
#include "../includes.h"

s_rpk_frame g_rpkframe_in;
s_rpk_frame g_rpkframe_out;


/********************************************//**
 * \brief Transform an incoming buffer into formated frame
 *
 * \param buffer CPU_INT08U* - buffer to process
 * \param buffer_size CPU_INT16U - size of the buffer
 * \param p_frame_in s_rpk_frame* - formated frame
 * \return e_RPK_Error  - error
 *
 ***********************************************/
e_RPK_Error RPK_Frame_Manage(CPU_INT08U * buffer,CPU_INT16U buffer_size,s_rpk_frame * p_frame_in)
{
    e_RPK_Error ret = rpkerr_NoError;
    CPU_INT16U i,framelength,calc_crc;

    // Check frame size (size of header + size of checksum)
    if(buffer_size < (sizeof(t_rpk_header)+sizeof(CPU_INT16U)))
    {
        ret = rpkerr_ErrTooShort;
    }else
    {
        for(i=0;i<sizeof(t_rpk_header);i++)
        {
            p_frame_in->u.raw[i] = buffer[i];
        }

        // Check Handle
        if(p_frame_in->u.f.header.handle != RPK_RASPBERRY_PI_HANDLE)
        {
            ret = rpkerr_ErrHandle;
        }else
        {
            // Check Version
            if(p_frame_in->u.f.header.version != RPK_VERSION)
            {
                ret = rpkerr_ErrHandle;
            }else
            {
                // Check frame length
                framelength = p_frame_in->u.f.header.length ;
                if(framelength > sizeof(s_rpk_frame))
                {
                    // if frame is too big, maybe length is written inverted
                    framelength = Word_Inversion(framelength);
                }

                // recheck with inverted word
                if(framelength > sizeof(s_rpk_frame))
                {
                    ret = rpkerr_ErrTooLong;
                }else
                {
                    // check frame length compared to received length
                    if(framelength != buffer_size)
                    {
                        ret = rpkerr_ErrLenCoherence;
                    }else
                    {
                        // calcultate checksum
                        calc_crc = CalculCRC(buffer, framelength - sizeof(CPU_INT16U));
                        p_frame_in->checksum = buffer[framelength - 2] << 8 | buffer[framelength - 1];

                        // verify checksum
                        if(calc_crc != p_frame_in->checksum)
                        {
                            ret = rpkerr_ErrChecksum;
                        }else
                        {
                            // everything ok, copy the rest of the data
                            for(i=sizeof(t_rpk_header);i<framelength - sizeof(CPU_INT16U);i++)
                            {
                                p_frame_in->u.raw[i] = buffer[i];
                            }
                        }
                    }

                }
            }
        }


    }



    return ret;
}

/********************************************//**
 * \brief Process formated frame
 *
 * \param p_frame_in s_rpk_frame* - input frame to process
 * \param p_frame_out s_rpk_frame* - answer to send if no error detected
 * \return e_RPK_Error error
 *
 ***********************************************/
e_RPK_Error RPK_Frame_Process(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out)
{
    e_RPK_Error err = rpkerr_NoError;

    switch (p_frame_in->u.f.header.command)
    {
        case RPK_C_READ:
            err = RPK_Read(p_frame_in,p_frame_out);
            break;
        case RPK_C_WRITE:
            err = RPK_Write(p_frame_in,p_frame_out);
            break;
        case RPK_C_DUMMY:
            err = RPK_Dummy(p_frame_in,p_frame_out);
            break;
        default:
            err = rpkerr_ErrNonSupportedFunction;
            break;
    }

    return err;
}

/********************************************//**
 * \brief Access memory and fill output frame with requested data
 *
 * \param p_frame_in s_rpk_frame* - input frame to process
 * \param p_frame_out s_rpk_frame* - answer to send if no error detected
 * \return e_RPK_Error - error
 *
 ***********************************************/
e_RPK_Error RPK_Read(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out)
{
    e_RPK_Error err = rpkerr_NoError;
    CPU_INT16U paramsize,i;
    CPU_INT08U* p_data;

    // check size and existance of paramID
    paramsize = GetSizeFromParamID(p_frame_in->u.f.header.option1);
    if(paramsize <= 0)
    {
        err = rpkerr_ErrUnknownParamID;
        p_frame_out->u.f.header.subcommand = RPK_SC_ERROR;
        p_frame_out->u.f.header.option1 = err;

    }else
    {
        if(p_frame_in->u.f.header.option2 != paramsize)
        {
            err = rpkerr_ErrWrongParamIDSize;

        }else
        {
            p_data = GetPointerFromParamID(p_frame_in->u.f.header.option1);
            for(i=0;i<paramsize;i++)
            {
                p_frame_out->u.f.data[i]= p_data[i];
            }

        }

    }

    if(err != rpkerr_NoError)
    {
        p_frame_out->u.f.header.length = HEADER_SIZE;
        p_frame_out->u.f.header.subcommand = RPK_SC_ERROR;
        p_frame_out->u.f.header.option1 = err;
        p_frame_out->u.f.header.option2 = 0;
    }else
    {
        p_frame_out->u.f.header.length = HEADER_SIZE + paramsize;
        p_frame_out->u.f.header.subcommand = RPK_SC_REPLY;
        p_frame_out->u.f.header.option1 = p_frame_in->u.f.header.option1;
        p_frame_out->u.f.header.option2 = p_frame_in->u.f.header.option2;
    }
    p_frame_out->u.f.header.handle = p_frame_in->u.f.header.handle;
    p_frame_out->u.f.header.version = p_frame_in->u.f.header.version;
    p_frame_out->u.f.header.command = p_frame_in->u.f.header.command;

    p_frame_out->checksum  = CalculCRC(p_frame_out->u.raw, p_frame_out->u.f.header.length - sizeof(CPU_INT16U));



    return err;
}

/********************************************//**
 * \brief Access memory and fill memory with input frame data
 *
 * \param p_frame_in s_rpk_frame* - input frame to process
 * \param p_frame_out s_rpk_frame* - answer to send if no error detected
 * \return e_RPK_Error - error
 *
 ***********************************************/
e_RPK_Error RPK_Write(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out)
{
    e_RPK_Error err = rpkerr_NoError;
    CPU_INT16U paramsize;

    // check size and existance of paramID
    paramsize = GetSizeFromParamID(p_frame_in->u.f.header.option1);
    if(paramsize <= 0)
    {
        err = rpkerr_ErrUnknownParamID;
        p_frame_out->u.f.header.subcommand = RPK_SC_ERROR;
        p_frame_out->u.f.header.option1 = err;

    }else
    {
        if(p_frame_in->u.f.header.option2 != paramsize)
        {
            err = rpkerr_ErrWrongParamIDSize;

        }else
        {
            SetValueFromParamID(p_frame_in->u.f.header.option1,(const unsigned char *)p_frame_in->u.f.data);
        }

    }

    if(err != rpkerr_NoError)
    {
        p_frame_out->u.f.header.length = HEADER_SIZE;
        p_frame_out->u.f.header.subcommand = RPK_SC_ERROR;
        p_frame_out->u.f.header.option1 = err;
        p_frame_out->u.f.header.option2 = 0;
    }else
    {
        p_frame_out->u.f.header.length = HEADER_SIZE ;
        p_frame_out->u.f.header.subcommand = RPK_SC_REPLY;
        p_frame_out->u.f.header.option1 = p_frame_in->u.f.header.option1;
        p_frame_out->u.f.header.option2 = p_frame_in->u.f.header.option2;
    }
    p_frame_out->u.f.header.handle = p_frame_in->u.f.header.handle;
    p_frame_out->u.f.header.version = p_frame_in->u.f.header.version;
    p_frame_out->u.f.header.command = p_frame_in->u.f.header.command;

    p_frame_out->checksum  = CalculCRC(p_frame_out->u.raw, p_frame_out->u.f.header.length - sizeof(CPU_INT16U));



    return err;
}

/********************************************//**
 * \brief Just answer an empty request
 *
 * \param p_frame_in s_rpk_frame* - input frame to process
 * \param p_frame_out s_rpk_frame* - answer to send if no error detected
 * \return e_RPK_Error - error
 *
 ***********************************************/
e_RPK_Error RPK_Dummy(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out)
{
    e_RPK_Error err = rpkerr_NoError;

    p_frame_out->u.f.header.length = HEADER_SIZE ;
    p_frame_out->u.f.header.subcommand = RPK_SC_REPLY;
    p_frame_out->u.f.header.option1 = p_frame_in->u.f.header.option1;
    p_frame_out->u.f.header.option2 = p_frame_in->u.f.header.option2;

    p_frame_out->u.f.header.handle = p_frame_in->u.f.header.handle;
    p_frame_out->u.f.header.version = p_frame_in->u.f.header.version;
    p_frame_out->u.f.header.command = p_frame_in->u.f.header.command;

    p_frame_out->checksum  = CalculCRC(p_frame_out->u.raw, p_frame_out->u.f.header.length - sizeof(CPU_INT16U));

    return err;
}

/********************************************//**
 * \brief Convert formatted frame into raw ouput buffer
 *
 * \param p_frame_out s_rpk_frame* - frame to send
 * \param buffer CPU_INT08U* - raw buffer
 * \return CPU_INT16U - size of the buffer
 *
 ***********************************************/
CPU_INT16U RPK_SendPrepare(s_rpk_frame * p_frame_out,CPU_INT08U * buffer)
{
    CPU_INT16U sizetosend = 0,i;

    // everything ok, copy the rest of the data
    for(i=0;i< p_frame_out->u.f.header.length - sizeof(CPU_INT16U);i++)
    {
        buffer[i] = p_frame_out->u.raw[i];
    }
    buffer[p_frame_out->u.f.header.length - 2] = p_frame_out->checksum & 0xFF;
    buffer[p_frame_out->u.f.header.length - 1] = (p_frame_out->checksum >> 8)& 0xFF;

    sizetosend = p_frame_out->u.f.header.length;
    return sizetosend;
}
