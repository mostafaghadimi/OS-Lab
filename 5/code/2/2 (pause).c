#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int flag = 1; // global flag


void alarm_handler(int signum) {
    flag = 0;
}


int main() 
{
    signal(SIGALRM, alarm_handler); // Register signal handler
    alarm(5);
    printf("Looping forever...\n");
    while(flag){
        pause();
    };
    printf("This line should be executed.\n");
    return 0;
}