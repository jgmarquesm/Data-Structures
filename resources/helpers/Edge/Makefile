#helper
# Directories
MAIN = main
TEST = test
# Generics
BIN = bin
INCLUDE = include
LIB = lib
OBJ = obj
SRC = src
hp_FOLDER_0 = ../ExceptionHandler/$(MAIN)
#--ADD_FOLDER_NEW_hp

# Names Definition
LIB_NAME = E
HELPER = edge
TEST_HELPER = edge.test
UNITY = ../../unity
DEPS = ../../scripts/dependencies
INSTALL = install.sh
hp_0 = exception_handler
#--ADD_NEW_hp
#hp1

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
LIBS = -l$(LIB_NAME) -L $(MAIN)/$(LIB)

--private-create_folders:
	mkdir $(MAIN)/$(LIB)
	mkdir $(MAIN)/$(OBJ)
	mkdir $(TEST)/$(BIN)

--private-get_external_lib:
	cp $(hp_FOLDER_0)/$(SRC)/$(hp_0).c $(MAIN)/$(SRC)/
	cp $(hp_FOLDER_0)/$(INCLUDE)/$(hp_0).h $(MAIN)/$(INCLUDE)/
#--ADD_GET_NEW_LIB
	cp $(UNITY)/$(INCLUDE)/* $(MAIN)/$(INCLUDE)/
	cp $(UNITY)/$(SRC)/* $(MAIN)/$(SRC)/

pack: clean_all --private-create_folders --private-get_external_lib \
	$(MAIN)/$(OBJ)/$(HELPER).o \
	$(MAIN)/$(OBJ)/$(hp_0).o \
#--ADD_TO_PACK
	ar -rcs $(MAIN)/$(LIB)/lib$(LIB_NAME).a $(MAIN)/$(OBJ)/*.o

compile_test: $(MAIN)/$(OBJ)/$(HELPER).o \
	$(MAIN)/$(OBJ)/unity.o \
 	$(TEST)/$(BIN)/$(TEST_HELPER) \
	$(MAIN)/$(OBJ)/$(hp_0).o \
#--ADD_TO_COMPILE_TEST

run_tests: clean_all pack compile_test
	$(TEST)/$(BIN)/$(TEST_HELPER)
	make clean_all

install_helper:
	$(DEPS)/$(INSTALL) -h

install:
	$(DEPS)/$(INSTALL) -$(filter-out $@,$(MAKECMDGOALS))

clean_all: clean_libs clean_test clean_external

clean_libs:
	rm -rf $(MAIN)/$(OBJ) $(MAIN)/$(LIB)

clean_test:
	rm -rf $(TEST)/$(BIN)

clean_external:
	rm -rf $(MAIN)/$(SRC)/$(hp_0).c
	rm -rf $(MAIN)/$(INCLUDE)/$(hp_0).h
#--ADD_TO_CLEAN
	rm -rf $(MAIN)/$(SRC)/unity.c
	rm -rf $(MAIN)/$(INCLUDE)/unity.h
	rm -rf $(MAIN)/$(INCLUDE)/unity_internals.h

$(MAIN)/$(OBJ)/%.o: $(MAIN)/$(SRC)/%.c $(MAIN)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(MAIN)/$(INCLUDE) -o $@

$(TEST)/$(BIN)/%: $(TEST)/tests/%.c
	gcc $(FLAGS) $< $(MAIN)/$(OBJ)/*.o -I $(MAIN)/$(INCLUDE) -o $@

