#!/bin/zsh

TitleCaseConverter() {
    sed 's/.*/\L&/; s/[a-z]*/\u&/g' <<<"$1"
}

CreateApp() {
echo "#include <stdlib.h>

int main() {

    char *command = \"make run_tests\";
    int executed = system(command);
    if (executed != 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}" > DSs1/"$1"/main/apps/app_"$2".c
}

CreateHeader() {
echo "#ifndef ${3}_H
#define ${3}_H

typedef struct _${2} ${1};

#endif" > DSs1/"$1"/main/include/"$2".h
}

CreateSimpleSource() {
echo "#include \"../include/${2}.h\"

//typedef struct _${2} {
// define your DS here
//} ${1};" > DSs1/"$1"/main/src/"$2".c
}

CreateComplexSource() {
echo "#include \"../include/${2}.h\"
#include \"../include/${3}.h\"

//typedef struct _${2} {
// define your DS here
//} ${1};" > DSs1/"$1"/main/src/"$2".c
}

CreateTest () {
echo "#include \"../../main/include/unity.h\"
#include \"../../main/include/${2}.h\"

void setUp(){}

void tearDown(){}

// define a print function like: void (*type_print_function)(void * data)
// define a conversion function like: type (*type_convert_function)(void * data)
// define a comparison function like: int (*type_compare_function)(void *data1, void *data2)

void test_1() {
    TEST_MESSAGE(\"Please, write the tests.\");
    TEST_ASSERT_EQUAL(1, 0);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_1);
    // ...
    return UNITY_END();
}
" > DSs1/"$1"/test/tests/"$2".test.c
}

SimpleMake() {
  echo "# Directories
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
APP_NAME = app_${2}
LIB_NAME = ${3}
ADT = ${2}
TEST_ADT = ${2}.test
UNITY = unity

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
LIBS = -l\$(LIB_NAME) -L \$(MAIN)/\$(LIB)

--private-create_folders:
	mkdir \$(MAIN)/\$(LIB)
	mkdir \$(MAIN)/\$(OBJ)
	mkdir \$(MAIN)/\$(BIN)
	mkdir \$(TEST)/\$(BIN)

--private-get_unity:
	cp ../../\$(UNITY)/\$(INCLUDE)/* \$(MAIN)/\$(INCLUDE)/
	cp ../../\$(UNITY)/\$(SRC)/* \$(MAIN)/\$(SRC)/

pack: clean_all --private-create_folders --private-get_unity \
	\$(MAIN)/\$(OBJ)/\$(ADT).o
	ar -rcs \$(MAIN)/\$(LIB)/lib\$(LIB_NAME).a \$(MAIN)/\$(OBJ)/*.o

compile_apps: \$(MAIN)/\$(BIN)/\$(APP_NAME)

compile_test: \$(MAIN)/\$(OBJ)/\$(ADT).o \
	\$(MAIN)/\$(OBJ)/\$(UNITY).o \
 	\$(TEST)/\$(BIN)/\$(TEST_ADT)

run_apps: pack compile_apps
	\$(MAIN)/\$(BIN)/\$(APP_NAME)
	make clean_unity

run_tests: pack compile_test
	\$(TEST)/\$(BIN)/\$(TEST_ADT)
	make clean_unity

clean_all: clean_libs clean_apps clean_test clean_unity

clean_libs:
	rm -rf \$(MAIN)/\$(OBJ) \$(MAIN)/\$(LIB)

clean_apps:
	rm -rf \$(MAIN)/\$(BIN)

clean_test:
	rm -rf \$(TEST)/\$(BIN)

clean_unity:
	rm -rf \$(MAIN)/\$(SRC)/unity.c
	rm -rf \$(MAIN)/\$(INCLUDE)/unity.h
	rm -rf \$(MAIN)/\$(INCLUDE)/unity_internals.h

\$(MAIN)/\$(OBJ)/%.o: \$(MAIN)/\$(SRC)/%.c \$(MAIN)/\$(INCLUDE)/%.h
	gcc \$(FLAGS) -c \$< -I \$(MAIN)/\$(INCLUDE) -o \$@

\$(MAIN)/\$(BIN)/%: \$(MAIN)/\$(APPS)/%.c
	gcc \$(FLAGS) \$< \$(LIBS) -I \$(MAIN)/\$(INCLUDE) -o \$@

\$(TEST)/\$(BIN)/%: \$(TEST)/\$(TESTS)/%.c
	gcc \$(FLAGS) \$< \$(MAIN)/\$(OBJ)/*.o -I \$(MAIN)/\$(INCLUDE) -o \$@
" > DSs1/"$1"/Makefile
}

ComplexMake() {
echo "# Directories
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
BASE_ADT_FOLDER = ${3}

# Names Definition
APP_NAME = app_${2}
LIB_NAME = ${5}
ADT = ${2}
TEST_ADT = ${2}.test
UNITY = unity
BASE_ADT = ${4}

EXTERNAL = ../\${BASE_ADT_FOLDER}/main

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
LIBS = -l\$(LIB_NAME) -L \$(MAIN)/\$(LIB)

--private-create_folders:
\tmkdir \$(MAIN)/\$(LIB)
\tmkdir \$(MAIN)/\$(OBJ)
\tmkdir \$(MAIN)/\$(BIN)
\tmkdir \$(TEST)/\$(BIN)

--private-get_external_lib:
\tcp \$(EXTERNAL)/\$(SRC)/\$(BASE_ADT).c \$(MAIN)/\$(SRC)/
\tcp \$(EXTERNAL)/\$(INCLUDE)/\$(BASE_ADT).h \$(MAIN)/\$(INCLUDE)/
\tcp ../../\${UNITY}/\${INCLUDE}/* \${MAIN}/\${INCLUDE}/
\tcp ../../\${UNITY}/\${SRC}/* \${MAIN}/\${SRC}/

pack: clean_all --private-create_folders --private-get_external_lib \
  \$(MAIN)/\$(OBJ)/\$(ADT).o \
  \$(MAIN)/\$(OBJ)/\$(BASE_ADT).o
\tar -rcs \$(MAIN)/\$(LIB)/lib\$(LIB_NAME).a \$(MAIN)/\$(OBJ)/*.o

compile_apps: \$(MAIN)/\$(BIN)/\$(APP_NAME)

compile_test: \$(MAIN)/\$(OBJ)/\$(ADT).o \
  \$(MAIN)/\$(OBJ)/\$(BASE_ADT).o \
  \$(MAIN)/\$(OBJ)/\$(UNITY).o \
  \$(TEST)/\$(BIN)/\$(TEST_ADT)

run_apps: pack compile_apps
\t\$(MAIN)/\$(BIN)/\$(APP_NAME)
\tmake clean_external

run_tests: pack compile_test
\t\$(TEST)/\$(BIN)/\$(TEST_ADT)
\tmake clean_external

clean_all: clean_libs clean_apps clean_test clean_external

clean_libs:
\trm -rf \$(MAIN)/\$(OBJ) \$(MAIN)/\$(LIB)

clean_apps:
\trm -rf \$(MAIN)/\$(BIN)

clean_test:
\trm -rf \$(TEST)/\$(BIN)

clean_external:
\trm -rf \$(MAIN)/\$(SRC)/\$(BASE_ADT).c
\trm -rf \$(MAIN)/\$(SRC)/unity.c
\trm -rf \$(MAIN)/\$(INCLUDE)/\$(BASE_ADT).h
\trm -rf \$(MAIN)/\$(INCLUDE)/unity.h
\trm -rf \$(MAIN)/\$(INCLUDE)/unity_internals.h

\$(MAIN)/\$(OBJ)/%.o: \$(MAIN)/\$(SRC)/%.c \$(MAIN)/\$(INCLUDE)/%.h
\tgcc \$(FLAGS) -c \$< -I \$(MAIN)/\$(INCLUDE) -o \$@

\$(MAIN)/\$(BIN)/%: \$(MAIN)/\$(APPS)/%.c
\tgcc \$(FLAGS) \$< \$(LIBS) -I \$(MAIN)/\$(INCLUDE) -o \$@

\$(TEST)/\$(BIN)/%: \$(TEST)/\$(TESTS)/%.c
\tgcc \$(FLAGS) \$< \$(MAIN)/\$(OBJ)/*.o -I \$(MAIN)/\$(INCLUDE) -o \$@
" > DSs1/"$1"/Makefile
}

AppendOnTestScript() {
  echo "cd ../${1} && make clean_all && make run_tests && make clean_all || exit 1" >> ./scripts/test/build_test_suite.sh
  echo "cd ../${1} && make clean_all && make run_tests && make clean_all" >> ./scripts/test/test_suite.sh
}

echo 'Data Structure Name:'
read -r NAME

NAME="$(TitleCaseConverter "$NAME")"
LIB_NAME="$(echo "$NAME" | sed 's/\(.\)[^ ]* */\1/g' | tr '[:upper:]' '[:lower:]')"
LOWER_NAME="$(echo "${NAME//_/ }" | sed 's/\(.\)\([A-Z]\)/\1_\2/g' | tr '[:upper:]' '[:lower:]')"
NAME=${NAME//[[:space:]]/}
NAME=${NAME//_}
NAME=${NAME//-}
LOWER_NAME=${LOWER_NAME//[[:space:]]/}
LOWER_NAME=${LOWER_NAME//-}
UPPER_NAME="$(echo "${LOWER_NAME}" | tr '[:lower:]' '[:upper:]')"

mkdir DSs1/"$NAME"
mkdir DSs1/"$NAME"/main
mkdir DSs1/"$NAME"/main/apps
mkdir DSs1/"$NAME"/main/include
mkdir DSs1/"$NAME"/main/src
mkdir DSs1/"$NAME"/test
mkdir DSs1/"$NAME"/test/tests

echo "Does ${NAME} depend on another one in this package? (y/n)"
read -r COMPLEX_DS

case ${COMPLEX_DS:0:1} in
    y|Y )
        echo "arr) Array
sll ) Singly Linked List
dll ) Doubly Linked List
cdll) Circular Linked List
ss  ) Static Stack
ds  ) Dynamic Stack
sq  ) Static Queue
dq  ) Dynamic Queue
Which?"
        read -r SELECTION
        declare -l SELECTION

        case ${SELECTION} in
            arr )
              BASE_ADT="Array"
              LOWER_BASE_ADT="array"
            ;;
            sll )
              BASE_ADT="SinglyLinkedList"
              LOWER_BASE_ADT="singly_linked_list"
            ;;
            dll )
              BASE_ADT="DoublyLinkedList"
              LOWER_BASE_ADT="doubly_linked_list"
            ;;
            cdll )
              BASE_ADT="CircularDoublyLinkedList"
              LOWER_BASE_ADT="circular_doubly_linked_list"
            ;;
            ss )
              BASE_ADT="StaticStack"
              LOWER_BASE_ADT="static_stack"
            ;;
            ds )
              BASE_ADT="DynamicStack"
              LOWER_BASE_ADT="dynamic_stack"
            ;;
            sq )
              BASE_ADT="StaticQueue"
              LOWER_BASE_ADT="static_queue"
            ;;
            dq )
              BASE_ADT="DynamicQueue"
              LOWER_BASE_ADT="dynamic_queue"
            ;;
            * )
              rm -rf DSs1/"$NAME"
              echo "Invalid selection: ${SELECTION}."
              exit 1
            ;;
        esac

        ComplexMake "$NAME" "$LOWER_NAME" "$BASE_ADT" "$LOWER_BASE_ADT" "$LIB_NAME"
        CreateComplexSource "$NAME" "$LOWER_NAME" "$LOWER_BASE_ADT"
    ;;
    n|N )
      SimpleMake "$NAME" "$LOWER_NAME" "$LIB_NAME"
      CreateSimpleSource "$NAME" "$LOWER_NAME"
    ;;
    * )
        rm -rf DSs1/"$NAME"
        echo "Invalid selection: ${COMPLEX_DS}."
        exit 1
    ;;
esac

CreateApp "$NAME" "$LOWER_NAME"
CreateHeader "$NAME" "$LOWER_NAME" "$UPPER_NAME"
CreateTest "$NAME" "$LOWER_NAME"
AppendOnTestScript "$NAME"
