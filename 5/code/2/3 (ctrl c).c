#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int counter = 1; // global flag


void handler(int signum) {
    if (counter == 2){
        printf("\nexiting...\n");
        exit(1);
    }
    else {
        printf("\npress CTRL + C again to exit.\n");
        counter += 1;
    }
}


int main() 
{
    signal(SIGINT, handler);
    while(1);
}