; Muhammad Saqlain - Worksheet 1
%include "asm_io.inc"

section .data
m0  db  "Ready", 10, 0
m1  db  "Begin: ", 0
m2  db  "End: ", 0
m3  db  "Range sum: ", 0
er  db  "Invalid input!", 10, 0
SZ  equ 100

section .bss
v   resd SZ
b   resd 1
e   resd 1
rs  resd 1

section .text
global _asm_main

_asm_main:
    enter 0, 0
    pusha

    mov ecx, 1
    mov edi, v
.i:
    mov [edi], ecx
    add edi, 4
    inc ecx
    cmp ecx, SZ+1
    jle .i

    mov eax, m0
    call print_string

    mov eax, m1
    call print_string
    call read_int
    mov [b], eax
    cmp eax, 1
    jl .er
    cmp eax, SZ
    jg .er

    mov eax, m2
    call print_string
    call read_int
    mov [e], eax
    cmp eax, 1
    jl .er
    cmp eax, SZ
    jg .er

    mov eax, [b]
    cmp eax, [e]
    jg .er

    xor eax, eax
    mov ecx, [b]
.c:
    mov edx, ecx
    dec edx
    shl edx, 2
    add edx, v
    add eax, [edx]
    cmp ecx, [e]
    jge .o
    inc ecx
    jmp .c

.o:
    mov [rs], eax
    mov eax, m3
    call print_string
    mov eax, [rs]
    call print_int
    call print_nl
    jmp .x

.er:
    mov eax, er
    call print_string
.x:
    popa
    xor eax, eax
    leave
    ret

