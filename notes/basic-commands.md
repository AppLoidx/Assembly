# NASM Commands

The NetWide Assembler, NASM, which is freely available on the Web, has many advanced commands for defining macros and assembling multiple output formats. For simple purposes, however, only a few commands, or pseudo-ops, are needed:

#### ORG 100h
* Sets the "origin'' address, the starting address for the program. For .COM files, this should be set to 100h as shown (so this will usually be the first statement in the source of any .COM program).

#### SECTION .text
* Marks the start of a group of instructions to be assembled into the executable code part of the program.

#### SECTION .data
* Marks the start of a group of declarations of initialized data.
#### SECTION .bss
* Marks the start of a group of declarations of uninitialized data. The SECTION commands may be interleaved in any order; when the file is assembled, all of the .text sections will be concatenated, followed by all of the .data and .bss sections in that order (the .bss sections don't actually generate any code, but the process of reserving blocks of memory causes the associated labels to be given the correct values).
#### label DB data list
* Declares a block of memory initialized with the given list of data, each datum occupying one byte. The label becomes associated with the starting address of the block. Think of this as defining a variable (with the name "label'') and giving it an initial value. The data may be given as numbers (default base is decimal; the suffixes 'h', 'q', and 'b' select hexadecimal, octal, and binary, respectively) or character strings (surrounded by either single or double quotes). For example,
```asm
name    DB      "George", 0Dh, 0Ah ; last two characters are CR, LF
age     DB      1
```

#### label DW data list
* Same as DB, except each datum is stored in a 16-bit word (two successive bytes). This is mainly used for numeric data; the only difference it makes to strings from using DB is that if a string has an odd number of characters then it is padded with a final zero byte. For example,
```asm
name    DW      "George", 0Dh, 0Ah
age     DW      1
```

is equivalent to
```asm
name    DB      "George", 0Dh, 00h, 0Ah, 00h
age     DB      1, 0
```
(which is probably not what you want for the string).
#### label RESB size
* Reserves a block of memory consisting of size bytes; assign the starting address to the label, but don't generate any output. For example, after the following commands, if x wound up at address 1230h, then y would start at address 1238h:
```asm
x       RESB    8
y       RESB    4
```

The next available address in this section would be 123Ch.

#### label RESW size
* Same as RESB, except size gives the number of two-byte words to allocate.

####  label EQU expr
* Defines the label to be equal to the value of the expression. The expression may involve constants, other labels, and the usual range of integer operators from C. There are also two special constants, $ and $$. The first, a single dollar sign, evaluates to the current address being assembled at the beginning of the current line. This is useful for the following sort of calculation:
```asm
msg     DB      "Hello"
msglen  EQU     $ - msg
```

Since the current address at the start of the second line is the next address after the end of the string, subtracting the address of the start of the string will give the length of the string---in this case, msglen will be defined as 5. The second special constant, the double dollar sign, evaluates to the address of the start of the current section, so that you can check how much space you've used (with the expression $ - $$).
