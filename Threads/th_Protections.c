#include "../includes.h"


void* threadProtections (void* arg)
{
    while(1) /* Boucle infinie */
    {
        m_msSleep(10);

        IRDistanceDetection();
        IRDistanceDetection();
        VoltageBatteryDetection();
        MotorBatteryDetection();
        CPUTemperatureDetection();

    }

    pthread_exit(NULL); /* Fin du thread */
}



te_FailureResult triggered_window(CPU_INT16S value
                                ,CPU_INT08U * status
                                ,CPU_INT16U * time
                                ,CPU_INT16U * occurence
                                ,CPU_INT16S value_threshold
                                ,CPU_INT16U occ_treshold
                                ,CPU_INT16U time_threshold
                                ,CPU_INT08S comp
                                ,CPU_INT16U failurereg_prec)
{
    te_FailureResult ret = fa_Maintened ;
    if (failurereg_prec == 1)
    {
        *status = 1;
    }

    if (comp == OVER)
    {
        if(value > value_threshold)
        {
            *status = 1;
            *occurence =  (*occurence + 1);
        }
    }
    else
    {
        if(value < value_threshold)
        {
            *status = 1;
            *occurence = (*occurence + 1);
        }
    }

    if (*status == 1)
    {
        *time = (CPU_INT16U)(*time +1);
    }

    if (*occurence >= (occ_treshold))
    {
        *status = 0;
        *time = 0;
        *occurence = 0;
        ret = fa_On;
    }
    else if (*time > time_threshold)
    {
        *status = 0;
        *time = 0;
        *occurence = 0;
        ret = fa_Off;
    }

    return ret;
}


CPU_BOOLEAN IRDistanceDetection()
{
	static CPU_INT08U status_alr=0;
	static CPU_INT16U timer_alr=0;
	static CPU_INT16U occurence_alr=0;

	te_FailureResult result;

	CPU_INT16S value;
	CPU_INT08U * status;
	CPU_INT16U * time;
	CPU_INT16U * occurence;
	CPU_INT16U value_threshold;
	CPU_INT16U occ_treshold;
	CPU_INT16U time_threshold;
	CPU_INT08S comp;
	CPU_INT16U failurereg = 0;

	value 			= Params.Analog_Values.ShortIRDistance;
	status 			= &status_alr;
	time 			= &timer_alr;
	occurence 		= &occurence_alr;
	value_threshold = Params.ProtectionConf.IRDistanceDetect.DetectionThreshold;
	occ_treshold 	= Params.ProtectionConf.IRDistanceDetect.ConfThreshold;
	time_threshold 	= Params.ProtectionConf.IRDistanceDetect.TimeWindow;
	comp 			= Params.ProtectionConf.IRDistanceDetect.CompDirection;
	failurereg 		= Params.FailureReg.global_1.bit.IRDistance;

	result = triggered_window(value,status,time,occurence,value_threshold,occ_treshold,time_threshold,comp,failurereg);
	if ( result == fa_On )
	{
		failurereg = TRUE;
	}else if ( result == fa_Off )
	{
		failurereg = FALSE;
	}else
	{
		//nothing
	}
	Params.FailureReg.global_1.bit.IRDistance = failurereg;

	return Params.FailureReg.global_1.bit.IRDistance;
}

CPU_BOOLEAN VoltageBatteryDetection()
{
	static CPU_INT08U status_alr=0;
	static CPU_INT16U timer_alr=0;
	static CPU_INT16U occurence_alr=0;

	te_FailureResult result;

	CPU_INT16S value;
	CPU_INT08U * status;
	CPU_INT16U * time;
	CPU_INT16U * occurence;
	CPU_INT16U value_threshold;
	CPU_INT16U occ_treshold;
	CPU_INT16U time_threshold;
	CPU_INT08S comp;
	CPU_INT16U failurereg = 0;

	value 			= Params.Analog_Values.VoltageBattery;
	status 			= &status_alr;
	time 			= &timer_alr;
	occurence 		= &occurence_alr;
	value_threshold = Params.ProtectionConf.VoltageBatteryDetect.DetectionThreshold;
	occ_treshold 	= Params.ProtectionConf.VoltageBatteryDetect.ConfThreshold;
	time_threshold 	= Params.ProtectionConf.VoltageBatteryDetect.TimeWindow;
	comp 			= Params.ProtectionConf.VoltageBatteryDetect.CompDirection;
	failurereg 		= Params.FailureReg.global_1.bit.BatteryVoltageLow;

	result = triggered_window(value,status,time,occurence,value_threshold,occ_treshold,time_threshold,comp,failurereg);
	if ( result == fa_On )
	{
		failurereg = TRUE;
	}else if ( result == fa_Off )
	{
		failurereg = FALSE;
	}else
	{
		//nothing
	}
	Params.FailureReg.global_1.bit.BatteryVoltageLow = failurereg;

	return Params.FailureReg.global_1.bit.BatteryVoltageLow;
}

