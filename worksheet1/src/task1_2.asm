; Muhammad Saqlain - Worksheet 1
%include "asm_io.inc"

section .data
p1  db  "Number A: ", 0
p2  db  "Number B: ", 0
r   db  "A+B = ", 0

section .bss
a   resd 1
b   resd 1

section .text
global _asm_main

_asm_main:
    enter 0, 0
    pusha

    mov eax, p1
    call print_string
    call read_int
    mov [a], eax

    mov eax, p2
    call print_string
    call read_int
    mov [b], eax

    mov eax, r
    call print_string
    mov eax, [a]
    add eax, [b]
    call print_int
    call print_nl

    popa
    xor eax, eax
    leave
    ret

