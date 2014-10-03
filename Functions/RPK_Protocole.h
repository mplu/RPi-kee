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

#define MAX_RPK_DATA    100

typedef struct s_rpk_header
{
    CPU_INT16S handle;
    CPU_INT16S version;
    CPU_INT16S command;
    CPU_INT16S subcommand;
    CPU_INT16S packet_id;
    CPU_INT16S packet_size;

}t_rpk_header;

typedef struct s_rpk_frame_wo_cksm
{
    t_rpk_header header;
    CPU_INT08S data[MAX_RPK_DATA];
}t_rpk_frame_wo_cksm;

typedef struct s_rpk_frame
{
    union
    {
        CPU_INT08U raw[sizeof(t_rpk_frame_wo_cksm)];
        t_rpk_frame_wo_cksm f;
    }u;
    CPU_INT16S checksum;

}s_rpk_frame;







#endif
