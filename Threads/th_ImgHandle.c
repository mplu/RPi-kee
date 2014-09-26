#include "../includes.h"


void* threadImgHandle (void* arg)
{
	t_img img_in1;
    t_img img_inter1;
    t_img img_out1;
	CPU_FP64 ** filter0;
	clock_t start, finish;
    double duration;
    CPU_FP64 angle;
    CPU_FP64 av_angle = 0;
    CPU_INT16U av_angle_weight = 0;

    CPU_INT16U number_of_segment = NUMBER_OF_SEGMENT;
    CPU_INT16U he_of_segement;
    CPU_INT16U margin = 5;
    CPU_INT16U i,j,index;
    CPU_CHAR Luminance = 0;
    CPU_INT08U maxvalue;
	CPU_INT16U number_of_loop=1;
	t_pixel tab_pixel[NUMBER_OF_SEGMENT];

	init_img(&img_in1);
    init_img(&img_out1);
    init_img(&img_inter1);

	CPU_CHAR outputfilename[32];
	CPU_CHAR inputfilename[32];

	filter0 = createTableFP64(GAUSS_SIZE,GAUSS_SIZE);
	create_gauss_filter(filter0,GAUSS_SIZE,SIGMA);

    while(number_of_loop<7) /* Boucle infinie */
    {
        sem_wait(&sem_Img_available); //waiting for new img to treat
        start = clock();
        //printf("Img received\n");
        sprintf((char *)inputfilename,"ligne%d.bmp",number_of_loop);
		load_img((CPU_CHAR *)inputfilename, &img_in1);
	    //ok for RPi-kee

		apply_linfilter(&img_in1,filter0,GAUSS_SIZE,GREEN|RED,&img_inter1);
		//sprintf((char *)outputfilename,"imgout_gauss%d.bmp",number_of_loop);
		//write_img(outputfilename,&img_inter1);
		search_contrast(CONTRAST_TOLERANCE,&img_inter1,&img_out1,SetRGB(255,255,255),GREEN|RED,HOR);
		sprintf((char *)outputfilename,"imgout_contdetect%d.bmp",number_of_loop);
		write_img(outputfilename,&img_out1);

        //looking for remarquable point

        he_of_segement = img_out1.he / (number_of_segment+1);

        //for each segment
        av_angle_weight = 0;
        for(index = 0 ; index <= number_of_segment ; index++)
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
                if((tab_pixel[index].x-tab_pixel[index-1].x)!=0)
                {
                    angle=atan((CPU_FP32)(tab_pixel[index].y-tab_pixel[index-1].y)/(CPU_FP32)(tab_pixel[index].x-tab_pixel[index-1].x));
                }else
                {
                    angle = PI / 2.0;
                }
                av_angle = (angle + (av_angle * av_angle_weight))/(CPU_FP64)(av_angle_weight + 1.0);
                av_angle_weight ++;


            }
        }
        printf("%d angle %f %f\n",number_of_loop,av_angle*180.0/PI,av_angle);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf( "%d duration : %f seconds\n", number_of_loop,duration );
        sprintf((char *)outputfilename,"imgout_line%d.bmp",number_of_loop);
        write_img(outputfilename,&img_in1);
        //printf("Img treated\n");
		number_of_loop++;
    }
    printf("fin tache\n");


    pthread_exit(NULL); /* Fin du thread */
    return NULL;
}
