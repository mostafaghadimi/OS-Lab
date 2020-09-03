#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    printf("\nsbrk(0) %llu ",(unsigned long long)sbrk(0));
    printf("\nmalloc(8) %llu ",(unsigned long long)malloc(8));
    printf("\nmalloc(8) %llu ",(unsigned long long)malloc(8));
    printf("\nsbrk(8) %llu ",(unsigned long long)sbrk(8));
    printf("\nmalloc(8) %llu ",(unsigned long long)malloc(8));
    printf("\nmalloc(8) %llu ",(unsigned long long)malloc(8));  
    printf("\n");
    return 0;
}