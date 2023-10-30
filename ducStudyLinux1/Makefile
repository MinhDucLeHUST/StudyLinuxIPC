.PHONY: all run clean

CUR_DIR := .
LIB_DIR := $(CUR_DIR)/lib

step1:
	gcc -c -Wall -Werror -fPIC foo.c

step2:
	gcc -shared -o libfoo1.so foo.o

step3:
	gcc -L$(LIB_DIR) -Wall -o test main.c -lfoo1
#@$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC) -lhello_static -o $(BIN_DIR)/$(STATIC_EXE)

all: step1 step2 step3

run:
	./test

clean:
	rm -rf ./lib
