# Directories
MAIN = main
TEST = test
# Generics
BIN = bin
INCLUDE = include
LIB = lib
OBJ = obj
SRC = src
#--ADD_FOLDER_NEW_HELPER

# Names Definition
LIB_NAME = eh
ADT = exception_handler
TEST_ADT = exception_handler.test
UNITY = ../../unity
DEPS = ../../scripts/dependencies
#--ADD_NEW_HELPER
#H0

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
LIBS = -l$(LIB_NAME) -L $(MAIN)/$(LIB)

--private-create_folders:
	mkdir $(MAIN)/$(LIB)
	mkdir $(MAIN)/$(OBJ)
	mkdir $(TEST)/$(BIN)

--private-get_unity:
#--ADD_GET_NEW_LIB
	cp $(UNITY)/$(INCLUDE)/* $(MAIN)/$(INCLUDE)/
	cp $(UNITY)/$(SRC)/* $(MAIN)/$(SRC)/

pack: clean_all --private-create_folders --private-get_unity \
	$(MAIN)/$(OBJ)/$(ADT).o \
#--ADD_TO_PACK
	ar -rcs $(MAIN)/$(LIB)/lib$(LIB_NAME).a $(MAIN)/$(OBJ)/*.o

compile_test: $(MAIN)/$(OBJ)/$(ADT).o \
	$(MAIN)/$(OBJ)/unity.o \
	$(TEST)/$(BIN)/$(TEST_ADT) \
#--ADD_TO_COMPILE_TEST

run_tests: clean_all pack compile_test
	$(TEST)/$(BIN)/$(TEST_ADT)
	make clean_all

add_deps:
	$(DEPS)/add_deps.sh

get_deps:
	$(DEPS)/get_deps.sh

clean_all: clean_libs clean_test clean_unity

clean_libs:
	rm -rf $(MAIN)/$(OBJ) $(MAIN)/$(LIB)

clean_test:
	rm -rf $(TEST)/$(BIN)

clean_unity:
#--ADD_TO_CLEAN
	rm -rf $(MAIN)/$(SRC)/unity.c
	rm -rf $(MAIN)/$(INCLUDE)/unity.h
	rm -rf $(MAIN)/$(INCLUDE)/unity_internals.h

$(MAIN)/$(OBJ)/%.o: $(MAIN)/$(SRC)/%.c $(MAIN)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(MAIN)/$(INCLUDE) -o $@

$(TEST)/$(BIN)/%: $(TEST)/tests/%.c
	gcc $(FLAGS) $< $(MAIN)/$(OBJ)/*.o -I $(MAIN)/$(INCLUDE) -o $@

