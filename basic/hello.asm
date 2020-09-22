section .data
message:
db  'hello, Onee-chan!'

section .text
global _start

_start:
    mov     rax, 1           ; 'write'
    mov     rdi, 1           ;
    mov     rsi, message     ;
    mov     rdx, 20          ;
    
    syscall

    mov     rax, 60          ; 'exit'
    xor     rdi, rdi
    syscall
