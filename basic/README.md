# Базовые примеры


### Structure of a NASM Program

![Structure of NASM](https://cs.lmu.edu/~ray/images/nasmstructure.png)

![](https://cs.lmu.edu/~ray/images/rdx.png)

These are the basic forms of addressing:

* `[ number ]`
* `[ reg ]`
* `[ reg + reg*scale ]`      *scale is 1, 2, 4, or 8 only*
* `[ reg + number ]`
* `[ reg + reg*scale + number ]`

The number is called the displacement; the plain register is called the base; the register with the scale is called the index.
