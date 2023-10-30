.PHONY: step1 step2 step3 step4 all clean

step1:
	gcc -E hello.c -o hello.i
step2:
	gcc -S hello.i -o hello.S
step3:
	gcc -c hello.S -o hello.o
step4:
	gcc -o hello hello.o

all:
	gcc -o hello hello.c

clean:
	rm -rf hello hello. hello.S hello.o
	rm -rf *.o

link:
	gcc -c -o main.o main.c
	gcc -c -o hello2.o hello2.c
	gcc -c -o hello3.o hello3.c
