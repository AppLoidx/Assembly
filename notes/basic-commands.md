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


#### lea eax, [rdi+1]

*из [stackoverflow](https://ru.stackoverflow.com/questions/610242/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80%D0%BD%D0%B0%D1%8F-%D0%BA%D0%BE%D0%BC%D0%B0%D0%BD%D0%B4%D0%B0-lea)*

```asm
lea eax, [rdi+1]
```
Эта команда загружает в eax адрес значения, лежащего по адресу rdi + 1. Т.е. она загружает в eax просто rdi+1.

Выглядит странно, и чтобы понять зачем именно нужна lea, и чем она лучше просто аналогичного вызова mov или ручного вычисления адреса, нужно понять как команды записываются в памяти и выполняются процессором.

Например, у вас есть команда чтения значения:
```asm
mov  eax, [rdi+1]; взять значение по адресу "rdi + 1"
```

Она компилируется в что-то вроде
```
[опкод mov][флаг что складываем в eax][флаг что берем по адресу rdi][+1]
```

![](https://i.stack.imgur.com/YEdtD.png)

Т.е. в `66 67 8B 47 01`

Предположим что вам нужно получить сам адрес rdi+1 в eax

Вы можете сделать одно из двух:

Высчитать его руками:
```asm
mov eax, rdi + 1; не работает, move не умеет плюс!
```
и вам придется написать:
```asm
mov eax, rdi 
inc eax; 66 05 01 00 00 00
```
т.е. выполнить две инструкции. Возможно, хороший вариант, но только для простых +1. А для адресов вида [bp+si+4]?
```asm
mov eax, bp
add eax, si
add eax, 4; да, некрасиво!
```
или выполнить lea:
```asm
lea  eax, [rdi+1]
```

!()[https://i.stack.imgur.com/ZlfnK.png]

Сравните с `mov`:

!()[https://i.stack.imgur.com/YEdtD.png]

Байткод: `66 67 8D 47 01`

Отличается только opcode, `8B` -> `8D`.

В процессоре есть готовый, очень эффективный механизм для базовых операций с адресами. 
И он уже реализован для операции mov - ведь mov умеет доставать значение по адресу!.

При использовании lea процессор делает все, что делает при mov, 
но пропускает последний шаг - извлечение значения по адресу. 
Вместо этого он складывает в eax сам адрес. Это гораздо удобнее и 
быстрее чем считать вещи вроде rdi + 1 отдельными командами.

