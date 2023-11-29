#include <windows.h>
#include <stdio.h>

void ExceptionHandler(EXCEPTION_RECORD * er);

int main(int*argc, char**argv) {
    
    __asm {
        mov eax, ExceptionHandler
        push eax
        push fs:[0]
        mov fs:[0], esp
        xor eax, eax
        mov [eax], 0
    }
    printf("after exception...");
    ExitProcess(0);
}

void ExceptionHandler(EXCEPTION_RECORD * er) {
    puts("In exception handler :)");
    printf("exception address: %p\n", er->ExceptionAddress);
    PVOID* ret_addy = er->ExceptionAddress;
    __asm {
        mov eax, ret_addy
        add eax, 3
        push eax
        ret
    }
}