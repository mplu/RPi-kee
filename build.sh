#! /bin/bash
rm RPi-kee
gcc main.c llips/llips_contrastdetect.c llips/llips_functions.c llips/llips_general.c llips/llips_io.c llips/llips_motiondetect.c -o RPi-kee -lwiringPi -lpthread -lm -DLinux
