#! /bin/bash
rm RPi-kee
#gcc main.c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c -o RPi-kee -lwiringPi -lpthread -RPi

#gcc -c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c -o llips.o -lwiringPi -lpthread -lm -DRPi
#gcc -c global_var.c Threads/th_Alarm.c Threads/th_Compteur.c Threads/th_CtrlCmd.c Threads/th_ImgAcq.c Threads/th_ImgHandle.c Threads/th_Motordrive.c Threads/th_SensorAcq.c Threads/th_SensorIRHandle.c Threads/th_SensorOtherHandle.c Threads/th_TCPCom.c -o threads.o -lwiringPi -lpthread -DRPi
gcc main.c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c global_var.c Threads/th_Alarm.c Threads/th_Compteur.c Threads/th_CtrlCmd.c Threads/th_ImgAcq.c Threads/th_ImgHandle.c Threads/th_Motordrive.c Threads/th_SensorAcq.c Threads/th_SensorIRHandle.c Threads/th_SensorOtherHandle.c Threads/th_TCPCom.c -o RPi-kee -lwiringPi -lpthread -lm -DRPi
