#include <stdio.h>
#include <windows.h>

int main(void) {
	int counter = 0;
	int mem_size = 0x1000;
	unsigned int *ptr = VirtualAlloc(NULL, mem_size, MEM_COMMIT, PAGE_READWRITE);
	printf("[*] Allocated memory at %p...\n", ptr);

	for (counter = 0; counter < 10; counter++){
		ptr[counter] = counter;
		printf("[-] Data at address %p -> %d\n", &ptr[counter], counter);
	}

	VirtualFree(ptr, mem_size, MEM_DECOMMIT);
	printf("[*] Memory freed... :)");
}