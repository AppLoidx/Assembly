%include "lib.inc"

; some system code variables
%define sys_exit 60
%define sys_read 0
%define sys_write 1

; input/output
%define stdin 0
%define stdout 1

; result codes
%define success 0

; const
%define new_line 0xA
%define base_10 10

global _start
_start:
    call read_char

    mov rsi, rax
    mov rdx, 1

    mov rax, 1
    mov rdi, 1

    syscall

    mov rax, 60
    mov rdi, 0

    syscall

