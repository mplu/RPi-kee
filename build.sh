#! /bin/bash
rm RPi-kee
gcc main.c global_var.c Parameters.c Functions/functions.c Threads/th_ADC_Acq.c Threads/th_ADC_Data_Handle.c Threads/th_CtrlCmd.c Threads/th_debug.c Threads/th_ImgAcq.c Threads/th_ImgHandle.c Threads/th_MotorLeftdrive.c Threads/th_MotorRightdrive.c Threads/th_OtherSensorHandle.c Threads/th_Protections.c Threads/th_TCPCom.c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c driver/Motor.c driver/ADC.c driver/IR_100_550.c driver/IR_20_150.c -o RPi-kee -lwiringPi -lpthread -lm -DRPi
