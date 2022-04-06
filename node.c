#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>

#define MYPORT "4444"
#define BACKLOG 5
int main(int argc, char const *argv[]){
    /* Network Interface Process*/
    pid_t monitor_pid = fork();
    if (monitor_pid == 0){
        struct sockaddr_storage their_addr;
        socklen_t addr_size;
        struct addrinfo hints, *res;
        int sockfd, new_fd;

        // !! don't forget your error checking for these calls !!

        // first, load up address structs with getaddrinfo():

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

        getaddrinfo(NULL, MYPORT, &hints, &res);

        // make a socket, bind it, and listen on it:

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        bind(sockfd, res->ai_addr, res->ai_addrlen);
        listen(sockfd, BACKLOG);

        // now accept an incoming connection:

        addr_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

        // ready to communicate on socket descriptor new_fd!
    }
    /* Main Loop Process*/
    else{
        int user_choice;
        bool mainLoop = true;
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
                    printf("case2\n");
                    break;
                /* De-register Files */
                case(3):
                    printf("case3\n");
                    break;
                default:
                    mainLoop = false;
                    break;
            }
        }while(mainLoop);
        kill(monitor_pid, SIGQUIT);
        printf("Network Process Terminated\n");
        printf("Terminating Node\n");
    }
    return 0;
}
