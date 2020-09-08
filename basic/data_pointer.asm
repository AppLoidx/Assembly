section .data

first_msg : db "First message with some length", 10, 0
second_msg: db "Second message", 10, 0

second_msg_len: equ $ - second_msg
first_msg_len: equ $ - second_msg_len - 1 - first_msg

first_msg_len2 : equ second_msg - first_msg

section .text

global _start

_start:
    mov rax, 1
    mov rdi, 1

    mov rsi, first_msg
    mov rdx, first_msg_len

    syscall

    mov rax, 1
    mov rdi, 1

    mov rsi, first_msg
    mov rdx, first_msg_len2

    syscall

    mov rax, 1
    mov rdi, 1

    mov rsi, second_msg
    mov rdx, second_msg_len

    syscall

    mov rax, 60
    mov rdi, 0

    syscall
