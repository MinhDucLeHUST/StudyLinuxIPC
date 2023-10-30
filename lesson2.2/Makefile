.PHONY: run all clean

all:
	@gcc -o runfile main.c

run: all
	@./runfile

show: run
	@cat helloworld.txt

clean: 
#rm runfile
	rm -rf *.txt
	rm -rf *.o
