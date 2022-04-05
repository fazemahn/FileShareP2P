#include "pdu.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#define PORT 4444
int main(int argc, char const *argv[]){
    int server_fd, new_socket;
    if ((server_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == 0){
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    return 0;
}