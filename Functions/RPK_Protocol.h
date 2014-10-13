/* **************************************************************/
/* RPi-kee Communication Protocol Definition                    */
/* Description :                                                */
/*                                                              */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/* **************************************************************/

#ifndef __RPK_PROTOCOL_H
#define __RPK_PROTOCOL_H

#define RPK_MAX_DATA            100
#define RPK_RASPBERRY_PI_HANDLE 115
#define RPK_VERSION             1
#define HEADER_SIZE             16
#define HEADER_SIZE_wo_CKSM     14

#define RPK_C_READ              1
#define RPK_C_WRITE             2
#define RPK_C_DUMMY             3

#define RPK_SC_REQUEST          1
#define RPK_SC_REPLY            2
#define RPK_SC_ERROR            0xFF


// Error Management
typedef enum e_RPK_Err
{
    rpkerr_NoError,
    rpkerr_ErrTooShort,
    rpkerr_ErrTooLong,
    rpkerr_ErrHandle,
    rpkerr_ErrVersion,
    rpkerr_ErrLenCoherence,
    rpkerr_ErrChecksum,
    rpkerr_ErrNonSupportedFunction,
    rpkerr_ErrUnknownParamID,
    rpkerr_ErrWrongParamIDSize,
    e_RPK_Error_size
}e_RPK_Error;

typedef struct s_rpk_header
{
    CPU_INT16S handle;
    CPU_INT16S version;
    CPU_INT16S length;
    CPU_INT16S command;
    CPU_INT16S subcommand;
    CPU_INT16S option1;
    CPU_INT16S option2;

}t_rpk_header;

typedef struct s_rpk_frame_wo_cksm
{
    t_rpk_header header;
    CPU_INT08S data[RPK_MAX_DATA];
}t_rpk_frame_wo_cksm;

typedef struct s_rpk_frame
{
    union
    {
        CPU_INT08U raw[sizeof(t_rpk_frame_wo_cksm)];
        t_rpk_frame_wo_cksm f;
    }u;
    CPU_INT16U checksum;

}s_rpk_frame;


extern s_rpk_frame g_rpkframe_in;
extern s_rpk_frame g_rpkframe_out;

e_RPK_Error RPK_Frame_Manage(CPU_INT08U * buffer,CPU_INT16U buffer_size,s_rpk_frame * p_frame_in);
e_RPK_Error RPK_Frame_Process(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out);
e_RPK_Error RPK_Read(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out);
e_RPK_Error RPK_Write(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out);
e_RPK_Error RPK_Dummy(s_rpk_frame * p_frame_in,s_rpk_frame * p_frame_out);
CPU_INT16U RPK_SendPrepare(s_rpk_frame * p_frame_out,CPU_INT08U * buffer);


#endif
