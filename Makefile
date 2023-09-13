MAIN = main
HELPERS = resources/helpers
ARRAY = $(MAIN)/Array
SLL = $(MAIN)/SinglyLinkedList
DLL = $(MAIN)/DoublyLinkedList
CLL = $(MAIN)/CircularDoublyLinkedList
SS = $(MAIN)/StaticStack
DS = $(MAIN)/DynamicStack
SQ = $(MAIN)/StaticQueue
DQ = $(MAIN)/DynamicQueue
MAT = $(MAIN)/Matrix
UWG = $(MAIN)/UndirectedWeightedGraph
#--NEW_DS_DIR
EH = $(HELPERS)/ExceptionHandler
N = $(HELPERS)/Node
V = $(HELPERS)/Vertex
#--NEW_HELPER_DIR

APP = LIBDS
AUX = aux
LIB = lib
INCLUDE = include
SRC = src
OBJ = obj

LIB_NAME = ds

SCRIPTS = resources/scripts
TEST_SCRIPT = test/test_suite.sh
BUILD_TEST_SCRIPT = test/build_test_suite.sh
CREATE_DS_SCRIPT = create/create_ds.sh
CREATE_HELPER_SCRIPT = create/create_helper.sh

# Data Structures
ED1 = array
ED2 = singly_linked_list
ED3 = doubly_linked_list
ED4 = circular_doubly_linked_list
ED5 = static_stack
ED6 = dynamic_stack
ED7 = static_queue
ED8 = dynamic_queue
ED9 = matrix
ED10 = undirected_weighted_graph
#--ADD_NEW_DS
#DS11
H1 = exception_handler
H2 = node
H3 = vertex
#--ADD_NEW_HELPER
#H4

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
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
	cp $(MAT)/$(MAIN)/$(SRC)/$(ED9).c $(APP)/$(AUX)/$(SRC)
	cp $(UWG)/$(MAIN)/$(SRC)/$(ED10).c $(APP)/$(AUX)/$(SRC)
	cp $(EH)/$(MAIN)/$(SRC)/$(H1).c $(APP)/$(AUX)/$(SRC)
	cp $(N)/$(MAIN)/$(SRC)/$(H2).c $(APP)/$(AUX)/$(SRC)
	cp $(V)/$(MAIN)/$(SRC)/$(H3).c $(APP)/$(AUX)/$(SRC)
#--GET_SRC

--private-get_headers:
	cp $(ARRAY)/$(MAIN)/$(INCLUDE)/$(ED1).h $(APP)/$(INCLUDE)
	cp $(SLL)/$(MAIN)/$(INCLUDE)/$(ED2).h $(APP)/$(INCLUDE)
	cp $(DLL)/$(MAIN)/$(INCLUDE)/$(ED3).h $(APP)/$(INCLUDE)
	cp $(CLL)/$(MAIN)/$(INCLUDE)/$(ED4).h $(APP)/$(INCLUDE)
	cp $(SS)/$(MAIN)/$(INCLUDE)/$(ED5).h $(APP)/$(INCLUDE)
	cp $(DS)/$(MAIN)/$(INCLUDE)/$(ED6).h $(APP)/$(INCLUDE)
	cp $(SQ)/$(MAIN)/$(INCLUDE)/$(ED7).h $(APP)/$(INCLUDE)
	cp $(DQ)/$(MAIN)/$(INCLUDE)/$(ED8).h $(APP)/$(INCLUDE)
	cp $(MAT)/$(MAIN)/$(INCLUDE)/$(ED9).h $(APP)/$(INCLUDE)
	cp $(UWG)/$(MAIN)/$(INCLUDE)/$(ED10).h $(APP)/$(INCLUDE)
	cp $(EH)/$(MAIN)/$(INCLUDE)/$(H1).h $(APP)/$(INCLUDE)
	cp $(N)/$(MAIN)/$(INCLUDE)/$(H2).h $(APP)/$(INCLUDE)
	cp $(V)/$(MAIN)/$(INCLUDE)/$(H3).h $(APP)/$(INCLUDE)
#--GET_H

--private-get_eds: --private-create_lib --private-get_srcs --private-get_headers

--private-clean_all:
	rm -rf $(APP)
	rm -rf *.tar.gz

--private-test: --private-clean_all
	$(SCRIPTS)/$(TEST_SCRIPT)

--private-build_test: --private-clean_all
	$(SCRIPTS)/$(BUILD_TEST_SCRIPT)

compile: $(APP)/$(AUX)/$(OBJ)/$(ED1).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED2).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED3).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED4).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED5).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED6).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED7).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED8).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED9).o \
	$(APP)/$(AUX)/$(OBJ)/$(ED10).o \
	$(APP)/$(AUX)/$(OBJ)/$(H1).o \
	$(APP)/$(AUX)/$(OBJ)/$(H2).o \
	$(APP)/$(AUX)/$(OBJ)/$(H3).o \
#--ADD_TO_COMPILE
	ar -rcs $(APP)/$(LIB)/lib$(LIB_NAME).a $(APP)/$(AUX)/$(OBJ)/*.o
	rm -rf $(APP)/$(AUX)

build: --private-build_test --private-get_eds
	make compile

create:
	$(SCRIPTS)/$(CREATE_DS_SCRIPT)

create-helper:
	$(SCRIPTS)/$(CREATE_HELPER_SCRIPT)

pack: build
	tar -zcvf lib$(LIB_NAME).tar.gz $(APP)
	rm -rf $(APP)

test: --private-test

check: --private-build_test

.SILENT:
b: build

.SILENT:
c: create

.SILENT:
ch: create-helper

.SILENT:
p: pack

t: test

$(APP)/$(AUX)/$(OBJ)/%.o: $(APP)/$(AUX)/$(SRC)/%.c $(APP)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(APP)/$(INCLUDE) -o $@
