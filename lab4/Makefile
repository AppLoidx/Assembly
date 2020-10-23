CC = gcc
MAIN_COMPILE_CONFIG = -o main

all: main
run: all
	./main

clean:
	rm *.o
	rm main
	rm serialized.bin
	rm output.txt

main: main.c linked_list.c util.c functions.c
	$(CC) $(MAIN_COMPILE_CONFIG) main.c linked_list.c util.c functions.c