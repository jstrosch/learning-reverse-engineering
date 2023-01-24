#include <stdio.h>
#include <windows.h>

int main(void) {
    char* fmt_address = "0x%08x\n";
    DWORD dwNtdllBase = 0x0;
    HINSTANCE dwLoadLibrary = 0x0;

	__asm
	{

		xor ebx, ebx             ; // clear ebx
		mov ebx, fs:[ 0x30 ]     ; // get a pointer to the PEB: https://msdn.microsoft.com/en-us/library/windows/desktop/aa813706(v=vs.85).aspx

        push ebx
        push ebx
        push fmt_address
        call printf
        add esp, 8
        pop ebx

		mov ebx, [ ebx + 0x0C ]  ; // get PEB->Ldr - https://msdn.microsoft.com/en-us/library/windows/desktop/aa813708(v=vs.85).aspx
		mov ebx, [ ebx + 0x1C ]  ; // get PEB->Ldr.InInitializationOrderModuleList.Flink (1st entry)
		mov ebx, [ ebx + 0x08 ]  ; // get the entries base address

		mov dwNtdllBase, ebx
    }

    dwLoadLibrary = LoadLibrary(TEXT("ntdll"));

    printf("0x%08x <--> 0x%08x\n", dwNtdllBase, dwLoadLibrary);
}