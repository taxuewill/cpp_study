#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>



void ouch(int sig){
    printf("\nOuch! - I got %d",sig);
}

int main(){
    struct sigaction act;
    act.sa_handler=ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESETHAND;

    sigaction(SIGINT,&act,0);    
    while(1){
        printf("...");
        sleep(1);
    }

    return 0;
}