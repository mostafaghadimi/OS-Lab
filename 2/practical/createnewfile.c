#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int open_result;
    int write_result;
    open_result = open("oslab2.txt", O_CREAT | O_WRONLY, 0777);
    write_result = write(open_result, "Mostafa Ghadimi\n", strlen("Mostafa Ghadimi\n"));
    close(open_result);
    return 0;
}
