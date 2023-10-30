.PHONY: all clean objs run

# LD_LIBRARY_PATH := /usr/bin
# export LD_LIBRARY_PATH_1 = $(LD_LIBRARY_PATH)/libhello_shared.so
STATIC_EXE := result_static
SHARED_EXE := result_shared
CUR_DIR := .
INC_DIR := $(CUR_DIR)/include
OBJ_DIR := $(CUR_DIR)/objs
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src

LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC := $(LIB_DIR)/static
LIB_SHARED := $(LIB_DIR)/shared

INC_FLAGS := -I $(INC_DIR)

CREATE_OBJS_SHARED := -c -fPIC -o
CREATE_OBJS_STATIC := -c -o
CC := gcc

objs:
	@$(CC) -c -o $(OBJ_DIR)/hello_vietnam.o $(SRC_DIR)/hello_vietnam.c $(INC_FLAGS)
	@$(CC) -c -o $(OBJ_DIR)/hello_trungquoc.o $(SRC_DIR)/hello_trungquoc.c $(INC_FLAGS)
	@$(CC) -c -o $(OBJ_DIR)/main.o main.c $(INC_FLAGS)

objs_shared:
	@$(CC) $(CREATE_OBJS_SHARED) $(OBJ_DIR)/hello_anh.o $(SRC_DIR)/hello_anh.c $(INC_FLAGS)
	@$(CC) $(CREATE_OBJS_SHARED) $(OBJ_DIR)/hello_duc.o $(SRC_DIR)/hello_duc.c $(INC_FLAGS)
	@$(CC) $(CREATE_OBJS_SHARED) $(OBJ_DIR)/main.o main.c $(INC_FLAGS)
# Make static lib
mklibstatic: objs
	@ar rcs $(LIB_STATIC)/libhello_static.a $(OBJ_DIR)/hello_vietnam.o $(OBJ_DIR)/hello_trungquoc.o

all: mklibstatic
	@$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC) -lhello_static -o $(BIN_DIR)/$(STATIC_EXE)

run:
	@./$(BIN_DIR)/$(STATIC_EXE)

# Make shared lib
mklibshared:
	@$(CC) -shared $(OBJ_DIR)/main.o -o $(LIB_SHARED)/libhello_shared.so $(OBJ_DIR)/hello_anh.o $(OBJ_DIR)/hello_duc.o

install:
	@sudo install $(LIB_SHARED)/libhello_shared.so /usr/bin
	
all_shared: objs_shared mklibshared install
	@$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARED) -lhello_shared -o $(BIN_DIR)/$(SHARED_EXE)

run_shared:
	@./$(BIN_DIR)/$(SHARED_EXE)




clean:
	@rm -rf $(OBJ_DIR)/*
	@rm -rf $(BIN_DIR)/*
	@rm -rf $(LIB_SHARED)/*
	@rm -rf $(LIB_STATIC)/*