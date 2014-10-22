#include "../includes.h"


void* threadTCPCom (void* arg)
{
    CPU_INT32S port=DEF_PORT;
    typedef CPU_INT32U socklen_t;
#if defined (Win32)
	SOCKET serv_sock,client_sock;
	SOCKADDR_IN serv_sin,cli_sin;
#elif defined (RPi)
	CPU_INT32S serv_sock,client_sock;
	struct sockaddr_in serv_sin,cli_sin;
#else
    #error "No OS defined"
#endif
    socklen_t clilen;

#if defined (Win32)
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);
#endif

	CPU_INT08U data_in[MAX_TCP_DATA];
	CPU_INT08U data_out[MAX_TCP_DATA];
	CPU_INT16S data_in_size;
	CPU_INT16S data_out_size,ret_send;

    e_RPK_Error rpk_err;

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(serv_sock == INVALID_SOCKET)
    {
        printf("Could not create socket\n");
    }else
    {
        serv_sin.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_sin.sin_port = htons(port);
        serv_sin.sin_family = AF_INET;

#if defined (Win32)
        if(bind(serv_sock,(SOCKADDR *) &serv_sin, sizeof serv_sin) == SOCKET_ERROR)
#elif defined (RPi)
		if(bind(serv_sock,(struct sockaddr *) &serv_sin, sizeof serv_sin) == SOCKET_ERROR)
#endif
        {
            printf("Could not create bind socket\n");

        }else
        {
            if(listen(serv_sock, MAX_CLIENTS) == SOCKET_ERROR)
            {
                printf("Could not create listen\n");
            }else
            {
                while(1) /* Boucle infinie */
                {
                    m_sSleep(1);
                    //Accept and incoming connection
                    printf("Waiting for incoming connections...\n");

#if defined (Win32)
					clilen = sizeof(SOCKADDR_IN);
#elif defined (RPi)
					clilen = sizeof(struct sockaddr);
#endif

                    //accept connection from an incoming client
#if defined (Win32)
					client_sock = accept(serv_sock, (struct sockaddr *)&cli_sin, (int*)&clilen);
#elif defined (RPi)
					client_sock = accept(serv_sock, (struct sockaddr *)&cli_sin, &clilen);
#endif
                    printf("Client connected\n");
                    do
                    {
                        data_in_size    = recv(client_sock , (char *) data_in , MAX_TCP_DATA , 0);

                        if(data_in_size >0)
                        {
                            rpk_err = RPK_Frame_Manage(data_in, data_in_size, &g_rpkframe_in);
                            if(rpk_err == rpkerr_NoError)
                            {
                                rpk_err = RPK_Frame_Process(&g_rpkframe_in,&g_rpkframe_out);
                            }

                            data_out_size = RPK_SendPrepare(&g_rpkframe_out,data_out);
                            ret_send = send(client_sock,(const char *)data_out,data_out_size,0);
                        }

                    }while(data_in_size>=0&&(ret_send>=0));
                    printf("Client disconnected\n");

                }
            }
        }




    }



    pthread_exit(NULL); /* Fin du thread */
    return NULL;
}
