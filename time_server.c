/* time_server.c - main */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>

#include "pdu.h"
#include "content.h"


/*------------------------------------------------------------------------
 * main - Iterative UDP server for TIME service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	struct  sockaddr_in fsin;	/* the from address of a client	*/
	struct PDU buf;		/* "input" buffer; any size > 0	*/
	char    *pts;
	int	sock;			/* server socket		*/
	time_t	now;			/* current time			*/
	int	alen;			/* from-address length		*/
	struct  sockaddr_in sin; /* an Internet endpoint address         */
        int     s, type;        /* socket descriptor and socket type    */
	int 	port=3000;
                                                                                

	switch(argc){
		case 1:
			break;
		case 2:
			port = atoi(argv[1]);
			break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
	}

        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(port);
                                                                                                 
    /* Allocate a socket */
        s = socket(AF_INET, SOCK_DGRAM, 0);
        if (s < 0)
		fprintf(stderr, "can't creat socket\n");
                                                                                
    /* Bind the socket */
        if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		fprintf(stderr, "can't bind to %d port\n",port);
        listen(s, 5);	
	alen = sizeof(fsin);

	while (1) {

		
		if (recvfrom(s, &buf, sizeof(buf), 0,
				(struct sockaddr *)&fsin, &alen) < 0)
			fprintf(stderr, "recvfrom error\n");
		
		switch(buf.type){
            case('r'):
				int numbytes;
                printpdu_r((pdur)&buf);
                pdur request = (pdur)&buf;
                // send acknowledgement
                struct PDU *senddata = create('a', "Acknowledged\n");
                if ((numbytes=sendto(s, senddata, sizeof(struct PDU), 0,
                    (struct sockaddr *)&fsin, sizeof(fsin))) == -1) {
                        perror("index: sendto");
                        exit(1);
                }
	            printf("index: sent %d bytes to %s\n", numbytes, "node");

                break;
			case('s'):
				break;
			case('t'):
				break;
			case('e'):
				break;
			case('o'):
				break;
            default:
				(void) time(&now);
        		pts = ctime(&now);

				(void) sendto(s, pts, strlen(pts), 0,
				(struct sockaddr *)&fsin, sizeof(fsin));
                break;
        }

		
	}
}
