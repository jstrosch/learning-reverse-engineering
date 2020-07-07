#include <stdio.h>

struct aligned_struct { 
	int a;		// 4 bytes		Offset 0
	short b;	// 2 bytes		Offset +4
	char c;		// 1 byte		Offset +6
	char d;		// 1 byte		Offset +7
};				// Total: 8 bytes

struct padded_struct {
	char a; 	// 1 bytes      Offset 0
				// 1 byte 		padding
	short b; 	// 2 bytes      Offset 2
	int c; 		// 4 bytes      Offset 4
	int* d; 	// 4 bytes      Offset 8
}; 				// Total: 12 bytes

struct padded2_struct {
	char *p; 		// 4 bytes Offset 0
	char c;			// 1 byte  Offset +4
					// 3 bytes padding
	long x;			// 4 bytes Offset +8
};					// Total: 12 bytes

int main(void) {
	int z = 99;

	struct aligned_struct as = {0};
	as.a = 42;
	as.b = 0x1FF;
	as.c = 'a';
	as.d = 'b';

	struct aligned_struct*as2 = (struct aligned_struct*)malloc(sizeof(struct aligned_struct));
	as2->a = 43;
	as2->b = 3;
	as2->c = 'c';
	as2->d = 'd';

	struct padded_struct*ps = (struct padded_struct*)malloc(sizeof(struct padded_struct));
	ps->a = 'e';
	ps->b = 0xAA;
	ps->c = 44;
	ps->d = &z;
}