/****************************************************************/
/* Light Library for Image ProcesS                              */
/* File : llips_constrastdetect.h                               */
/* Description :                                                */
/*   About contrast and edge detection on image                 */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

/****************************************************************/
/**           Define                                            */
/****************************************************************/
#define HOR                 0x0001
#define VER                 0x0002
#define DIAG                0x0004

/****************************************************************/
/**           Global variables                                  */
/****************************************************************/

/****************************************************************/
/**           Prototypes                                        */
/****************************************************************/
CPU_CHAR search_contrast(CPU_CHAR tolerance, t_img * img_in1,t_img * img_out,CPU_INT32U RGB, CPU_INT32U color,CPU_CHAR direction);