CPU_BOOLEAN MotorBatteryDetection()
{
	static CPU_INT08U status_alr=0;
	static CPU_INT16U timer_alr=0;
	static CPU_INT16U occurence_alr=0;

	te_FailureResult result;

	CPU_INT16S value;
	CPU_INT08U * status;
	CPU_INT16U * time;
	CPU_INT16U * occurence;
	CPU_INT16U value_threshold;
	CPU_INT16U occ_treshold;
	CPU_INT16U time_threshold;
	CPU_INT08S comp;
	CPU_INT16U failurereg = 0;

	value 			= Params.Analog_Values.Voltage12V;
	status 			= &status_alr;
	time 			= &timer_alr;
	occurence 		= &occurence_alr;
	value_threshold = Params.ProtectionConf.Voltage12VDetect.DetectionThreshold;
	occ_treshold 	= Params.ProtectionConf.Voltage12VDetect.ConfThreshold;
	time_threshold 	= Params.ProtectionConf.Voltage12VDetect.TimeWindow;
	comp 			= Params.ProtectionConf.Voltage12VDetect.CompDirection;
	failurereg 		= Params.FailureReg.global_1.bit.MotorVoltageLow;

	result = triggered_window(value,status,time,occurence,value_threshold,occ_treshold,time_threshold,comp,failurereg);
	if ( result == fa_On )
	{
		failurereg = TRUE;
	}else if ( result == fa_Off )
	{
		failurereg = FALSE;
	}else
	{
		//nothing
	}
	Params.FailureReg.global_1.bit.MotorVoltageLow = failurereg;

	return Params.FailureReg.global_1.bit.MotorVoltageLow;
}

CPU_BOOLEAN CPUTemperatureDetection()
{
	static CPU_INT08U status_alr=0;
	static CPU_INT16U timer_alr=0;
	static CPU_INT16U occurence_alr=0;

	te_FailureResult result;

	CPU_INT16S value;
	CPU_INT08U * status;
	CPU_INT16U * time;
	CPU_INT16U * occurence;
	CPU_INT16U value_threshold;
	CPU_INT16U occ_treshold;
	CPU_INT16U time_threshold;
	CPU_INT08S comp;
	CPU_INT16U failurereg = 0;

	value 			= Params.Analog_Values.CPUTemperature;
	status 			= &status_alr;
	time 			= &timer_alr;
	occurence 		= &occurence_alr;
	value_threshold = Params.ProtectionConf.CPUTemperatureDetect.DetectionThreshold;
	occ_treshold 	= Params.ProtectionConf.CPUTemperatureDetect.ConfThreshold;
	time_threshold 	= Params.ProtectionConf.CPUTemperatureDetect.TimeWindow;
	comp 			= Params.ProtectionConf.CPUTemperatureDetect.CompDirection;
	failurereg 		= Params.FailureReg.global_1.bit.CPU_Temp_High;

	result = triggered_window(value,status,time,occurence,value_threshold,occ_treshold,time_threshold,comp,failurereg);
	if ( result == fa_On )
	{
		failurereg = TRUE;
	}else if ( result == fa_Off )
	{
		failurereg = FALSE;
	}else
	{
		//nothing
	}
	Params.FailureReg.global_1.bit.CPU_Temp_High = failurereg;

	return Params.FailureReg.global_1.bit.CPU_Temp_High;
}
