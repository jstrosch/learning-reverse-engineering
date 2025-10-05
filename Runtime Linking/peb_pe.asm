; assemble with: nasm -f win32 peb_pe.asm
; Link with: link /subsystem:console peb_pe.obj kernel32.lib ucrt.lib /entry:main

BITS 32
section .text
global _main
extern _ExitProcess@4

_main:
    ; Save registers
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    ; Step 1: Get PEB (FS:[0x30] in 32-bit)
    mov eax, fs:[0x30]          ; PEB address
    mov eax, [eax + 0x0C]       ; PEB->Ldr (PEB_LDR_DATA)
    mov esi, [eax + 0x0C]       ; InLoadOrderModuleList (head)

    ; Step 2: Find kernel32.dll
    mov edi, kernel32_str       ; "kernel32.dll" (Unicode)
find_dll_loop:
    mov ebx, [esi]              ; Next entry (Flink)
    cmp ebx, esi                ; Reached head? (end of list)
    je not_found
    mov edx, [ebx + 0x30]       ; LDR_DATA_TABLE_ENTRY.BaseDllName.Buffer
    call compare_unicode        ; Compare with "kernel32.dll"
    test eax, eax
    jnz found_dll
    mov esi, ebx                ; Move to next entry
    jmp find_dll_loop

found_dll:
    mov eax,  [ebx + 0x18]    ; LDR_DATA_TABLE_ENTRY.DllBase
    mov [kernel32_base], eax
; Step 3: Parse PE header
    mov esi, eax                ; kernel32.dll base
    movzx eax, word [esi]       ; DOS header e_magic
    cmp ax, 0x5A4D             ; 'MZ'
    jne not_found
    mov eax, [esi + 0x3C]       ; e_lfanew
    add eax, esi                ; NT headers
    mov edx, [eax + 0x78]       ; DataDirectory[EXPORT].VirtualAddress
    add edx, esi                ; Export directory address
    mov [export_dir], edx

    ; Step 4: Walk export directory to find SetConsoleTitleA
    mov ecx, [edx + 0x18]       ; NumberOfNames
    mov ebx, [edx + 0x20]       ; AddressOfNames
    add ebx, dword [kernel32_base]              ; RVA to VA
    xor eax, eax                ; Counter (i)

export_loop:
    cmp eax, ecx                ; Check if done
    jge not_found
    mov esi, [ebx + eax*4]      ; Name RVA
    add esi, [kernel32_base]    ; Name VA
    mov edi, setconsoletitlea_str ; "SetConsoleTitleA"
    push eax 
    call compare_ansi           ; Compare strings
    test eax, eax
    pop eax
    jnz found_export
    inc eax                     ; Next name
    jmp export_loop

found_export:
    mov edi, [edx + 0x24]       ; AddressOfNameOrdinals
    add edi, dword [kernel32_base]
    mov edx, [edx + 0x1C]       ; AddressOfFunctions
    add edx, dword [kernel32_base]
    movzx ecx, word [edi + eax*2] ; Ordinal from AddressOfNameOrdinals
    mov eax, [edx + ecx*4]      ; Function RVA from AddressOfFunctions
    add eax, [kernel32_base]    ; Function VA
    mov [setconsoletitlea_addr], eax

    ; Step 5: Call SetConsoleTitleA
    push title_str              ; Pointer to new title
    call [setconsoletitlea_addr]

    ; Exit
    push 0
    call _ExitProcess@4

not_found:
    ; Exit with error
    push 1
    call _ExitProcess@4

; Compare Unicode strings (edx = str1, edi = str2)
compare_unicode:
    push esi
    push edi
compare_unicode_loop:
    mov ax, [edx]
    mov cx, [edi]
    cmp ax, cx
    jne compare_unicode_fail
    test ax, ax
    jz compare_unicode_success
    add edx, 2
    add edi, 2
    jmp compare_unicode_loop
compare_unicode_success:
    mov eax, 1
    pop edi
    pop esi
    ret
compare_unicode_fail:
    xor eax, eax
    pop edi
    pop esi
    ret

; Compare ANSI strings (esi = str1, edi = str2)
compare_ansi:
    push esi
    push edi
compare_ansi_loop:
    mov al, [esi]
    mov cl, [edi]
    cmp al, cl
    jne compare_ansi_fail
    test al, al
    jz compare_ansi_success
    inc esi
    inc edi
    jmp compare_ansi_loop
compare_ansi_success:
    mov eax, 1
    pop edi
    pop esi
    ret
compare_ansi_fail:
    xor eax, eax
    pop edi
    pop esi
    ret

section .data
kernel32_str:
    dw 'K', 'E', 'R', 'N', 'E', 'L', '3', '2', '.', 'D', 'L', 'L', 0
setconsoletitlea_str:
    db 'SetConsoleTitleA', 0
title_str:
    db 'My Custom Console Title', 0
kernel32_base:
    dd 0
export_dir:
    dd 0
setconsoletitlea_addr:
    dd 0