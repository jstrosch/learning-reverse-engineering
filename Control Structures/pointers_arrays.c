#include <stdio.h>

int main(int argc, char ** argv, char ** envp) {

	int x;
	short array[37];
	x = 12;
	
	while( x > 0) {
		x++;
	}

	for(x = 0; x < 37; x++) {
		array[x] = x * x;
	}
}