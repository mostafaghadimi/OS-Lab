#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MyStruct {
    int a;
    int b;
    char name[20];
};

struct MyStruct *instance;

int main()
{
    instance = (struct MyStruct *) malloc(sizeof(struct MyStruct));
    instance -> a = 4;
    instance -> b = 5;
    strcpy(instance -> name, "Mostafa Ghadimi");
    printf("a: \t%d\n", instance -> a);
    printf("b: \t%d\n", instance -> b);
    printf("name: \t%s\n", instance -> name);
}