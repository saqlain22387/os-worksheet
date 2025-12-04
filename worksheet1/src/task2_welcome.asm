; Muhammad Saqlain - Worksheet 1
%include "asm_io.inc"

section .data
q1  db  "Name: ", 0
q2  db  "Count (50-100): ", 0
g1  db  "Greetings, ", 0
g2  db  "!", 0
e1  db  "Error: under 50", 10, 0
e2  db  "Error: over 100", 10, 0
LO  equ 50
HI  equ 100

section .bss
nm  resb 48
ct  resd 1
i   resd 1

section .text
global _asm_main

_asm_main:
    enter 0, 0
    pusha

    mov eax, q1
    call print_string
    mov edi, nm
.rd:
    call read_char
    cmp al, 10
    je .dn
    mov [edi], al
    inc edi
    jmp .rd
.dn:
    mov byte [edi], 0

    mov eax, q2
    call print_string
    call read_int
    mov [ct], eax

    cmp eax, LO
    jl .e1
    cmp eax, HI
    jg .e2

    mov dword [i], 0
.lp:
    mov eax, [i]
    cmp eax, [ct]
    jge .ex
    mov eax, g1
    call print_string
    mov eax, nm
    call print_string
    mov eax, g2
    call print_string
    call print_nl
    inc dword [i]
    jmp .lp

.e1:
    mov eax, e1
    call print_string
    jmp .ex
.e2:
    mov eax, e2
    call print_string
.ex:
    popa
    xor eax, eax
    leave
    ret

