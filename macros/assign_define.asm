section .data
loop_with_define: equ "------------------------------"

%assign i 0 
%rep    10 
        inc     word [i] 
        %define i i + 1 
%endrep


loop_with_assign: equ "-------------------------------"

%assign i 0 
%rep    10 
        inc     word [i] 
        %assign i i + 1 
%endrep

just_another_one: equ "---------------------------------"

%define a 0
inc a
inc a
%assign a a + 1
inc a
%assign a a + 1
inc a
%assign a a + 1
inc a
%assign a a + 1
inc a

%define a a + 1
inc a
%define a a + 1
inc a
%define a a + 1
inc a
%define a a + 1
inc a
%define a a + 1
inc a
%assign a a + 1
inc a


