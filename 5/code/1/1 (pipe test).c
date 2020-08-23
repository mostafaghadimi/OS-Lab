#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    int pipefd[2];
    int result = pipe(pipefd);
    if (result == 0)
    {
        printf("pipe done");
    }
    return 0;
}