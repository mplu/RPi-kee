#! /bin/bash
rm RPi-kee
gcc main.c Parameters.c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c global_var.c Threads/th_Alarm.c Threads/th_Compteur.c Threads/th_CtrlCmd.c Threads/th_ImgAcq.c Threads/th_ImgHandle.c Threads/th_MotorRightdrive.c Threads/th_MotorLeftdrive.c Threads/th_SensorAcq.c Threads/th_SensorIRHandle.c Threads/th_SensorOtherHandle.c Threads/th_TCPCom.c -o RPi-kee -lwiringPi -lpthread -lm -DRPi
