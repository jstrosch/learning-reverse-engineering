#include <stdio.h>

int main(int argc, char ** argv, char ** envp) {

	int i;

	for(i = 0; i < argc; i++) {
		printf("--%s\n", *argv);
		argv++;
	}
}