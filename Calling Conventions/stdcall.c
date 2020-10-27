#include <stdio.h>

int __stdcall demo(int a, int b, int c, int d) {
	return (a + b + c + d);
}

int main(void) {
	int a = 0;

	a =demo(1,2,3,4);
}