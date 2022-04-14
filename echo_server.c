/* A simple echo server using TCP */
#include <stdio.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define SERVER_TCP_PORT 4444	/* well-known port */
#define BUFLEN	256	/* buffer length */
#define STDIN 0
int echod(int);
void reaper(int);

int main(int argc, char **argv)
{

	int sd, new_sd, client_len, port;
	struct sockaddr_in server, client;
	int i, j, rv, n;
	switch(argc){
	case 1:
		port = SERVER_TCP_PORT;
		break;
	case 2:
		port = atoi(argv[1]);
		break;
	default:
		fprintf(stderr, "Usage: %s [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	/* Bind an address to the socket	*/
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
		fprintf(stderr, "Can't bind name to socket\n");
		exit(1);
	}

	/* queue up to 5 connect requests  */
	listen(sd, 5);
	listen(0, 5);

	/* Local Terminal Input Buffer*/
	char locbuf[BUFLEN];

	/* IO Multiplexing */
	fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number
	FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

	//fd_set rfds, afds;  
	//FD_ZERO(&rfds);  
	
	FD_SET(STDIN ,&master); // Listening on STDIN
	FD_SET(sd, &master); /* Listening on a TCP socket */
	//FD_SET(STDIN, &rfds); /* Listening on stdin */
	fdmax = sd; 
	while(1) {client_len = sizeof(client);
		read_fds = master;
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }
		for(i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &read_fds)) {
				if (i == sd) {
					new_sd = accept(sd, (struct sockaddr *)&client, &client_len);
					if(new_sd < 0){
						fprintf(stderr, "Can't accept client \n");
						exit(1);
					}else{
						FD_SET(new_sd, &master); // add to master set
						if (new_sd > fdmax) {    // keep track of the max
                            fdmax = new_sd;
							printf("Got New Connection\n");
                        }
					}
				} else if (i==STDIN){
					char tmp[1000], *p;
					if (!fgets(tmp, sizeof tmp, stdin)) /* deal with error */;
					if (!*tmp) /* embedded NUL detected: input is not a text file */;
					if (tmp[strlen(tmp) - 1] != '\n') /* partial line */;
					p = tmp;

					//while (*p && *p != 'X') putchar(*p++);
					// ignore the X and all the subsequent characters

				}
				else{ //Handle client data
					if ((n = recv(i, locbuf, BUFLEN, 0)) <= 0) {
                        // got error or connection closed by client
                        if (n == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    }else{
						 // we got some data from a client
                        // for(j = 0; j <= fdmax; j++) {
                        //     // send to everyone!
                        //     if (FD_ISSET(j, &master)) {
                        //         // except the listener and ourselves
                        //         if (j != listener && j != i) {
                        //             if (send(j, buf, nbytes, 0) == -1) {
                        //                 perror("send");
                        //             }
                        //         }
                        //     }
						// }
						printf("Got some Data\n");
					}
				}
			}
		}  
	}
	(void) signal(SIGCHLD, reaper);
}

/*	echod program	*/
int echod(int sd)
{
	char	*bp, buf[BUFLEN];
	int 	n, bytes_to_read;

	while(n = read(sd, buf, BUFLEN)) 
		write(sd, buf, n);
	close(sd);

	return(0);
}

/*	reaper		*/
void	reaper(int sig)
{
	int	status;
	while(wait3(&status, WNOHANG, (struct rusage *)0) >= 0);
}
