#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[]){
    /* Process to monitor network */
    if (fork()==0){
        printf("monitor process running");

    }
    /* Process for the main loop*/
    else{
        short user_choice = 1;
    do{        
        switch(user_choice){
            /* Look up Files */
            case (1):
                printf("choices being read");
                break;
            /* Register Files */
            case(2):
                break;
            /* De-register Files */
            case(3):
                break;
            default:
                perror(1);
        }
    }while(1);

    }
    
    return 0;
}
