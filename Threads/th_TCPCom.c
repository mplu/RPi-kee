#include "../includes.h"


void* threadTCPCom (void* arg)
{
    CPU_INT32S port=DEF_PORT;
    typedef CPU_INT32U socklen_t;
    SOCKET serv_sock,client_sock;
    socklen_t clilen;
	SOCKADDR_IN serv_sin,cli_sin;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);

	CPU_INT08U data_in[MAX_TCP_DATA];
	CPU_INT08U data_out[MAX_TCP_DATA];
	CPU_INT16S data_in_size;
	CPU_INT16S data_out_size,ret_send;

	CPU_INT16U i;

	// reception package
	s_rpk_frame TCP_Frame;

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(serv_sock == INVALID_SOCKET)
    {
        printf("Could not create socket\n");
    }else
    {
        serv_sin.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_sin.sin_port = htons(port);
        serv_sin.sin_family = AF_INET;

        if(bind(serv_sock,(SOCKADDR *) &serv_sin, sizeof serv_sin) == SOCKET_ERROR)
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
                    clilen = sizeof(SOCKADDR_IN);

                    //accept connection from an incoming client
                    client_sock = accept(serv_sock, (struct sockaddr *)&cli_sin, (int*)&clilen);

                    do
                    {
                        data_in_size    = recv(client_sock , (char *) data_in , MAX_TCP_DATA , 0);
                        for(i=0;i<data_in_size;i++)
                        {
                            data_out[i] = data_in[i] + 1;
                            TCP_Frame.u.raw[i] = data_in[i];
                        }
                        data_out_size = data_in_size;
                        ret_send        = send(client_sock,(const char *)data_out,data_out_size,0);
                    }while((data_in[0]!='q')&&data_in_size>0&&(ret_send>0));

                }
            }
        }




    }



    pthread_exit(NULL); /* Fin du thread */
    return NULL;
}
