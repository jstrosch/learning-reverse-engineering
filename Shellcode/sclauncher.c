#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

char hexcc[1] = {0x90};
char shellcode[1] = ""; //use this as a byte array to load shellcode. Example: char shellcode[2] = "\x55\xEB"

void usage(void) {
	puts("[~] Simple shellcode launcher and debugger! This program can read shellcode from a file or use an internal array.");
	puts("[~] Usage: sclauncher.exe [-f=shellcode.bin] [-o=INT] [-bp]");
	puts("\t-f: path to file to load shellocode. If you don't provide a file, \n\t\t it will check for an internal array - see source code.");
	puts("\t-bp: insert a breakpoint before the shellcode, only use if debugging");
	puts("\t-o: adjust entry point offset in bytes");
}

int main(int argc, char **argv) {
	unsigned int shellcode_size = 0;
	unsigned int offset = 0;
	char file_path[100] = {0};
	FILE*fp = NULL;

	void*stage = NULL;
	int i = 0, len = 0;
	void* target_addy = NULL;
	int arg_count = 0;
	char*p = NULL;

	for (arg_count = 0; arg_count < argc; arg_count++) {

		if (!strncmp(argv[arg_count],"-h",2)) {
			usage();
			exit(0);
		} else if (!strncmp(argv[arg_count],"-o",2)) {
			p = strstr(argv[arg_count],"=");
			if (p == NULL){
				printf("[!] Equal sign between \"%s\" parameter not found, exiting!",argv[arg_count]);
				exit(1);
			}
			p++;
			offset = atoi(p);
			printf("[*] Adjusting shellcode entry point to (hex): %08x\n", offset);
		} else if(!strncmp(argv[arg_count],"-f",2)){
			p = strstr(argv[arg_count],"=");
			if (p == NULL){
				printf("[!] Equal sign between \"%s\" parameter not found, exiting!",argv[arg_count]);
				exit(1);
			}
			p++;
			strncpy(file_path,p,strlen(argv[arg_count]));
			printf("[*] Loading shelloce from %s\n",file_path);
		} else if(!strncmp(argv[arg_count],"-bp",3)){
			hexcc[0] = 0xCC;
			puts("[*] Inserting breakpoint before shellocde");
		}
	}

	if (strlen(file_path) > 0){
		printf("[*] Loading shellcode from path: %s\n", file_path);
		fp = fopen(file_path,"rb");

		if (fp != NULL){
			fseek(fp, 0L, SEEK_END);
			shellcode_size = ftell(fp);
			printf("[*] Found %d bytes of shellcode\n",shellcode_size);
			fseek(fp, 0L, SEEK_SET);
			
			stage = VirtualAlloc(0, shellcode_size + 1, 0x1000,0x40 );
			printf("[*] Allocated memory at %p\n", stage);
			memmove(stage, &hexcc, 1);
			fread((char*)stage+1, sizeof(char), shellcode_size, fp);
			printf("[*] Shellcode copied\n");
		} else {
			puts("[!] Error opening file... exiting");
			exit(1);
		}

	} else if(strlen(shellcode)) {
		puts("[*] Loading shellcode from internal array");
		shellcode_size = strlen(shellcode);
		printf("[*] Found %d bytes of shellcode\n",shellcode_size);

		stage = VirtualAlloc(0, shellcode_size + 1, 0x1000,0x40 );
		printf("[*] Allocated memory at %p\n", stage);
		memmove(stage, &hexcc, 1);
		//memmove((char*)stage+1, fp, shellcode_size);
		printf("[*] Shellcode copied\n");

	} else {
		puts("[!] No shellcode found, exiting...");
		exit(1);
	}

	if (offset) {
		target_addy = (char*)stage + offset;
		printf("[*] Adjusting offset, new entry point: 0x%p\n", target_addy);
	} else {
		target_addy = stage;
	}

	printf("[*} JUMPing to shellcode at %p, enjoy :)\n",target_addy);
	__asm {
		mov eax, target_addy
		jmp eax
	}
}