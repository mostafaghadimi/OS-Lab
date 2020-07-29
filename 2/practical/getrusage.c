#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

int main() {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    printf("maximum resident set size: %ld\n", ru.ru_maxrss);
    printf("integral shared memory size: %ld\n", ru.ru_ixrss);
    printf("integral unshared stack size: %ld\n", ru.ru_isrss);
}