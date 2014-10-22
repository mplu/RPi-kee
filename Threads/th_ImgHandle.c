#include "../includes.h"


void* threadImgHandle (void* arg)
{
	t_img img_in1;
    t_img img_inter1;
    t_img img_out1;
	CPU_FP64 ** filter0;
	clock_t start, finish;
	CPU_INT32U number_of_loop = 0;
    double duration;
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
	CPU_INT08U enable_out_img = FALSE;

	t_pixel tab_pixel[NUMBER_OF_SEGMENT];

	CPU_FP64 MotorCommandRatio = 0;

	init_img(&img_in1);
    init_img(&img_out1);
    init_img(&img_inter1);

	CPU_CHAR inputfilename[IMG_FILENAME_SIZE];
	CPU_CHAR outputfilename[IMG_FILENAME_SIZE];
	CPU_CHAR delele_img_cmd[IMG_FILENAME_SIZE + 10];


	filter0 = createTableFP64(GAUSS_SIZE,GAUSS_SIZE);
	create_gauss_filter(filter0,GAUSS_SIZE,SIGMA);

	while(1) /* Boucle infinie */
    {
        sem_wait(&sem_Img_available); //waiting for new img to treat

        start = clock();

		if (load_img((CPU_CHAR *)g_nextIMGfilename, &img_in1) != ERR_NONE)
		{
			//printf("erreur ouverture\n");
		}else
		{
		    // saving name
		    sprintf((char *)inputfilename,"%s",g_nextIMGfilename);

			apply_linfilter(&img_in1,filter0,GAUSS_SIZE,GREEN|RED,&img_inter1);
			if(enable_out_img == TRUE)
			{
				sprintf((char *)outputfilename,"out__gauss_%s",inputfilename);
				write_img(outputfilename,&img_inter1);
			}

			search_contrast(CONTRAST_TOLERANCE,&img_inter1,&img_out1,SetRGB(255,255,255),GREEN|RED,HOR);
			if(enable_out_img == TRUE)
			{
				sprintf((char *)outputfilename,"out_contdetec_%s",inputfilename);
				write_img(outputfilename,&img_out1);
			}

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
				tab_pixel[index].y = i;
				tab_pixel[index].x = 0;
				maxvalue = 0;
				for(j=0+margin;j<(img_out1.wi - margin);j++)
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

			finish = clock();
			duration = (double)(finish - start) / CLOCKS_PER_SEC;

			//printf( "%d duration : %f seconds\n", number_of_loop,duration );
			(void)duration;
			if (enable_out_img == TRUE)
			{
				sprintf((char *)outputfilename,"out%05lu_process_%s_%.2f_%.2f_%d.bmp",number_of_loop
																				,inputfilename
																				,av_angle
																				,av_x
																				,Params.Analog_Values.ImgMoveDirection);
				write_img(outputfilename,&img_in1);
			}
			printf("Img treated %d\n",Params.Analog_Values.ImgMoveDirection);

			// suppress file
#if defined (Win32)
			sprintf((char *)delele_img_cmd,"del %s",inputfilename);
#elif defined (RPi)
			sprintf((char *)delele_img_cmd,"rm %s -rf",inputfilename);
#endif
			system((const char *)delele_img_cmd);
			asm("nop");

		}
		number_of_loop ++;

    }
    printf("fin tache\n");


    pthread_exit(NULL); /* Fin du thread */
    return NULL;
}
