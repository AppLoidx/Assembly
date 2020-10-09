#!/bin/bash

INF_C="\033[1;32m"  # green (light)
EMP_C="\033[0m"     # no color
DGR_C="\033[0;33m"  # orange 

for i in **/*.asm
do
        echo -e "${INF_C}[INFO]${EMP_C} Building file : $i"
        # nasm compile
        echo -e "${INF_C}[INFO]${EMP_C} nasm -felf64 $i -o ${i%.c}.o"
        nasm "$i" -felf64 -o "${i%.c}.o"
        NASM_COMPILE_RES=$? 
        if [ $NASM_COMPILE_RES -eq 0 ]; then

            # linking
            echo -e "${INF_C}[INFO]${EMP_C} ld ${i%.c}.o -o ${i%.c}.out"
            ld "${i%.c}.o" -o "${i%.c}".out
        else
            echo -e "${DGR_C}[ERROR] Can't compile file : $i"
        fi
        done

echo -e "${DGR_C}[DELETE]${EMP_C} Deleting temp files..."
find . -type f -name '*.o' -delete
echo -e "${INF_C}DONE!${EMP_C}"
