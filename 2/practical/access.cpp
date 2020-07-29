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
        printf("%s doesn't exist.", path);
    }
    return 0;
}