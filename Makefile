CFLAGS = -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
kernel:	boot.o main.o screen.o
	ld -T link.ld -o kernel boot.o main.o screen.o
boot.o: boot.asm
	nasm -f elf -o boot.o boot.asm
main.o: main.c
	gcc -Wall -O $(CFLAGS) -I. -c -o main.o main.c
screen.o:
	gcc -Wall -O $(CFLAGS) -I. -c -o screen.o screen.c

clean:
	rm -rf boot.o main.o screen.o kernel
