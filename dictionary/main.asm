%include "list_config.inc"
%include "colon.inc"
%include "words.inc"

%assign buffer_alloc 256

extern read_word
extern find_word
extern print_string
extern string_length
extern exit


section .data
    msg_noword: db "No such word ❌", 0

section .text

global _start
_start:
    push rbp
    mov rbp, rsp        ; store rsp value
    sub rsp, buffer_alloc
    mov rdi, rsp
    call read_word
    mov rdi, rax
    mov rsi, last_elem
    call find_word      ; search in our list
    test rax, rax
    jz .word_not_found
    add rax, key_size   ; points to start of value
    push rax
    mov rax, [rsp]
    mov rdi, rax
    call string_length
    pop rdi
    add rdi, rax
    inc rdi             ; for null-terminator
    call print_string
    mov rsp, rbp        ; restore stack pointer
    pop rbp
    mov rdi, 0
    call exit 
 .word_not_found:
    mov rdi, msg_noword
    call print_string
    mov rsp, rbp        ; restore stack pointer
    pop rbp
    mov rdi, 0
    call exit
