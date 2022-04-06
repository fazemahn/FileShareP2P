/* time_client.c - main */

#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>                                                                            
#include <netinet/in.h>
#include <arpa/inet.h>

#include "pdu.h"
#include "content.h"
                                                                                
#include <netdb.h>

#define	BUFSIZE 64

#define	MSG		"Any Message \n"


/*------------------------------------------------------------------------
 * main - UDP client for TIME service that prints the resulting time
 *------------------------------------------------------------------------
 */
int
main(int argc, char **argv)
{
	char	*host = "localhost";
	int	port = 3000;
	char	now[100];		/* 32-bit integer to hold time	*/ 
	struct hostent	*phe;	/* pointer to host information entry	*/
	struct sockaddr_in sin;	/* an Internet endpoint address		*/
	int	s, n, type;	/* socket descriptor and socket type	*/
	struct PDU buf;
	struct  sockaddr_in fsin;
	int alen = sizeof(fsin);
	switch (argc) {
	case 1:
		break;
	case 2:
		host = argv[1];
	case 3:
		host = argv[1];
		port = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "usage: UDPtime [host [port]]\n");
		exit(1);
	}

	memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;                                                                
    sin.sin_port = htons(port);
                                                                                        
    /* Map host name to IP address, allowing for dotted decimal */
	if ( phe = gethostbyname(host) ){
			memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
	}
	else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
	fprintf(stderr, "Can't get host entry \n");
                                                                                
    /* Allocate a socket */
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	fprintf(stderr, "Can't create socket \n");
	
                                                                                
    /* Connect the socket */
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	fprintf(stderr, "Can't connect to %s %s \n", host, "Time");
	
	/* Main Client Loop */
	int mainLoop = 1;
    int user_choice; 
    
    do{        
        printf("1. Download\n"\
                "2. Register\n"\
                "3. De-register\n"\
                "0. Exit\n");
        scanf("%d", &user_choice);
        switch(user_choice){
            /* Download Files */
            case (1):
                printf("case1\n");
                break;
            /* Register Files */
            case(2):
                // open tcp socket
				// send r type
				int numbytes;
				struct PDUr *senddata = create_r("node1", "content1", 5);
                //void * sendstr = senddata;
                printpdu_r(senddata);
                if ((numbytes = sendto(s, senddata, sizeof(struct PDU), 0,
                    (struct sockaddr *)&sin, sizeof(sin))) == -1) {
                        perror("node: sendto");
                        exit(1);
                }
				// await a/e type
				if (recvfrom(s, &buf, sizeof(buf), 0,
				(struct sockaddr *)&fsin, &alen) < 0)
					fprintf(stderr, "recvfrom error\n");
				char *p = buf.data;
				while(*p!='\n')
					printf("%c", *p++);
				printf("\n");
			break;
            /* De-register Files */
            case(3):
                printf("case3\n");
                break;
            default:
                
                mainLoop = 0;
                break;
        }
    }while(mainLoop);


	//(void) write(s, MSG, strlen(MSG));
	//(void) sendto(s, MSG, strlen(MSG), 0, 
	//	(struct sockaddr *)&sin, sizeof(sin));
	/* Read the time */

	//n = read(s, (char *)&now, sizeof(now));
	//if (recvfrom(s, &buf, sizeof(buf), 0,
	//			(struct sockaddr *)&fsin, &alen) < 0)
	//		fprintf(stderr, "recvfrom error\n");
	//write(1, buf, sizeof(buf));
	//char *p = &buf;
	//while(*p!='\n')
	//	printf("%c", *p++);
	//printf("\n");
	exit(0);
}
