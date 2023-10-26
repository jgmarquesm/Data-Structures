#!/bin/zsh

# shellcheck disable=SC2034
GREY='\033[1;90m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[1;93m'
BLUE='\033[1;94m'
PURPLE='\033[1;95m'
CYAN='\033[1;96m'
WHITE='\033[1;97m'
NO_COLOR='\033[0m'

function _title_case_converter() {
    sed 's/.*/\L&/; s/[a-z]*/\u&/g' <<<"${1}"
}

function _title_to_pascal_case() {
  sed 's/_-/ /g; s/ //g' <<<"${1}"
}

function _title_case_to_snake_case() {
 # shellcheck disable=SC2001
 sed 's/[A-Z]/_\l&/g' <<<"${1}" | cut -c2-
}

function _get_dir_name() {
  TITLE_NAME="$(_title_case_converter "${1}")"
  # shellcheck disable=SC2005
  echo "$(_title_to_pascal_case "$TITLE_NAME")"
}

function _get_lib_name() {
  TITLE_NAME="$(_title_case_converter "${1}")"
  # shellcheck disable=SC2001
  sed 's/\(.\)[^ ]* */\1/g' <<<"${TITLE_NAME}"
}

function _get_lower_name() {
  DIR_NAME="$(_get_dir_name "${1}")"
  # shellcheck disable=SC2005
  echo "$(_title_case_to_snake_case "$DIR_NAME")"
}

function _get_upper_name() {
  LOWER_NAME="$(_get_lower_name "${1}")"
  # shellcheck disable=SC2005
  echo "$(echo "${LOWER_NAME}" | tr '[:lower:]' '[:upper:]')"
}

function _get_formatted_name() {
  dir_name=$(_get_dir_name "${1}")
  # shellcheck disable=SC2001
  formatted=$(echo "$dir_name" | sed 's/\([A-Z]\)/ \1/g')
  echo "$formatted"
}

function _get_Helpers_count() {
  # shellcheck disable=SC2012
  count=$(cd ./resources/helpers/ && ls | wc -l)
  echo "$count"
}

function CreateDir() {
  mkdir ./resources/helpers/"${1}"
  mkdir ./resources/helpers/"${1}"/main
  mkdir ./resources/helpers/"${1}"/main/include
  mkdir ./resources/helpers/"${1}"/main/src
  mkdir ./resources/helpers/"${1}"/test
  mkdir ./resources/helpers/"${1}"/test/tests
}

function CreateHeader() {
echo "#ifndef ${3}_H
#define ${3}_H
//#--ADD_TO_INCLUDE

#include <stdbool.h>
#include <stddef.h>

#ifdef __UNSORTED__
    #undef __UNSORTED__
#endif
#ifdef __ASC__
    #undef __ASC__
#endif
#ifdef __DESC__
    #undef __DESC__
#endif
#ifdef __DEFAULT_LONG__
    #undef __DEFAULT_LONG__
#endif
#ifdef __DEFAULT_SIZE_T__
    #undef __DEFAULT_SIZE_T__
#endif
#ifdef __DEFAULT_BOOL__
    #undef __DEFAULT_BOOL__
#endif
#ifdef __NOT_DEFAULT_BOOL__
    #undef __NOT_DEFAULT_BOOL__
#endif
#ifdef __DEFAULT_PTR__
    #undef __DEFAULT_PTR__
#endif
#ifdef __TYPE_COMPARE_FUNCTION_NAME__
    #undef __TYPE_COMPARE_FUNCTION_NAME__
#endif
#ifdef __TYPE_COMPARE_FUNCTION_SIGNATURE__
    #undef __TYPE_COMPARE_FUNCTION_SIGNATURE__
#endif
#ifdef __TYPE_PRINT_FUNCTION_NAME__
    #undef __TYPE_PRINT_FUNCTION_NAME__
#endif
#ifdef __TYPE_PRINT_FUNCTION_SIGNATURE__
    #undef __TYPE_PRINT_FUNCTION_SIGNATURE__
#endif

#define __UNSORTED__ 0
#define __ASC__ 1
#define __DESC__ -1
#define __DEFAULT_LONG__ -1
#define __DEFAULT_SIZE_T__ 0
#define __DEFAULT_BOOL__ false
#define __NOT_DEFAULT_BOOL__ true
#define __DEFAULT_PTR__ NULL
#define __TYPE_COMPARE_FUNCTION_NAME__ type_compare_func
#define __TYPE_COMPARE_FUNCTION_SIGNATURE__ int (*__TYPE_COMPARE_FUNCTION_NAME__)(void *data1, void *data2)
#define __TYPE_PRINT_FUNCTION_NAME__ type_print_func
#define __TYPE_PRINT_FUNCTION_SIGNATURE__ void (*__TYPE_PRINT_FUNCTION_NAME__)(void *data)

#define SIZE_OF_${3}_TYPE size_of_${2}_type

extern const size_t size_of_${2}_type;

typedef struct _${2} ${1};

#endif" > resources/helpers/"${1}"/main/include/"${2}".h
}

