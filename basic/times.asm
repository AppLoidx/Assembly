section .data
message: db "ALL HAIL ARTHUR!!!👑", 10
message_len: equ $ - message
section .text

global _start

_start:
    call print_data
    call print_data
    call print_data
    call print_data
    call print_data
    mov rax, 60
    mov rbx, 0

    syscall

section .print_data
print_data:
    mov rax, 1
    mov rbx, 1

    mov rsi, message
    mov rdx, message_len
   
    syscall
    ret
