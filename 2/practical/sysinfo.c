
#include <linux/kernel.h>
#include <stdio.h>
#include <sys/sysinfo.h>

int main()
{
    const double megabyte = 1024 * 1024;
    struct sysinfo si;
    sysinfo(&si);
    printf("total RAM: %5.1f MB\n", si.totalram / megabyte);
    printf("free RAM: %5.1f MB\n", si.freeram / megabyte);
    return 0;
}