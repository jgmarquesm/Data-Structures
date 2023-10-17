# Directories
MAIN = main
TEST = test
# Generics
APPS = apps
TESTS = tests
BIN = bin
INCLUDE = include
LIB = lib
OBJ = obj
SRC = src
hp_FOLDER_0 = ../../resources/helpers/Node/$(MAIN)
hp_DEP_FOLDER_0_1 = ../../resources/helpers/ExceptionHandler/$(MAIN)
hp_FOLDER_1 = ../../resources/helpers/Edge/$(MAIN)
#--ADD_FOLDER_NEW_hp
ds_FOLDER_0 = ../CircularDoublyLinkedList/$(MAIN)
#--ADD_FOLDER_NEW_ds

# Names Definition
APP_NAME = app_undirected_weighted_graph2
LIB_NAME = UWG2
DS = undirected_weighted_graph2
TEST_DS = undirected_weighted_graph2.test
UNITY = ../../resources/unity
DEPS = ../../resources/scripts/dependencies
INSTALL = install.sh
hp_0 = node
hp_DEP_0_1 = exception_handler
hp_1 = edge
#--ADD_NEW_hp
ds_0 = circular_doubly_linked_list
#--ADD_NEW_ds
#ds1
#hp2

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
LIBS = -l$(LIB_NAME) -L $(MAIN)/$(LIB)

--private-create_folders:
	mkdir $(MAIN)/$(LIB)
	mkdir $(MAIN)/$(OBJ)
	mkdir $(MAIN)/$(BIN)
	mkdir $(TEST)/$(BIN)

--private-get_external_lib:
	cp $(ds_FOLDER_0)/$(SRC)/$(ds_0).c $(MAIN)/$(SRC)/
	cp $(ds_FOLDER_0)/$(INCLUDE)/$(ds_0).h $(MAIN)/$(INCLUDE)/
	cp $(hp_FOLDER_0)/$(SRC)/$(hp_0).c $(MAIN)/$(SRC)/
	cp $(hp_FOLDER_0)/$(INCLUDE)/$(hp_0).h $(MAIN)/$(INCLUDE)/
	cp $(hp_DEP_FOLDER_0_1)/$(SRC)/$(hp_DEP_0_1).c $(MAIN)/$(SRC)/
	cp $(hp_DEP_FOLDER_0_1)/$(INCLUDE)/$(hp_DEP_0_1).h $(MAIN)/$(INCLUDE)/
	cp $(hp_FOLDER_1)/$(SRC)/$(hp_1).c $(MAIN)/$(SRC)/
	cp $(hp_FOLDER_1)/$(INCLUDE)/$(hp_1).h $(MAIN)/$(INCLUDE)/
#--ADD_GET_NEW_LIB
	cp $(UNITY)/$(INCLUDE)/* $(MAIN)/$(INCLUDE)/
	cp $(UNITY)/$(SRC)/* $(MAIN)/$(SRC)/

pack: clean_all --private-create_folders --private-get_external_lib \
	$(MAIN)/$(OBJ)/$(DS).o \
	$(MAIN)/$(OBJ)/$(ds_0).o \
	$(MAIN)/$(OBJ)/$(hp_0).o \
	$(MAIN)/$(OBJ)/$(hp_DEP_0_1).o \
	$(MAIN)/$(OBJ)/$(hp_1).o \
#--ADD_TO_PACK
	ar -rcs $(MAIN)/$(LIB)/lib$(LIB_NAME).a $(MAIN)/$(OBJ)/*.o

compile_apps: $(MAIN)/$(BIN)/$(APP_NAME)

compile_test: $(MAIN)/$(OBJ)/$(DS).o \
  $(MAIN)/$(OBJ)/unity.o \
  $(TEST)/$(BIN)/$(TEST_DS) \
	$(MAIN)/$(OBJ)/$(ds_0).o \
	$(MAIN)/$(OBJ)/$(hp_0).o \
	$(MAIN)/$(OBJ)/$(hp_DEP_0_1).o \
	$(MAIN)/$(OBJ)/$(hp_1).o \
#--ADD_TO_COMPILE_TEST

run_apps: pack compile_apps
	$(MAIN)/$(BIN)/$(APP_NAME)
	make clean_external

run_tests: clean_all pack compile_test
	$(TEST)/$(BIN)/$(TEST_DS)
	make clean_all

install_ds:
	$(DEPS)/$(INSTALL) -ds

install_helper:
	$(DEPS)/$(INSTALL) -h

install:
	$(DEPS)/$(INSTALL) -$(filter-out $@,$(MAKECMDGOALS))

clean_all: clean_libs clean_apps clean_test clean_external

clean_libs:
	rm -rf $(MAIN)/$(OBJ) $(MAIN)/$(LIB)

clean_apps:
	rm -rf $(MAIN)/$(BIN)

clean_test:
	rm -rf $(TEST)/$(BIN)

clean_external:
	rm -rf $(MAIN)/$(SRC)/$(ds_0).c
	rm -rf $(MAIN)/$(INCLUDE)/$(ds_0).h
	rm -rf $(MAIN)/$(SRC)/$(hp_0).c
	rm -rf $(MAIN)/$(INCLUDE)/$(hp_0).h
	rm -rf $(MAIN)/$(SRC)/$(hp_DEP_0_1).c
	rm -rf $(MAIN)/$(INCLUDE)/$(hp_DEP_0_1).h
	rm -rf $(MAIN)/$(SRC)/$(hp_1).c
	rm -rf $(MAIN)/$(INCLUDE)/$(hp_1).h
#--ADD_TO_CLEAN
	rm -rf $(MAIN)/$(SRC)/unity.c
	rm -rf $(MAIN)/$(INCLUDE)/unity.h
	rm -rf $(MAIN)/$(INCLUDE)/unity_internals.h

$(MAIN)/$(OBJ)/%.o: $(MAIN)/$(SRC)/%.c $(MAIN)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(MAIN)/$(INCLUDE) -o $@

$(MAIN)/$(BIN)/%: $(MAIN)/$(APPS)/%.c
	gcc $(FLAGS) $< $(LIBS) -I $(MAIN)/$(INCLUDE) -o $@

$(TEST)/$(BIN)/%: $(TEST)/$(TESTS)/%.c
	gcc $(FLAGS) $< $(MAIN)/$(OBJ)/*.o -I $(MAIN)/$(INCLUDE) -o $@
