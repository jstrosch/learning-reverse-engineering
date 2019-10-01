#include <stdlib.h>
#include <stdio.h>

int main(void) {

	int iarray[10] = {0,1,2,3,4,5,6,7,8,9};

	char carray[25] = "hello ";

	char*cptr = &carray[6];

	int temp = 0;

	for (int i = 0; i < 5; i++) {

		temp = iarray[i+5];
		temp += iarray[i];

		cptr += sprintf(cptr,"%d ", temp);
	}

	printf("%s\n", carray);
}