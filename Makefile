#FOLDERS
ARRAY = DSs1/Array
SLL = DSs1/SinglyLinkedList
DLL = DSs1/DoublyLinkedList
CLL = DSs1/CircularDoublyLinkedList
SS = DSs1/StaticStack
DS = DSs1/DynamicStack
SQ = DSs1/StaticQueue
DQ = DSs1/DynamicQueue
APP = LIBDS1
AUX = aux
MAIN = main
LIB = lib
INCLUDE = include
SRC = src
OBJ = obj
TEST = test

LIB_NAME = ds1
TEST_SCRIPT = test_suite.sh
BUILD_TEST_SCRIPT = build_test_suite.sh

# Data Structures
ED1 = array
ED2 = singly_linked_list
ED3 = doubly_linked_list
ED4 = circular_doubly_linked_list
ED5 = static_stack
ED6 = dynamic_stack
ED7 = static_queue
ED8 = dynamic_queue

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds
LIBS = -l$(LIB_NAME) -L $(LIB)

--private-create_lib:
	mkdir $(APP)
	mkdir $(APP)/$(INCLUDE)
	mkdir $(APP)/$(LIB)
	mkdir $(APP)/$(AUX)
	mkdir $(APP)/$(AUX)/$(SRC)
	mkdir $(APP)/$(AUX)/$(OBJ)

--private-get_srcs:
	cp $(ARRAY)/$(MAIN)/$(SRC)/$(ED1).c $(APP)/$(AUX)/$(SRC)
	cp $(SLL)/$(MAIN)/$(SRC)/$(ED2).c $(APP)/$(AUX)/$(SRC)
	cp $(DLL)/$(MAIN)/$(SRC)/$(ED3).c $(APP)/$(AUX)/$(SRC)
	cp $(CLL)/$(MAIN)/$(SRC)/$(ED4).c $(APP)/$(AUX)/$(SRC)
	cp $(SS)/$(MAIN)/$(SRC)/$(ED5).c $(APP)/$(AUX)/$(SRC)
	cp $(DS)/$(MAIN)/$(SRC)/$(ED6).c $(APP)/$(AUX)/$(SRC)
	cp $(SQ)/$(MAIN)/$(SRC)/$(ED7).c $(APP)/$(AUX)/$(SRC)
	cp $(DQ)/$(MAIN)/$(SRC)/$(ED8).c $(APP)/$(AUX)/$(SRC)

--private-get_headers:
	cp $(ARRAY)/$(MAIN)/$(INCLUDE)/$(ED1).h $(APP)/$(INCLUDE)
	cp $(SLL)/$(MAIN)/$(INCLUDE)/$(ED2).h $(APP)/$(INCLUDE)
	cp $(DLL)/$(MAIN)/$(INCLUDE)/$(ED3).h $(APP)/$(INCLUDE)
	cp $(CLL)/$(MAIN)/$(INCLUDE)/$(ED4).h $(APP)/$(INCLUDE)
	cp $(SS)/$(MAIN)/$(INCLUDE)/$(ED5).h $(APP)/$(INCLUDE)
	cp $(DS)/$(MAIN)/$(INCLUDE)/$(ED6).h $(APP)/$(INCLUDE)
	cp $(SQ)/$(MAIN)/$(INCLUDE)/$(ED7).h $(APP)/$(INCLUDE)
	cp $(DQ)/$(MAIN)/$(INCLUDE)/$(ED8).h $(APP)/$(INCLUDE)

--private-get_eds: --private-create_lib --private-get_srcs --private-get_headers

--private-clean_all:
	rm -rf $(APP)
	rm -rf *.tar.gz

--private-test: --private-clean_all
	$(TEST)/$(TEST_SCRIPT)

--private-build_test: --private-clean_all
	$(TEST)/$(BUILD_TEST_SCRIPT)

compile: $(APP)/$(AUX)/$(OBJ)/$(ED1).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED2).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED3).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED4).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED5).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED6).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED7).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED8).o
	ar -rcs $(APP)/$(LIB)/lib$(LIB_NAME).a $(APP)/$(AUX)/$(OBJ)/*.o
	rm -rf $(APP)/$(AUX)

build: --private-build_test --private-get_eds
	make compile

pack: build
	tar -zcvf lib$(LIB_NAME).tar.gz $(APP)
	rm -rf $(APP)

test: --private-test

$(APP)/$(AUX)/$(OBJ)/%.o: $(APP)/$(AUX)/$(SRC)/%.c $(APP)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(APP)/$(INCLUDE) -o $@
