; Muhammad Saqlain - Worksheet 1
%include "asm_io.inc"

section .data
x   dd  77
y   dd  23
m1  db  "Sum of ", 0
m2  db  " and ", 0
m3  db  " is ", 0

section .bss
z   resd 1

section .text
global _asm_main

_asm_main:
    enter 0, 0
    pusha

    mov eax, m1
    call print_string
    mov eax, [x]
    call print_int
    mov eax, m2
    call print_string
    mov eax, [y]
    call print_int
    mov eax, m3
    call print_string
    
    mov eax, [x]
    mov ebx, [y]
    add eax, ebx
    mov [z], eax
    call print_int
    call print_nl

    popa
    xor eax, eax
    leave
    ret

