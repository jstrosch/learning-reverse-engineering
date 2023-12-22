#include <stdio.h>

int main(int argc, char ** argv, char ** envp) {

	int x;
	char c_array[20];
	short s_array[20];
	int i_array[20] = {0};

	for(x = 0; x < 20; x++) {
		c_array[x] = x;
		s_array[x] = x;		
		i_array[x] = x;
	}
}