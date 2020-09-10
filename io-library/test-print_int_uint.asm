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



section .data
start_test: db "Starting test...", 10, 0
start_test_len: equ $ - start_test

expected_value_msg: db "Expected value: ", 0

s15: db "15", 10, 0
s666: db "666", 10, 0
s77: db "77", 10, 0
s_77: db "-77", 10, 0
sUnsigned_77: db "18446744073709551539", 10, 0

line_break: db 10, 0


section .text

global _start
_start:

    mov rdi, start_test
    call print
    
    
    mov rdi, s15
    call print_expected

    mov rdi, 15
    call print_uint
 
    mov rdi, line_break
    call print
     
    mov rdi, s666
    call print_expected

  
    mov rdi, 666
    call print_uint
  
    mov rdi, line_break
    call print
        
    mov rdi, s_77
    call print_expected


    mov rdi, -77
    call print_int
     
    mov rdi, line_break
    call print
         
    mov rdi, sUnsigned_77
    call print_expected

    
    mov rdi, -77
    call print_uint
     
    mov rdi, line_break
    call print
 
    mov rax, 60
    mov rdi, 0

    syscall

 
len:
    xor rax, rax    
    .str_len_loop:
        cmp byte[rdi + rax], 0  ; check for null sym
        je .end                 ; if equals
        inc rax                 ; increment counter
        jmp .str_len_loop       ; back to loop
    .end:
        ret

print:
    xor rax, rax
    
    mov rsi, rdi                ; put argument // lol
    
    call len          ; length of passed string
    mov rdx, rax

    mov rax, sys_write
    mov rdi, stdout
    syscall
    ret

print_expected:
    push r9
    mov r9, rdi    
    mov rdi, expected_value_msg
    call print
    mov rdi, r9
    call print

    pop r9
    ret
