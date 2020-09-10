%include "print_lib.inc"
%include "random.inc"

section .bss
    random_value resq 1

section .data

msg: db "Your random number:", 10, 0
msg_len: equ $ - msg
codes: db "0123456789ABCDEF"

fool_msg: db 10, "You are fool!🤡", 0
fool_msg_len: equ $ - fool_msg

not_fool_msg: db 10, "You are not fool! 👑", 0
not_fool_msg_len: equ $ - not_fool_msg

section .text
    global _start

    exit:

        mov     rax, 60            ; invoke 'exit' system call
        xor     rdi, rdi
        syscall
 
    print_fool:
        mov rsi, fool_msg
        mov rdx, fool_msg_len
        call print
        call exit

    print_not_fool:
        mov rsi, not_fool_msg
        mov rdx, not_fool_msg_len
        call print
        call exit

    _start:
        mov rsi, msg
        mov rdx, msg_len
        call print

        call Random_number
        mov rdi, 1                  
        mov rdx, 1                  
        mov rcx, 64   
        ; Each 4 bits should be output as one hexadecimal digit
        ; Use shift and bitwise AND to isolate them
        ; the result is the offset in 'codes' array
    .loop_print_rnd_num:                            
        push rax                    
        sub rcx, 4   
        ; cl is a register, smallest part of rcx
        ; rax -- eax -- ax -- ah + al
        ; rcx -- ecx -- cx -- ch + cl
        sar rax, cl                 
        and rax, 0xf                
                                                                                
        lea rsi, [codes + rax]
        mov rax, 1                  
        
        ;syscall leaves rcx and r11 changed
        push rcx                              
        syscall                     
        pop rcx                     
        
        pop rax
        ; test can be used for the fastest 'is it a zero?' check
        ; see docs for 'test' command
        test rcx, rcx
        jnz .loop_print_rnd_num   

    .print_fool_or_not:
        xor rax, rax
        call Random_bool

        cmp rax, 0
        je print_fool
        jne print_not_fool

                                                                                                                                                                                                                                                                                           
