#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
	long result;
	result = mkdir("testdir", 0777);
	printf("The result is %ld.\n", result);
	return 0;
}
