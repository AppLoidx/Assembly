all: main
run: main
	./main

main: main.o bmp.o
	gcc -o main $^

%.o: %.c
	gcc -c -o $@ $<

clean:
		find . -type f -name '*.o' -delete