function CreateSource() {
echo "//#--ADD_TO_INCLUDE
#include \"../include/${2}.h\"

//typedef struct _${2} {
// define your DS here
//} ${1};

//const size_t size_of_${2}_type = sizeof(${1});" > resources/helpers/"${1}"/main/src/"${2}".c
}

function CreateTest() {
echo "#include \"../../main/include/unity.h\"
#include \"../../main/include/${2}.h\"

void setUp(){}

void tearDown(){}

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
" > resources/helpers/"${1}"/test/tests/"${2}".test.c
}

function CreateMakefile() {
  echo "#helper
# Directories
MAIN = main
TEST = test
# Generics
BIN = bin
INCLUDE = include
LIB = lib
OBJ = obj
SRC = src
#--ADD_FOLDER_NEW_hp

# Names Definition
LIB_NAME = ${3}
HELPER = ${2}
TEST_HELPER = ${2}.test
UNITY = ../../unity
DEPS = ../../scripts/dependencies
INSTALL = install.sh
#--ADD_NEW_hp
#hp0

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
LIBS = -l\$(LIB_NAME) -L \$(MAIN)/\$(LIB)

--private-create_folders:
	mkdir \$(MAIN)/\$(LIB)
	mkdir \$(MAIN)/\$(OBJ)
	mkdir \$(TEST)/\$(BIN)

--private-get_unity:
#--ADD_GET_NEW_LIB
	cp \$(UNITY)/\$(INCLUDE)/* \$(MAIN)/\$(INCLUDE)/
	cp \$(UNITY)/\$(SRC)/* \$(MAIN)/\$(SRC)/

pack: clean_all --private-create_folders --private-get_unity \\
	\$(MAIN)/\$(OBJ)/\$(HELPER).o \\
#--ADD_TO_PACK
	ar -rcs \$(MAIN)/\$(LIB)/lib\$(LIB_NAME).a \$(MAIN)/\$(OBJ)/*.o

compile_test: \$(MAIN)/\$(OBJ)/\$(HELPER).o \\
	\$(MAIN)/\$(OBJ)/unity.o \\
 	\$(TEST)/\$(BIN)/\$(TEST_HELPER) \\
#--ADD_TO_COMPILE_TEST

run_tests: clean_all pack compile_test
	\$(TEST)/\$(BIN)/\$(TEST_HELPER)
	make clean_all

install_helper:
	\$(DEPS)/\$(INSTALL) -h

install:
	\$(DEPS)/\$(INSTALL) -\$(filter-out \$@,\$(MAKECMDGOALS))

clean_all: clean_libs clean_test clean_unity

clean_libs:
	rm -rf \$(MAIN)/\$(OBJ) \$(MAIN)/\$(LIB)

clean_test:
	rm -rf \$(TEST)/\$(BIN)

clean_unity:
#--ADD_TO_CLEAN
	rm -rf \$(MAIN)/\$(SRC)/unity.c
	rm -rf \$(MAIN)/\$(INCLUDE)/unity.h
	rm -rf \$(MAIN)/\$(INCLUDE)/unity_internals.h

\$(MAIN)/\$(OBJ)/%.o: \$(MAIN)/\$(SRC)/%.c \$(MAIN)/\$(INCLUDE)/%.h
	gcc \$(FLAGS) -c \$< -I \$(MAIN)/\$(INCLUDE) -o \$@

\$(TEST)/\$(BIN)/%: \$(TEST)/tests/%.c
	gcc \$(FLAGS) \$< \$(MAIN)/\$(OBJ)/*.o -I \$(MAIN)/\$(INCLUDE) -o \$@
" > resources/helpers/"$1"/Makefile
echo "" > resources/helpers/"$1"/.info
}

function AddToTestScript() {
  sed -i~ "s#^) \#--H#${1}\n) \#--H#" ./resources/scripts/test/test_suite.sh
  sed -i~ "s#^) \#--H#${1}\n) \#--H#" ./resources/scripts/test/ci-test.sh
}

function SetNewHelper() {
  INDEX=$(_get_Helpers_count)
  LOWER=$(_get_lower_name "${1}")
  LIB=$(_get_lib_name "${1}")
  DIR=$(_get_dir_name "${1}")
  TITLE=$(_title_case_converter "${1}")
  sed -i~ "s#^\${NO_COLOR}\" \#--H#\${PURPLE}$INDEX \)\${WHITE} $TITLE\n\${NO_COLOR}\" \#--H#" ./resources/scripts/dependencies/install_helper.sh
  sed -i~ "s#^\#--ADD_NEW_OPT#\t\t$INDEX \) DEPENDENCY=\"$DIR\";;\n\#--ADD_NEW_HELPER_OPT#" ./resources/scripts/dependencies/install_helper.sh
  sed -i~ "s#^\(\#--NEW_HELPER_DIR\)#$LIB = \$\(HELPERS\)\/$DIR\n\#--NEW_HELPER_DIR#" Makefile
  sed -i~ "s#^\(\#--ADD_NEW_HELPER\)#H$INDEX = $LOWER\n\#--ADD_NEW_HELPER#" Makefile
  sed -i~ "s#^\#H$INDEX#\#H$(( INDEX + 1 ))#" Makefile
  sed -i~ "s#^\(\#--GET_SRC\)#\tcp \$\($LIB\)\/\$\(HELPERS\)\/\$\(SRC\)\/\$\(H$INDEX\).c \$\(APP\)\/\$\(AUX\)\/\$\(SRC\)\n\#--GET_SRC#" Makefile
  sed -i~ "s#^\(\#--GET_H\)#\tcp \$\($LIB\)\/\$\(HELPERS\)\/\$\(INCLUDE\)\/\$\(H$INDEX\).h \$\(APP\)\/\$\(INCLUDE\)\n\#--GET_H#" Makefile
  sed -i~ "s#^\(\#--ADD_TO_COMPILE\)#\t\$\(APP\)\/\$\(AUX\)\/\$\(OBJ\)\/\$\(H$INDEX\).o \\\\\n\#--ADD_TO_COMPILE#" Makefile
}

echo "${CYAN}Helper Name:${NO_COLOR}"
read -r NAME

LIB_NAME="$(_get_lib_name "$NAME")"
DIR_NAME="$(_get_dir_name "$NAME")"
LOWER_NAME="$(_get_lower_name "$NAME")"
UPPER_NAME="$(_get_upper_name "$NAME")"
FORMATTED_NAME="$(_get_formatted_name "$NAME")"

echo "${PURPLE}Scaffolding...${NO_COLOR}"
echo "${BLUE}Creating Directories...${NO_COLOR}"
CreateDir "$DIR_NAME"
echo "${BLUE}Creating${YELLOW}${FORMATTED_NAME} ${PURPLE}header${BLUE}...${NO_COLOR}"
CreateHeader "$DIR_NAME" "$LOWER_NAME" "$UPPER_NAME"
echo "${BLUE}Creating${YELLOW}${FORMATTED_NAME} ${PURPLE}initial source${BLUE}...${NO_COLOR}"
CreateSource "$DIR_NAME" "$LOWER_NAME"
echo "${BLUE}Creating${YELLOW}${FORMATTED_NAME} ${PURPLE}initial test${BLUE}...${NO_COLOR}"
CreateTest "$DIR_NAME" "$LOWER_NAME"
echo "${BLUE}Adding${YELLOW}${FORMATTED_NAME} ${BLUE}to ${PURPLE}test suite${BLUE}...${NO_COLOR}"
AddToTestScript "$DIR_NAME"
echo "${BLUE}Creating ${YELLOW}Makefile${BLUE}...${NO_COLOR}"
CreateMakefile "$DIR_NAME" "$LOWER_NAME" "$LIB_NAME"
echo "${WHITE}Setting new Helper...${NO_COLOR}"
SetNewHelper "$NAME"
echo "${GREEN}Finishing...${NO_COLOR}"
