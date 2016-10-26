all: function_y1.o function_y2.o main.o
	gcc function_y1.o function_y2.o main.o -o lab2

main.o: main.c
	gcc -c main.c

function_y1.o: function_y1.asm
	nasm function_y1.asm -f elf -o function_y1.o

function_y2.o: function_y2.c
	gcc -c -masm=intel function_y2.c
