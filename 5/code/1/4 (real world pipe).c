#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int pipefd[2];
    pipe(pipefd);

    if (fork() > 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO); //make output go to the pipe
        execlp("ls", "ls", "-a", (char *) NULL);
        // execlp(argv[1], argv[1], (char *) NULL); //for more general usage
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO); //get input from pipe
    execlp("wc", "wc",(char *) NULL);
    // execlp(argv[2], argv[2],(char *) NULL); //for more general usage
}