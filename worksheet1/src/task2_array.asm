; Muhammad Saqlain - Worksheet 1
%include "asm_io.inc"

section .data
t1  db  "Building array", 10, 0
t2  db  "Summing", 10, 0
t3  db  "Sum=", 0
N   equ 100

section .bss
ar  resd N
sm  resd 1

section .text
global _asm_main

_asm_main:
    enter 0, 0
    pusha

    mov eax, t1
    call print_string
    mov ecx, 1
    mov edi, ar
.f:
    mov [edi], ecx
    add edi, 4
    inc ecx
    cmp ecx, N+1
    jle .f

    mov eax, t2
    call print_string
    xor eax, eax
    xor ecx, ecx
    mov esi, ar
.s:
    add eax, [esi]
    add esi, 4
    inc ecx
    cmp ecx, N
    jl .s
    mov [sm], eax

    mov eax, t3
    call print_string
    mov eax, [sm]
    call print_int
    call print_nl

    popa
    xor eax, eax
    leave
    ret

