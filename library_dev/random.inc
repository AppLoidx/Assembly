
SECTION .text

    Random_number:
        rdtsc  
        ret
    Random_bool:
        rdtsc
        xor     rdx, rdx            ; Required because there's no division of RAX solely
        mov     rcx, 2              ; 2 possible values
        div     rcx                 ; EDX:EAX / ECX --> EAX quotient, EDX remainder
        mov     rax, rdx            ; -> RAX = [0,1]
        ret 
