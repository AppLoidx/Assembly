%include "list_config.inc"

extern string_equals

section .text

global find_word

find_word:
    .compare_loop:
        test rsi, rsi
        jz .not_found
        push rdi
        push rsi
        add rsi, key_size
        call string_equals
        pop rsi
        pop rdi
        test rax, rax
        jnz .found
        mov rsi, [rsi]  ; imortant: used restored rsi value (see saving in stack above)
        jmp .compare_loop
    .not_found:
        xor rax, rax    ; we should return 0 if we didn't find key
        jmp .end
    .found:
        mov rax, rsi
        jmp .end   
    .end:
        ret
        
