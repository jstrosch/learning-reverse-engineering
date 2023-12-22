#include <stdio.h>
#include <stdlib.h>

typedef struct TESTS
	{
		char a;
		int b;
		char c[3];
		short d;
		int * e;
		float * f;
	} TESTS;

int main(int argc, char ** argv, char ** envp)
{
	int size = sizeof(TESTS);
	TESTS * t = malloc(size);
	t->a = 'a';
	t->b = 49;
	t->c[0] = 'c';
	t->d = 55;
	t->e = malloc(1 * sizeof(int));
	*t->e = 77;
	t->f = malloc(1*sizeof(float));
	*t->f = 3.1415926535;
	*t->f = *t->f * 2;
	printf("%f", *t->f);
}