# Базовые примеры


### Structure of a NASM Program

<p align='center'><img alt="NASM Structure" src="https://cs.lmu.edu/~ray/images/nasmstructure.png" /><p>

<p align='center'><img alt="RDX" src="https://cs.lmu.edu/~ray/images/rdx.png" /><p>
<p align='center'><img alt="RDX" src="https://www.cs.virginia.edu/~evans/cs216/guides/x86-registers.png" /><p>


### Forms of addressing

These are the basic forms of addressing:

* `[ number ]`
* `[ reg ]`
* `[ reg + reg*scale ]`      *scale is 1, 2, 4, or 8 only*
* `[ reg + number ]`
* `[ reg + reg*scale + number ]`

The number is called the displacement; the plain register is called the base; the register with the scale is called the index.

### Immediate Operands

```asm
200          ; decimal
0200         ; still decimal - the leading 0 does not make it octal
0200d        ; explicitly decimal - d suffix
0d200        ; also decimal - 0d prefex
0c8h         ; hex - h suffix, but leading 0 is required because c8h looks like a var
0xc8         ; hex - the classic 0x prefix
0hc8         ; hex - for some reason NASM likes 0h
310q         ; octal - q suffix
0q310        ; octal - 0q prefix
11001000b    ; binary - b suffix
0b1100_1000  ; binary - 0b prefix, and by the way, underscores are allowed
```

### Reserve space

To reserve space (without initializing), you can use the following pseudo instructions. They should go in a section called `.bss` (you'll get an error if you try to use them in a `.text` section):

```asm
buffer:         resb    64              ; reserve 64 bytes
wordvar:        resw    1               ; reserve a word
realarray:      resq    10              ; array of ten reals
```

### Understanding Calling Conventions

*from [https://cs.lmu.edu/~ray/notes/nasmtutorial/](https://cs.lmu.edu/~ray/notes/nasmtutorial/)*

* From left to right, pass as many parameters as will fit in registers. The order in which registers are allocated, are:
  * For integers and pointers, `rdi, rsi, rdx, rcx, r8, r9`.
  * For floating-point `(float, double), xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7`.
* Additional parameters are pushed on the stack, right to left, and are to be removed by the caller after the call.
* After the parameters are pushed, the call instruction is made, so when the called function gets control, the return address is at `[rsp]`, the first memory parameter is at `[rsp+8]`, etc.
* **The stack pointer rsp must be aligned to a 16-byte boundary before making a call**. Fine, but the process of making a call pushes the return address (8 bytes) on the stack, so when a function gets control, rsp is not aligned. You have to make that extra space yourself, by pushing something or subtracting 8 from rsp.
* The only registers that the called function is required to preserve (the calle-save registers) are: `rbp, rbx, r12, r13, r14, r15`. All others are free to be changed by the called function.
* The callee is also supposed to save the control bits of the XMCSR and the x87 control word, but x87 instructions are rare in 64-bit code so you probably don’t have to worry about this.
* Integers are returned in rax or rdx:rax, and floating point values are returned in `xmm0` or `xmm1:xmm0`.


### Conditional Instructions

After an arithmetic or logic instruction, or the compare instruction, cmp, the processor sets or clears bits in its rflags. The most interesting flags are:

* `s` (sign)
* `z` (zero)
* `c` (carry)
* `o` (overflow)

So after doing, say, an addition instruction, we can perform a jump, move, or set, based on the new flag settings. For example:

* `jz label`         	Jump to label L if the result of the operation was zero
* `cmovno x, y`	x ← y if the last operation did not overflow
* `setc x`	x ← 1 if the last operation had a carry, but x ← 0 otherwise (x must be a byte-size register or memory location)

The conditional instructions have three base forms: `j` for conditional `jump`, `cmov` for `conditional move`, and `set` for `conditional set`. The suffix of the instruction has one of the 30 forms: `s ns z nz c nc o no p np pe po e ne l nl le nle g ng ge nge a na ae nae b nb be nbe`

### Command Line Arguments

*echo.asm*

```asm
; -----------------------------------------------------------------------------
; A 64-bit program that displays its command line arguments, one per line.
;
; On entry, rdi will contain argc and rsi will contain argv.
; -----------------------------------------------------------------------------

        global  main
        extern  puts
        section .text
main:
        push    rdi                     ; save registers that puts uses
        push    rsi
        sub     rsp, 8                  ; must align stack before call

        mov     rdi, [rsi]              ; the argument string to display
        call    puts                    ; print it

        add     rsp, 8                  ; restore %rsp to pre-aligned value
        pop     rsi                     ; restore registers puts used
        pop     rdi

        add     rsi, 8                  ; point to next argument
        dec     rdi                     ; count down
        jnz     main                    ; if not done counting keep going

        ret
```

```text
./a.out
dog
22
-zzz
hi there
```

### Stack frame layout on x86-64

*Пиздец неточная инфа :) [https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/#id10](https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/#id10)*

Example stack in C:

```c
long myfunc(long a, long b, long c, long d,
            long e, long f, long g, long h)
{
    long xx = a * b * c * d * e * f * g * h;
    long yy = a + b + c + d + e + f + g + h;
    long zz = utilfunc(xx, yy, xx % yy);
    return zz + 20;
}
```

![](https://eli.thegreenplace.net/images/2011/08/x64_frame_nonleaf.png)

####  The red zone

> The 128-byte area beyond the location pointed to by %rsp is considered to be reserved and shall not be modified by signal or interrupt handlers. Therefore, functions may use this area for temporary data that is not needed across function calls. In particular, leaf functions may use this area for their entire stack frame, rather than adjusting the stack pointer in the prologue and epilogue. This area is known as the red zone.
