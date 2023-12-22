#include <stdio.h>

int main(void) {

	int x = 0;
	int y = 1;
	int z = 0;

	puts("Enter a number:");
	scanf("%d", &z);

	if(x < 10) {

		if(z > 0)
			puts("x < 10 and z > 0");
		else
			puts("x < 10 and z <= 0");

	} else {

		if(z > 0)
			puts ("x >= 10 and z > 0");
		else
			puts("x >= 10 and z < 0");
	}
}