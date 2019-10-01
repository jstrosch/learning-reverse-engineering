#include <stdio.h>

struct my_struct {
	char a; 	// 1 bytes        Offset 0
	// 			   1 byte padding
	short b; 	// 2 bytes        Offset 2
	int c; 		// 4 bytes        Offset 4
	float d; 	// 4 bytes        Offset 8
}; 				// Total: 12 bytes

struct foo1 {
	char *p; 		// 4 bytes Offset 0
	char c;			// 1 byte  Offset +4
					// 3 bytes padding
	long x;			// 4 bytes Offset +8
}					// Total: 12 bytes

void demo(struct my_struct *ms) {

	ms->a = 'j';
	ms->b = 1;
	ms->c = 32;
	ms->d = 99;

}

int main(void) {

	struct my_struct*ms = (struct my_struct*)malloc(sizeof(struct my_struct));

	demo(ms);

	struct foo1*my = (struct foo1*)malloc(sizeof(struct foo1));

	char a = 'a';

	my->p = &a;
	my->c = 'b';
	my->x = 1;

}