#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int result;
    char *path = argv[1];
    result = access(path, F_OK);
    if (result == 0)
    {
        printf("%s exists\n", path);
    }
    else
    {
        printf("%s doesn't exist\n", path);
    }
    result = access(path, R_OK);
    if (result == 0) {
        printf("read permission is granted\n");
    }
    else {
        printf("read permission isn't granted\n");
    }
    result = access(path, W_OK);
    if (result == 0) {
        printf("write permission is granted\n");
    }
    else {
        printf("write permission isn't granted\n");
    }
    result = access(path, X_OK);
    if (result == 0) {
        printf("execute permission is granted\n");
    }
    else {
        printf("execute permission isn't granted\n");
    }
    return 0;
}