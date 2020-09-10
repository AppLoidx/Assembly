section .data

    message : db "Your random value is : ", 0
    message_len : $ - message;
section .bss
    random_text resq 1

global random_value

section .text

; Adds mock data in rsi
add_mock_data:
    
    mov rsi, message
        
