#! /bin/bash
rm RPi-kee_gcc4.8
#gcc main.c global_var.c Parameters.c Functions/functions.c Functions/MotorCommands.c Functions/RPK_Protocol.c Threads/th_ADC_Acq.c Threads/th_ADC_Data_Handle.c Threads/th_CtrlCmd.c Threads/th_debug.c Threads/th_ImgAcq.c Threads/th_ImgHandle.c Threads/th_MotorLeftdrive.c Threads/th_MotorRightdrive.c Threads/th_MotorXSurvey.c Threads/th_MotorYSurvey.c Threads/th_OtherSensorHandle.c Threads/th_Protections.c Threads/th_TCPCom.c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c driver/StepperMotor.c driver/DCMotor.c driver/ADC.c driver/IR_100_550.c driver/IR_20_150.c driver/IR_Common.c -o RPi-kee -lwiringPi -lpigpio -lpthread -lrt -lm -DRPi -Wall -O3 -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16
gcc-4.8 main.c global_var.c Parameters.c Functions/functions.c Functions/MotorCommands.c Functions/RPK_Protocol.c Threads/th_ADC_Acq.c Threads/th_ADC_Data_Handle.c Threads/th_CtrlCmd.c Threads/th_debug.c Threads/th_ImgAcq.c Threads/th_ImgHandle.c Threads/th_MotorLeftdrive.c Threads/th_MotorRightdrive.c Threads/th_MotorXSurvey.c Threads/th_MotorYSurvey.c Threads/th_OtherSensorHandle.c Threads/th_Protections.c Threads/th_TCPCom.c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c driver/StepperMotor.c driver/DCMotor.c driver/ADC.c driver/IR_100_550.c driver/IR_20_150.c driver/IR_Common.c -o RPi-kee_gcc4.8 -lwiringPi -lpigpio -lpthread -lrt -lm -DRPi -Wall -O3 -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard