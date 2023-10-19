:: This script helps to assemble and compile ASM source code using 
:: a driver program. If you need to assemble any additional files, 
:: uncomment the NASM command, providing the ASM file as input.

@echo off

set arg1=%1

:: nasm -f win32 asm_io.asm

nasm -f win32 "%arg1%.asm"

:: -Zi produces debug symbols, can be used for debugging/disassembling
cl -Zi -Fe"%arg1%.exe" driver.c "%arg1%.obj" asm_io.obj /link legacy_stdio_definitions.lib