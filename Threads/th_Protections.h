/****************************************************************/
/* Thread : System Protection and failure detection             */
/* Description :                                                */
/*                                                              */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

#ifndef __TH_PROTECTION_H
#define __TH_PROTECTION_H

#define UNDER 					-1
#define OVER 					1

typedef enum {
		fa_Off=0,
		fa_On,
		fa_Maintened,
		fa_FailureResult_size} te_FailureResult;

void* threadProtections (void* arg);
te_FailureResult triggered_window(CPU_INT16S value
                                ,CPU_INT08U * status
                                ,CPU_INT16U * time
                                ,CPU_INT16U * occurence
                                ,CPU_INT16S value_threshold
                                ,CPU_INT16U occ_treshold
                                ,CPU_INT16U time_threshold
                                ,CPU_INT08S comp
                                ,CPU_INT16U failurereg_prec);

CPU_BOOLEAN IRDistanceDetection();
CPU_BOOLEAN VoltageBatteryDetection();
CPU_BOOLEAN MotorBatteryDetection();
CPU_BOOLEAN CPUTemperatureDetection();

#endif
