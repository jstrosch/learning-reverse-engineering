;;; This follows along with the book by Dr Paul Carter
;;; Available at: https://pacman128.github.io/pcasm/

%include "asm_io.inc"
;
; initialized data is put in the .data segment
;
segment .data
formats db "Hello TTD :) %d",0xD,0xA,0xD,0xA,0

;
; uninitialized data is put in the .bss segment
;
segment .bss

;
; code is put in the .text segment
;
segment .text
        global  _asm_main
        extern _printf
_asm_main:
    push ebp,
    mov ebp, esp
;; START WRITING YOUR CUSTOM PROGRAMS HERE.
;; If you need stack space for locals, make sure to adjust the prologue
;; i.e. sub esp, XX bytes

    mov eax, 0x42
    xor eax, 0x32

    push eax
    push formats 
    call _printf
    add esp, 8


;; END OF CUSTOM CODE. 
    mov esp, ebp 
    pop ebp
    ret 


