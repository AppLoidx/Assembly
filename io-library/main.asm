%include "lib.inc"

section .data


section .text
global _start
_start:
    
    call read_char

    mov rax, 60
    mov rdi, 0

    syscall

