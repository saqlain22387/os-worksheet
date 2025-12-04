global init
extern main_entry

MULTIBOOT_MAG equ 0x1BADB002
MULTIBOOT_FLG equ 0x0
MULTIBOOT_CHK equ -MULTIBOOT_MAG

STACK_SZ equ 4096

section .bss
align 4
stack_area:
    resb STACK_SZ

section .text
align 4
    dd MULTIBOOT_MAG
    dd MULTIBOOT_FLG
    dd MULTIBOOT_CHK

init:
    mov esp, stack_area + STACK_SZ
    mov eax, 0xCAFEBABE
    call main_entry

forever:
    cli
    hlt
    jmp forever

