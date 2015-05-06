#include "../includes.h"


void* threadImgHandle (void* arg)
{
	t_img img_in1,img_in2;
    t_img img_inter1;
    t_img img_out1,img_out2;
	CPU_FP64 ** filter0;
	CPU_INT32U number_of_loop = 0;
	clock_t start, finish;
	clock_t loop_start, loop_finish;
    double duration_loop=0,duration_process=0,duration_move=0,duration_io=0,duration_net=0;
    CPU_FP32 vx, vy;
    CPU_FP64 angle;
    CPU_FP64 av_angle = 0;
    CPU_INT16U av_angle_weight = 0;

    CPU_FP64 av_x = 0;
    CPU_INT16U av_x_weight = 0;

    CPU_INT16U number_of_segment_max = NUMBER_OF_SEGMENT;
    CPU_INT16U number_of_segment_found = 0;
    CPU_INT16U he_of_segement;
    CPU_INT16U margin = 5;
    CPU_INT16U i,j,index;
    CPU_CHAR Luminance = 0;
    CPU_INT08U maxvalue;
	CPU_INT08U enable_out_img = OUT_IMG_DBG;

	t_pixel tab_pixel[NUMBER_OF_SEGMENT];

	CPU_FP64 MotorCommandRatio = 0;
    t_simplearea area;
	init_img(&img_in1);
	init_img(&img_in2);
    init_img(&img_out1);
	init_img(&img_out2);
    init_img(&img_inter1);

	CPU_CHAR inputfilename[IMG_FILENAME_SIZE];
	CPU_CHAR outputfilename[IMG_FILENAME_SIZE];
	CPU_CHAR delele_img_cmd[IMG_FILENAME_SIZE + 10];
	CPU_CHAR temporary_cmd[100];
	CPU_CHAR * pch;

	filter0 = createTableFP64(GAUSS_SIZE,GAUSS_SIZE);
	create_gauss_filter(filter0,GAUSS_SIZE,SIGMA);

	//variable for motion detection and tracking
	CPU_CHAR Got_first_frame = FALSE,move_detected=FALSE;
	CPU_CHAR img_diff_1_2=0;
	t_area change_1_2;
	CPU_INT16S mouvementx = 0;
	CPU_INT16S mouvementx_threshold = 5;
	CPU_INT16S mouvementy = 0;
	CPU_INT16S mouvementy_threshold = 5;
	time_t ttt = 0;
	loop_start = clock();
	while(1) /* Boucle infinie */
    {
		loop_finish = clock();
		duration_loop = (double)(loop_finish - loop_start) / CLOCKS_PER_SEC;
		printf("Loop %.3f\t(process %.3f + move %.3f + io %.3f + net %.3f \n",duration_loop,duration_process,duration_move,duration_io,duration_net);
        sem_wait(&sem_Img_available); //waiting for new img to treat
		loop_start = clock();
	
        start = clock();

        if((Params.StatusReg.LineFollow == 1)&&(Params.StatusReg.Survey == 0))
        {
                 // Line Follow Mode
            if (load_img((CPU_CHAR *)g_nextIMGfilename, &img_in1) != ERR_NONE)
            {
                //printf("erreur ouverture\n");
            }else
            {
                // saving name
                sprintf((char *)inputfilename,"%s",g_nextIMGfilename);


                //looking for remarquable point
                he_of_segement = img_out1.he / (number_of_segment_max+1);

                //for each segment
                av_angle_weight = 0;
                av_x_weight = 0;
                av_x = 0;
                av_angle = 0;
                number_of_segment_found = 0;
                for(index = 0 ; index <= number_of_segment_max ; index++)
                {
                    i= (index + 1) * he_of_segement;

                    area.BotLeft.x = 0;
                    area.BotLeft.y = i;
                    area.TopRight.x = img_in1.wi;
                    area.TopRight.y = i+1;

                    apply_linfilter(&img_in1,filter0,GAUSS_SIZE,GREEN,&area,&img_inter1);
                    /*if(enable_out_img == TRUE)
                    {
                        sprintf((char *)outputfilename,"out__gauss_%s",inputfilename);
                        write_img(outputfilename,&img_inter1);
                    }*/

                    search_contrast(CONTRAST_TOLERANCE,&img_inter1,&area,&img_out1,SetRGB(255,255,255),GREEN,HOR);
                    /*if(enable_out_img == TRUE)
                    {
                        sprintf((char *)outputfilename,"out_contdetec_%s",inputfilename);
                        write_img(outputfilename,&img_out1);
                    }*/








                    tab_pixel[index].y = i;
                    tab_pixel[index].x = 0;
                    maxvalue = 0;
                    for(j=area.BotLeft.x+margin;j<(area.TopRight.x - margin);j++)
                    {

                        //calcultate luminance Y = 0,299 R + 0,587 G + 0,114 B
                        Luminance = (CPU_CHAR)(  (CPU_FP32)img_out1.Red[i][j]   * 0.299
                                                + (CPU_FP32)img_out1.Green[i][j] * 0.587
                                                + (CPU_FP32)img_out1.Blue[i][j]  * 0.114 );
                        if(maxi(maxvalue,Luminance) > maxvalue)
                        {
                            tab_pixel[index].x = j;
                        }


                    }
                    if((index >= 1)&&(tab_pixel[index-1].x!=0)&&(tab_pixel[index].x!=0))
                    {
                        highlight_line(&img_in1,tab_pixel[index-1],tab_pixel[index],SetRGB(0,255,0));
                        vy = tab_pixel[index].y - tab_pixel[index-1].y;
                        vx = tab_pixel[index].x - tab_pixel[index-1].x;
                        if(vx!=0)
                        {
                            angle=atan2(vy,vx);
                        }else
                        {
                            angle = PI / 2.0;
                        }
                        av_angle = (angle + (av_angle * av_angle_weight))/(CPU_FP64)(av_angle_weight + 1.0);
                        av_angle_weight ++;
                        if(index > number_of_segment_max/2)
                        {
                            av_x = ((tab_pixel[index].x + tab_pixel[index-1].x)/2.0   +  (av_x * av_x_weight)   ) / (CPU_FP64)(av_x_weight + 1.0);
                            av_x_weight ++ ;
                        }
                        number_of_segment_found ++;

                    }
                }

                // Normalize angle and position from vertical center of image
                if(av_angle>=0)
                {
                    av_angle = av_angle - PI/2.0 ;
                }else
                {
                    av_angle = PI/2.0 + av_angle;
                }
                av_x = av_x - img_out1.wi/2 ;

                MotorCommandRatio = CalculateMotorCommandFromLine(av_angle,(CPU_FP32)av_x/(CPU_FP32)img_out1.wi);
                if(av_angle_weight != 0)
                {
                    Params.Analog_Values.ImgMoveDirection = ratioTOangle(MotorCommandRatio) ;
                }else
                {
                    Params.Analog_Values.ImgMoveDirection = 32767;
                }
				
				if (enable_out_img == TRUE)
                {
                    sprintf((char *)outputfilename,"out%05lu_process_%s_%.2f_%.2f_%d.bmp",number_of_loop
                                                                                    ,inputfilename
                                                                                    ,av_angle
                                                                                    ,av_x
                                                                                    ,Params.Analog_Values.ImgMoveDirection);
                    write_img(outputfilename,&img_in1);
                }
                finish = clock();
                duration_process = (double)(finish - start) / CLOCKS_PER_SEC;
                printf("Img treated (in %.3f): direction %d, \n",duration_process,Params.Analog_Values.ImgMoveDirection);

                // suppress file
    #if defined (Win32)
                sprintf((char *)delele_img_cmd,"del %s",inputfilename);
    #elif defined (RPi)
                sprintf((char *)delele_img_cmd,"rm %s -rf",inputfilename);
    #endif
                system((const char *)delele_img_cmd);

            }
            number_of_loop ++;
        }
        else if((Params.StatusReg.LineFollow == 0)&&(Params.StatusReg.Survey == 1))
        {
            // get frame
            if(Got_first_frame == FALSE)
            {
                if (load_img((CPU_CHAR *)g_nextIMGfilename, &img_in1) != ERR_NONE)
                {
                    //printf("erreur ouverture\n");
                }else
                {
                    // saving name
                    sprintf((char *)inputfilename,"%s",g_nextIMGfilename);
                }
                Got_first_frame = TRUE;
            }else
            {
                if (load_img((CPU_CHAR *)g_nextIMGfilename, &img_in2) != ERR_NONE)
                {
                    //printf("erreur ouverture\n");
                }else
                {
                    // saving name
                    sprintf((char *)inputfilename,"%s",g_nextIMGfilename);
                }
                // subsample image

                //compare two image img_in1 et img_in2
                img_diff_1_2 = search_diff(11,1,1,GREEN|RED|BLUE,&img_in1,&img_in2,&img_out1,&change_1_2);
                if((img_diff_1_2 & DIFF_HIGH_QUANTITY)!=0)
                {
                    //calculate center of diff aera, relatively to image center
                    //mouvementx on left is negative
                    //mouvementx on left is positive
                    mouvementx = (((change_1_2.BotLeft.x/2 + change_1_2.BotRight.x/2)*100)/img_in1.wi)-50 ;
                    mouvementy = (((change_1_2.BotLeft.y/2 + change_1_2.TopLeft.y/2)*100)/img_in1.he)-50 ;
					move_detected = TRUE;
					ttt = (CPU_INT32S)clock();
					time ( &ttt );
                }else
                {

                    mouvementx = 0;
                    mouvementy = 0;
                }

                //calculate treatment time
                finish = clock();
                duration_process = (double)(finish - start) / CLOCKS_PER_SEC;
				
				start = clock();
				//drive motor according to diff
                if((abs(mouvementx) > mouvementx_threshold)||(abs(mouvementy) > mouvementy_threshold))
                {
                    pthread_mutex_lock(&mtx_LockCamera);

                    Params.XMotorCommand.Steps = (CPU_INT16S)((CPU_FP32)mouvementx/(CPU_FP32)5);
					Params.YMotorCommand.Steps = (CPU_INT16S)((CPU_FP32)mouvementy/(CPU_FP32)5);
					printf("X-Steps:%d Y-Steps:%d \n",Params.XMotorCommand.Steps,Params.YMotorCommand.Steps);
					if(Params.XMotorCommand.Steps > 0)
					StepperTurnCounterClockwise(MotorX_LR, Params.XMotorCommand.Speed, Params.XMotorCommand.Steps, &sem_XMotorEmergencyStop);
					else
					StepperTurnClockwise(MotorX_LR, Params.XMotorCommand.Speed, 0-Params.XMotorCommand.Steps, &sem_XMotorEmergencyStop);

					if(Params.YMotorCommand.Steps > 0)
					StepperTurnCounterClockwise(MotorY_UD, Params.YMotorCommand.Speed, Params.YMotorCommand.Steps, &sem_YMotorEmergencyStop);
					else
					StepperTurnClockwise(MotorY_UD, Params.YMotorCommand.Speed, 0-Params.YMotorCommand.Steps, &sem_YMotorEmergencyStop);

					pthread_mutex_unlock(&mtx_LockCamera);

					//Params.YMotorCommand.Unused = 0;
                    Got_first_frame = FALSE;
                }else
				{
					Params.XMotorCommand.Steps = 0;
					Params.YMotorCommand.Steps = 0;
				}
				//calculate move time
                finish = clock();
                duration_move = (double)(finish - start) / CLOCKS_PER_SEC;

				start = clock();
                //printf("Img treated (in %.3f), x_move : %d, y_move : %d\n",duration,mouvementx,mouvementy);
				//if(move_detected == TRUE)
				{
					copy_img( &img_in2, &img_out2);
                    highlight_area(&img_out2,&change_1_2,SetRGB(255,0,0));
#if defined (RPi)
					//sprintf((char *)outputfilename,"out_survey_%ld_diff.bmp",(CPU_INT32U)ttt);
					//write_img((CPU_CHAR *)outputfilename,&img_out1);
					//sprintf((char *)outputfilename,"out_survey_%ld_1.bmp",(CPU_INT32U)ttt);
					//write_img((CPU_CHAR *)outputfilename,&img_in1);
					//sprintf((char *)outputfilename,"out_survey_%ld_2.bmp",(CPU_INT32U)ttt);
					//write_img((CPU_CHAR *)outputfilename,&img_in2);
					sprintf((char *)outputfilename,"out_survey_%ld_2_diff.bmp",(CPU_INT32U)ttt);
					write_img((CPU_CHAR *)outputfilename,&img_out2);
					

					sprintf((char *)temporary_cmd,"gm mogrify -format jpg %s",outputfilename);
					system((const char *)temporary_cmd);
					sprintf((char *)temporary_cmd,"rm %s -f",outputfilename);
					system((const char *)temporary_cmd);
					pch=(CPU_CHAR *)strchr((const char *)outputfilename,'.');
					if(pch!=NULL)
					{
						outputfilename[pch-outputfilename+1] = 'j';
						outputfilename[pch-outputfilename+2] = 'p';
						outputfilename[pch-outputfilename+3] = 'g';
					}
					//calculate io time
					finish = clock();
					duration_io = (double)(finish - start) / CLOCKS_PER_SEC;
					
					start = clock();
					sprintf((char *)temporary_cmd,"cp %s /media/motiondetect_imgrepo/small/image_small.jpg -f",outputfilename);
					system((const char *)temporary_cmd);
					
					//calculate io time
					finish = clock();
					duration_net = (double)(finish - start) / CLOCKS_PER_SEC;
					
					sprintf((char *)temporary_cmd,"rm %s -f",outputfilename);
					system((const char *)temporary_cmd);
#endif

				}
				move_detected = FALSE;

				//store img_in2 in img_in1
                copy_img( &img_in2, &img_in1);
				
				
            }
            // suppress file
#if defined (Win32)
            sprintf((char *)delele_img_cmd,"del %s",inputfilename);
#elif defined (RPi)
            sprintf((char *)delele_img_cmd,"rm %s -rf",inputfilename);
#endif
            system((const char *)delele_img_cmd);

        }else
        {
            // nothing matter
        }


    }
    printf("fin tache\n");


    pthread_exit(NULL); /* Fin du thread */
    return NULL;
}
