.PHONY = all test clean

pipe:
	@gcc pipe.c
	@pipe.exe

clean: 
	rm -rf *.exe
