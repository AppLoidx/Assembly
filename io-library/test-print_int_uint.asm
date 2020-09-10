%include "lib.inc"

section .data
start_test: db "Starting test...", 10, 0
start_test_len: equ $ - start_test
line_break: db 10, 0


section .text

global _start
_start:

    mov rdi, start_test
    call print_string

    mov rdi, 15
    call print_uint
 
    mov rdi, line_break
    call print_string
   
    mov rdi, 666
    call print_uint
  
    mov rdi, line_break
    call print_string
    
    mov rdi, -77
    call print_uint
     
    mov rdi, line_break
    call print_string
     
    mov rdi, -77
    call print_int
     
    mov rdi, line_break
    call print_string
 
    mov rax, 60
    mov rdi, 0

    syscall
