.PHONY: clean handleSinal

EXE_DIR := ./exe

create_handleSinal:
	@gcc -o $(EXE_DIR)/handleSignal handleSignal.c

handleSignal: create_handleSinal
	@$(EXE_DIR)/handleSignal

createProcess:
	@gcc -o $(EXE_DIR)/run_createProcess createProcess.c
	@$(EXE_DIR)/run_createProcess

create_countParameter:
	@gcc -o $(EXE_DIR)/countParameter countParameter.c

countParameter: create_countParameter 
	@$(EXE_DIR)/countParameter test1

all: countParameter handleSignal
# Clear all execute file
clean:
	rm -rf ./exe/*