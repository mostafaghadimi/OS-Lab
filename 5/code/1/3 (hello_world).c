#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSG_SIZE 11


int main()
{
    int pipefd[2];
    int result = pipe(pipefd);
    if (fork() > 0)
    {
        printf("parent is executed...\n");
        close(pipefd[0]);
        printf("writing message in the file descriptor...\n");
        write(pipefd[1], "Hello world", MSG_SIZE);
        printf("closing read file descriptor in parent...\n");
        close(pipefd[1]);
    }
    else {
        char msg[MSG_SIZE];
        printf("child is executed...\n");
        read(pipefd[0], msg, MSG_SIZE);
        printf("%s", msg);
    }
    return 0;
}