section .data
    message db "Hello, "
    name db "Arthur"
    line_break db "",10
    emoji: db "😆"
    .end:

section .text

global _start;

_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    ; mov rdx, 19
    ; or you can use
    mov rdx, emoji.end - message
    syscall

    mov rax, 60
    mov rdi, 0

    syscall


