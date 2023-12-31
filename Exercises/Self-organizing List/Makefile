# Directories
MAIN = ./main
TEST = ./test
APPS = apps
BIN = bin
INCLUDE = include
LIB = lib
OBJ = obj
SRC = src

# Names Definition
APP_NAME = products_self_organizing_linked_list
LIB_NAME = psoll
TEST_SCRIPT = run_tests.sh

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds
LIBS = -l$(LIB_NAME) -L $(MAIN)/$(LIB)

pack: $(MAIN)/$(OBJ)/product.o \
	$(MAIN)/$(OBJ)/self_organizing_linked_list.o
	ar -rcs $(MAIN)/$(LIB)/lib$(LIB_NAME).a $(MAIN)/$(OBJ)/*.o

compile_apps: clean_apps \
	$(MAIN)/$(BIN)/$(APP_NAME)

run_apps: pack compile_apps
	$(MAIN)/$(BIN)/$(APP_NAME)

run_tests: clean_test pack compile_apps
	$(TEST)/$(TEST_SCRIPT)

clean_all: clean_libs clean_apps clean_test

clean_libs:
	rm -rf $(MAIN)/$(OBJ)/* $(MAIN)/$(LIB)/*

clean_apps:
	rm -rf $(MAIN)/$(BIN)/*

clean_test:
	rm -rf $(TEST)/*.test $(TEST)/test_cases/out/*.res

$(MAIN)/$(OBJ)/%.o: $(MAIN)/$(SRC)/%.c $(MAIN)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(MAIN)/$(INCLUDE) -o $@

$(MAIN)/$(BIN)/%: $(MAIN)/$(APPS)/%.c
	gcc $(FLAGS) $< $(LIBS) -I $(MAIN)/$(INCLUDE) -o $@
