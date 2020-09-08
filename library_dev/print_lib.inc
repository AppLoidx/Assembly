section .text
    ; Prints with syscall rsi (with rdi for length) value
    print:
        mov rax, 1
        mov rdi, 1

        syscall
        ret         ; don't forget it
                    ; or try to call this section without ret :)
