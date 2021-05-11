METHOD = newton

all: program
clean: 
	rm func.o task6.o
program: func.o task6.o
	gcc -m32 -o program func.o task6.o 
func.o: func.asm
	nasm -f elf32 -o func.o func.asm
task6.o: task6.c
	gcc -c -m32 -D $(METHOD) -o task6.o task6.c -lm