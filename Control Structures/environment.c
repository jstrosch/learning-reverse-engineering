#include <stdio.h>

int main(int argc, char ** argv, char ** envp) {

	char * name = argv[0];
	char * e = envp[0];
	int i;

	printf("Program name: %s\n", name);

	for ( i = 1; i < argc; i++) {
		printf("\tArg: %s\n", argv[i]);
	}

	puts("");

	while (e != NULL) {
		printf("\tENV: %s\n", e);
		envp++;
		e = *envp;
	}

}