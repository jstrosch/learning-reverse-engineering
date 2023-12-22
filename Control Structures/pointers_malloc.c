#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv, char ** envp) {
	int * x = malloc(10 * sizeof(int));
	char * y = malloc(107);
	short * s = malloc(2 * sizeof(short));

	*x = 125;
	*y = '!';
	*s = 34;
}