#include <stdio.h>

void doWhileLoop(void) {

	size_t x = 99;

	while ( x > 0 ) {
		printf("%lu\n", x);
		x--;
	}
}

int main(void) {
	
	size_t i;

	for(i = 0; i < 10; i++) {
		printf("%lu\n",i);
	}

	doWhileLoop();

}