; some system code variables
%define sys_exit 60
%define sys_read 0
%define sys_write 1

; input/output shit
%define stdin 0
%define stdout 1

; result codes
%define success 0

section .bss
    %define name_max_len 64
    name: resb name_max_len
    name_len: resq 1

section .data
    prompt: db "Please enter your name 😀: "
    prompt_len: equ $-prompt

    welcome_message: db "Hello👋, "
    welcome_message_len: equ $-welcome_message

    suffix_message: db "!🍉", 10
    suffix_message_len: equ $-suffix_message

section .text

global _start

_start:
    mov rax, sys_write
    mov rdi, stdout
    mov rsi, prompt
    mov rdx, prompt_len
    syscall

    mov rax, sys_read
    mov rdi, stdout
    mov rsi, name
    mov rdx, name_max_len
    syscall

    ; we have to store len of user's name
    mov [name_len], rax

    ; writing full welcome message with user name

    mov rax, sys_write
    mov rdi, stdout
    mov rsi, welcome_message
    mov rdx, welcome_message_len
    syscall

    
    mov rax, sys_write
    mov rdi, stdout
    mov rsi, name
    mov rdx, [name_len]
    ; we have to delete last char of user input, because he contains newline character
    ; first method: 
    sub rdx, 1
    syscall

    mov rax, sys_write
    mov rdi, stdout
    mov rsi, suffix_message
    mov rdx, suffix_message_len
    syscall

    mov rax, sys_exit
    mov rbx, success
    syscall

    



