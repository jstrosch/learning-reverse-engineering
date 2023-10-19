;;; This follows along with the book by Dr Paul Carter
;;; Available at: https://pacman128.github.io/pcasm/

%include "asm_io.inc"
;
; initialized data is put in the .data segment
;
segment .data

;
; uninitialized data is put in the .bss segment
;
segment .bss

;
; code is put in the .text segment
;
segment .text
        global  _asm_main
_asm_main:
;; PROLOGUE
    push ebp,
    mov ebp, esp
;; START WRITING YOUR CUSTOM PROGRAMS HERE.
;; If you need stack space for locals, make sure to adjust the prologue
;; i.e. sub esp, XX bytes



;; END OF CUSTOM CODE. 
;; EPILOGUE
    mov esp, ebp 
    pop ebp
    ret 


