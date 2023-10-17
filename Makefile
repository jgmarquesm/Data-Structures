MAIN = main
HELPERS = resources/helpers
ARRAY = $(MAIN)/Array
SLL = $(MAIN)/SinglyLinkedList
DLL = $(MAIN)/DoublyLinkedList
CDLL = $(MAIN)/CircularDoublyLinkedList
SS = $(MAIN)/StaticStack
DS = $(MAIN)/DynamicStack
SQ = $(MAIN)/StaticQueue
DQ = $(MAIN)/DynamicQueue
MAT = $(MAIN)/Matrix
UWG1 = $(MAIN)/UndirectedWeightedGraph1
UWG2 = $(MAIN)/UndirectedWeightedGraph2
#--NEW_DS_DIR
EH = $(HELPERS)/ExceptionHandler
N = $(HELPERS)/Node
V = $(HELPERS)/Vertex
E = $(HELPERS)/Edge
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
CREATE_SCRIPT = create/create.sh

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
ED10 = undirected_weighted_graph1
ED11 = undirected_weighted_graph2
#--ADD_NEW_DS
#DS12
H1 = exception_handler
H2 = node
H3 = vertex
H4 = edge
#--ADD_NEW_HELPER
#H5

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
	cp $(CDLL)/$(MAIN)/$(SRC)/$(ED4).c $(APP)/$(AUX)/$(SRC)
	cp $(SS)/$(MAIN)/$(SRC)/$(ED5).c $(APP)/$(AUX)/$(SRC)
	cp $(DS)/$(MAIN)/$(SRC)/$(ED6).c $(APP)/$(AUX)/$(SRC)
	cp $(SQ)/$(MAIN)/$(SRC)/$(ED7).c $(APP)/$(AUX)/$(SRC)
	cp $(DQ)/$(MAIN)/$(SRC)/$(ED8).c $(APP)/$(AUX)/$(SRC)
	cp $(MAT)/$(MAIN)/$(SRC)/$(ED9).c $(APP)/$(AUX)/$(SRC)
	cp $(UWG1)/$(MAIN)/$(SRC)/$(ED10).c $(APP)/$(AUX)/$(SRC)
	cp $(EH)/$(MAIN)/$(SRC)/$(H1).c $(APP)/$(AUX)/$(SRC)
	cp $(N)/$(MAIN)/$(SRC)/$(H2).c $(APP)/$(AUX)/$(SRC)
	cp $(V)/$(MAIN)/$(SRC)/$(H3).c $(APP)/$(AUX)/$(SRC)
	cp $(UWG2)/$(MAIN)/$(SRC)/$(ED11).c $(APP)/$(AUX)/$(SRC)
	cp $(E)/$(HELPERS)/$(SRC)/$(H4).c $(APP)/$(AUX)/$(SRC)
#--GET_SRC

--private-get_headers:
	cp $(ARRAY)/$(MAIN)/$(INCLUDE)/$(ED1).h $(APP)/$(INCLUDE)
	cp $(SLL)/$(MAIN)/$(INCLUDE)/$(ED2).h $(APP)/$(INCLUDE)
	cp $(DLL)/$(MAIN)/$(INCLUDE)/$(ED3).h $(APP)/$(INCLUDE)
	cp $(CDLL)/$(MAIN)/$(INCLUDE)/$(ED4).h $(APP)/$(INCLUDE)
	cp $(SS)/$(MAIN)/$(INCLUDE)/$(ED5).h $(APP)/$(INCLUDE)
	cp $(DS)/$(MAIN)/$(INCLUDE)/$(ED6).h $(APP)/$(INCLUDE)
	cp $(SQ)/$(MAIN)/$(INCLUDE)/$(ED7).h $(APP)/$(INCLUDE)
	cp $(DQ)/$(MAIN)/$(INCLUDE)/$(ED8).h $(APP)/$(INCLUDE)
	cp $(MAT)/$(MAIN)/$(INCLUDE)/$(ED9).h $(APP)/$(INCLUDE)
	cp $(UWG1)/$(MAIN)/$(INCLUDE)/$(ED10).h $(APP)/$(INCLUDE)
	cp $(EH)/$(MAIN)/$(INCLUDE)/$(H1).h $(APP)/$(INCLUDE)
	cp $(N)/$(MAIN)/$(INCLUDE)/$(H2).h $(APP)/$(INCLUDE)
	cp $(V)/$(MAIN)/$(INCLUDE)/$(H3).h $(APP)/$(INCLUDE)
	cp $(UWG2)/$(MAIN)/$(INCLUDE)/$(ED11).h $(APP)/$(INCLUDE)
	cp $(E)/$(HELPERS)/$(INCLUDE)/$(H4).h $(APP)/$(INCLUDE)
#--GET_H

--private-get_eds: --private-create_lib --private-get_srcs --private-get_headers

--private-clean_all:
	rm -rf $(APP)
	rm -rf *.tar.gz

--private-test: --private-clean_all
	$(SCRIPTS)/$(TEST_SCRIPT)

--private-test-debug-mode: --private-clean_all
	$(SCRIPTS)/$(TEST_SCRIPT) -d

--private-test-build-mode: --private-clean_all
	$(SCRIPTS)/$(TEST_SCRIPT) --build

.SILENT:
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
	$(APP)/$(AUX)/$(OBJ)/$(ED11).o \
	$(APP)/$(AUX)/$(OBJ)/$(H4).o \
#--ADD_TO_COMPILE
	ar -rcs $(APP)/$(LIB)/lib$(LIB_NAME).a $(APP)/$(AUX)/$(OBJ)/*.o
	rm -rf $(APP)/$(AUX)

.SILENT:
build: --private-test-build-mode --private-get_eds
	make compile

.SILENT:
create:
	$(SCRIPTS)/$(CREATE_SCRIPT) --$(filter-out $@,$(MAKECMDGOALS))

.SILENT:
create-ds:
	$(SCRIPTS)/$(CREATE_SCRIPT) -ds

.SILENT:
create-h:
	$(SCRIPTS)/$(CREATE_SCRIPT) -h

.SILENT:
pack: build
	tar -zcvf lib$(LIB_NAME).tar.gz $(APP)
	rm -rf $(APP)

.SILENT:
test: --private-test

.SILENT:
test-debug: --private-test-debug-mode

.SILENT:
check: --private-test-build-mode

b: build

p: pack

$(APP)/$(AUX)/$(OBJ)/%.o: $(APP)/$(AUX)/$(SRC)/%.c $(APP)/$(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(APP)/$(INCLUDE) -o $@
