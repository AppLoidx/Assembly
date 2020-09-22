%define S "some shit"

section .data
msg: db S, 0
.end:
section .text
global _start
_start:

    mov rax, 1
    mov rdi, 1

    mov rsi, msg
    mov rdx, msg.end - msg

    mov rax, 60
    mov rdi, 0
    syscall
