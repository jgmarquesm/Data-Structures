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
APP_NAME = app_array
LIB_NAME = array
ADT = array
TEST_ADT = array.test
UNITY = unity

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds
LIBS = -l$(LIB_NAME) -L $(MAIN)/$(LIB)

--private-create_folders:
	mkdir $(MAIN)/$(LIB)
	mkdir $(MAIN)/$(OBJ)
	mkdir $(MAIN)/$(BIN)
	mkdir $(TEST)/$(BIN)

--private-get_unity:
	cp ../../$(UNITY)/$(INCLUDE)/* $(MAIN)/$(INCLUDE)/
	cp ../../$(UNITY)/$(SRC)/* $(MAIN)/$(SRC)/

pack: clean_all --private-create_folders --private-get_unity \
	$(MAIN)/$(OBJ)/$(ADT).o
	ar -rcs $(MAIN)/$(LIB)/lib$(LIB_NAME).a $(MAIN)/$(OBJ)/*.o

compile_apps: $(MAIN)/$(BIN)/$(APP_NAME)

compile_test: $(MAIN)/$(OBJ)/$(ADT).o \
	$(MAIN)/$(OBJ)/$(UNITY).o \
 	$(TEST)/$(BIN)/$(TEST_ADT)

run_apps: pack compile_apps
	$(MAIN)/$(BIN)/$(APP_NAME)
	make clean_unity

run_tests: pack compile_test
	$(TEST)/$(BIN)/$(TEST_ADT)
	make clean_unity

clean_all: clean_libs clean_apps clean_test clean_unity

clean_libs:
	rm -rf $(MAIN)/$(OBJ) $(MAIN)/$(LIB)

clean_apps:
	rm -rf $(MAIN)/$(BIN)

clean_test:
	rm -rf $(TEST)/$(BIN)

clean_unity:
	rm -rf $(MAIN)/$(SRC)/unity.c
	rm -rf $(MAIN)/$(INCLUDE)/unity.h
	rm -rf $(MAIN)/$(INCLUDE)/unity_internals.h

$(MAIN)/$(OBJ)/%.o: $(MAIN)/$(SRC)/%.c $(MAIN)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(MAIN)/$(INCLUDE) -o $@

$(MAIN)/$(BIN)/%: $(MAIN)/$(APPS)/%.c
	gcc $(FLAGS) $< $(LIBS) -I $(MAIN)/$(INCLUDE) -o $@

$(TEST)/$(BIN)/%: $(TEST)/$(TESTS)/%.c
	gcc $(FLAGS) $< $(MAIN)/$(OBJ)/*.o -I $(MAIN)/$(INCLUDE) -o $@
