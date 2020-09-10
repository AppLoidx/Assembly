section .data

; --------------------------------------------:
text : db "Message len is : ", 0
text_len : equ $ - text
br: db 10
.end:
; --------------------------------------------

section .text

string_length:
    xor rax, rax
        .loop:
            cmp byte[rdi, rax], 0
            jz .exit
            inc rax
            jmp .loop
        .exit:
            ret


global _start
_start:
    
    mov rsi, ds
    mul rsi, 16
    mov rdx, text4.end

    mov rax, 1
    mov rdi, 1


    syscall

    mov rax, 60
    mov rdi, 0 ; status
    syscall

