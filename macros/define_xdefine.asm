%define isTrue 0
; тупой код, конечно :)
%define isFalse isTrue

label1: equ "With just define"

v1: equ isFalse

%define isTrue 1

v2 : equ isFalse

%define isTrue 0
; тупой код, конечно :)


label2: equ "With super xdefine"

%xdefine isFalse isTrue
v1: equ isFalse

%define isTrue 1

v2 : equ isFalse


