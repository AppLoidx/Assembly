%include "print_lib.inc"

section .data

msg: db "Yo!", 10, 0
msg_len: equ $ - msg

section .text
    global _start

    _start:
        mov rsi, msg
        mov rdx, msg_len

        call print
        
        mov rdi, 0
        mov rax, 60
        syscall
