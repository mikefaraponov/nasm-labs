all: retranslate.o
	gcc retranslate.o -o retranslate
retranslate.o: retranslate.asm
	nasm -f elf -o retranslate.o retranslate.asm