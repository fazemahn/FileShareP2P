/*
** node.c -- a datagram "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "pdu.h"
#include "content.h"

#define SERVERPORT "4950"	// the port users will be connecting to


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
int main(int argc, char *argv[])
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
    struct sockaddr_storage their_addr;
    struct PDU recv;
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    
	if (argc != 2) {
		fprintf(stderr,"usage: node hostname\n");
		exit(1);
	}
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET6; // set to AF_INET to use IPv4
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("node: socket");
			continue;
		}
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) < 0) {
			close(sockfd);
			perror("node: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "node: failed to create socket\n");
		return 2;
	}

    
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
                printf("Registration\n");
                struct PDUr *senddata = create_r("node1", "content1", 5);
                void * sendstr = senddata;
                printpdu_r(senddata);
                if ((numbytes = sendto(sockfd, sendstr, sizeof(struct PDU), 0,
                    p->ai_addr, p->ai_addrlen)) == -1) {
                        perror("node: sendto");
                        exit(1);
                }
	            printf("node: sent %d bytes to %s\n", numbytes, "server");
                printf("wait for ack or err\n");
                // listen for ack or err
                addr_len = sizeof their_addr;
                if ((numbytes = recvfrom(sockfd, &recv, sizeof(struct PDU) , 0,
		            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
		                perror("recvfrom");
		                exit(1);
	            }
	            printf("node: got packet from %s\n",
		        inet_ntop(their_addr.ss_family,
		        get_in_addr((struct sockaddr *)&their_addr),s, sizeof s));
	            printf("node: packet is %d bytes long\n", numbytes);

                break;
            /* De-register Files */
            case(3):
                printf("case3\n");
                break;
            default:
                
                close(sockfd);
                mainLoop = 0;
                break;
        }
    }while(mainLoop);

	return 0;
}
