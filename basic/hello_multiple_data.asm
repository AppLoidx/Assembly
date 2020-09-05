section .data
message db "Hello, world!", 10  ; here 10 equals to \n
one_line_message db "Onee-chan!" ; without line break
; each letter, comma, space, or exclamation point is one byte.

section .text

global _start ; this defines the entry-point of the program
_start:
    mov rax, 1
    ; mov - moves data and values around between registers and memory
    ; rax - general purpose register
    ; 1 - just number [simple value :) ]
    ; result is move value "1" ro rax register
    
    ; preparing to make a call to the operating system. 
    ; 1 stands for sys_write, which tells the operating system to write some data to a file or stream. 
    ; rax is the register Linux checks to figure out what a program wants it to do.

    mov rdi, 1
    ; similar to the above, but in this context 1 stands for STDOUT
    ; Another way to use it is to set value to 2 for STDERR

    ; as result of whole program we have rax and rdi with values 1

    mov rsi, message
    ; write to rsi our message

    ; when Linux checks this register to see what data to write to STDOUT, 
    ; it will find the location in memory where the message string begins.
    
    mov rdx, 14
    ; how many bytes of message to write

    ; rsi doesn't have value "Hello, world!" (message), instead of this
    ; he contains address that points to a location in memeory where the letter "H" is

    ; like in bcomp

    ; So, we have to tell Linux when to stop read data

    syscall
    
    ; Linux will check the values we loaded into the 
    ; registers rax, rdi, rsi, and rdx, and it will use those values to determine what to do.

    ; Full programm execution

    ; 1. Check rax and find the value 1, which stands for sys_write. This means we want to write some data.
    ; 2. Check rdi to see where to write the data and find 1, which stands for STDOUT (the console).
    ; 3. Check rsi to see what data to write, and find the address of our string.
    ; 4. Check rdx to see how much data to write, and find the length of our string.
    ; 5. Finally, with these 4 questions answered, Linux will write 14 characters starting from the "H" in "Hello, world!" 
    ;    out to the console, and then return control to our program.

    
    ; WRITE ANOTHER MESSAGE:
    ; ! you have to restore register values !
    mov rax, 1
    mov rdi, 1
    mov rsi, one_line_message
    mov rdx, 10 ; another length

    syscall ; use system to print another message

    ; EXIT PROGRAMM:
    mov rax, 60
    mov rdi, 0
    syscall
