# Directories
MAIN = ./main
TEST = ./test
# Generics
APPS = apps
TESTS = tests
BIN = bin
INCLUDE = include
LIB = lib
OBJ = obj
SRC = src

# Names Definition
APP_NAME = app_circular_doubly_linked_list
LIB_NAME = cdll
ADT = circular_doubly_linked_list
TEST_ADT = circular_doubly_linked_list.test
UNITY = unity

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds
LIBS = -l$(LIB_NAME) -L $(MAIN)/$(LIB)

pack: $(MAIN)/$(OBJ)/$(ADT).o
	ar -rcs $(MAIN)/$(LIB)/lib$(LIB_NAME).a $(MAIN)/$(OBJ)/*.o

compile_apps: clean_apps \
	$(MAIN)/$(BIN)/$(APP_NAME)

compile_test: $(MAIN)/$(OBJ)/$(ADT).o \
	$(MAIN)/$(OBJ)/$(UNITY).o \
	clean_test \
 	$(TEST)/$(BIN)/$(TEST_ADT)

run_apps: pack compile_apps
	$(MAIN)/$(BIN)/$(APP_NAME)

run_tests: compile_test
	$(TEST)/$(BIN)/$(TEST_ADT)

clean_all: clean_libs clean_apps clean_test

clean_libs:
	rm -rf $(MAIN)/$(OBJ)/* $(MAIN)/$(LIB)/*

clean_apps:
	rm -rf $(MAIN)/$(BIN)/*

clean_test:
	rm -rf $(TEST)/$(BIN)/*

$(MAIN)/$(OBJ)/%.o: $(MAIN)/$(SRC)/%.c $(MAIN)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(MAIN)/$(INCLUDE) -o $@

$(MAIN)/$(BIN)/%: $(MAIN)/$(APPS)/%.c
	gcc $(FLAGS) $< $(LIBS) -I $(MAIN)/$(INCLUDE) -o $@

$(TEST)/$(BIN)/%: $(TEST)/$(TESTS)/%.c
	gcc $(FLAGS) $< $(MAIN)/$(OBJ)/*.o -I $(MAIN)/$(INCLUDE) -o $@
