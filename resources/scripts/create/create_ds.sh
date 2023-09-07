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

function TitleCaseConverter() {
    sed 's/.*/\L&/; s/[a-z]*/\u&/g' <<<"${1}"
}

function TitleToPascalCase() {
  sed 's/_-/ /g; s/ //g' <<<"${1}"
}

function TitleCaseTo_snake_case() {
 # shellcheck disable=SC2001
 sed 's/[A-Z]/_\l&/g' <<<"${1}" | cut -c2-
}

function _get_dir_name() {
  TITLE_NAME="$(TitleCaseConverter "${1}")"
  # shellcheck disable=SC2005
  echo "$(TitleToPascalCase "$TITLE_NAME")"
}

function _get_lib_name() {
  TITLE_NAME="$(TitleCaseConverter "${1}")"
  # shellcheck disable=SC2001
  sed 's/\(.\)[^ ]* */\1/g' <<<"${TITLE_NAME}"
}

function _get_lower_name() {
  DIR_NAME="$(_get_dir_name "${1}")"
  # shellcheck disable=SC2005
  echo "$(TitleCaseTo_snake_case "$DIR_NAME")"
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

function _get_DS_count() {
  # shellcheck disable=SC2012
  count=$(cd ./main/ && ls | wc -l)
  echo "$count"
}

function CreateDir() {
  mkdir ./main/"${1}"
  mkdir ./main/"${1}"/main
  mkdir ./main/"${1}"/main/apps
  mkdir ./main/"${1}"/main/include
  mkdir ./main/"${1}"/main/src
  mkdir ./main/"${1}"/test
  mkdir ./main/"${1}"/test/tests
}

function CreateHeader() {
echo "#ifndef ${3}_H
#define ${3}_H

typedef struct _${2} ${1};

#endif" > main/"${1}"/main/include/"${2}".h
}

function CreateSource() {
echo "#include \"../include/${2}.h\"
//#--ADD_TO_INCLUDE

//typedef struct _${2} {
// define your DS here
//} ${1};" > main/"${1}"/main/src/"${2}".c
}

function CreateApp() {
echo "#include <stdlib.h>

int main() {

    char *command = \"make run_tests\";
    int executed = system(command);
    if (executed != 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}" > main/"${1}"/main/apps/app_"${2}".c
}

function CreateTest() {
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
" > main/"${1}"/test/tests/"${2}".test.c
}

function CreateMakefile() {
  echo "# Directories
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
#--ADD_FOLDER_NEW_HELPER
#--ADD_FOLDER_NEW_DS

# Names Definition
APP_NAME = app_${2}
LIB_NAME = ${3}
DS = ${2}
TEST_DS = ${2}.test
UNITY = ../../resources/unity
DEPS = ../../resources/scripts/dependencies
#--ADD_NEW_HELPER
#--ADD_NEW_DS
#DS0
#H0

# Compilation Flags
FLAGS = -O3 -Wall -pedantic -Warray-bounds -Werror
LIBS = -l\$(LIB_NAME) -L \$(MAIN)/\$(LIB)

--private-create_folders:
	mkdir \$(MAIN)/\$(LIB)
	mkdir \$(MAIN)/\$(OBJ)
	mkdir \$(MAIN)/\$(BIN)
	mkdir \$(TEST)/\$(BIN)

--private-get_unity:
#--ADD_GET_NEW_LIB
	cp \$(UNITY)/\$(INCLUDE)/* \$(MAIN)/\$(INCLUDE)/
	cp \$(UNITY)/\$(SRC)/* \$(MAIN)/\$(SRC)/

pack: clean_all --private-create_folders --private-get_unity \\
	\$(MAIN)/\$(OBJ)/\$(DS).o \\
#--ADD_TO_PACK
	ar -rcs \$(MAIN)/\$(LIB)/lib\$(LIB_NAME).a \$(MAIN)/\$(OBJ)/*.o

compile_apps: \$(MAIN)/\$(BIN)/\$(APP_NAME)

compile_test: \$(MAIN)/\$(OBJ)/\$(DS).o \\
  \$(MAIN)/\$(OBJ)/unity.o \\
  \$(TEST)/\$(BIN)/\$(TEST_DS) \\
#--ADD_TO_COMPILE_TEST

run_apps: pack compile_apps
	\$(MAIN)/\$(BIN)/\$(APP_NAME)
	make clean_unity

run_tests: clean_all pack compile_test
	\$(TEST)/\$(BIN)/\$(TEST_DS)
	make clean_all

add_deps:
	\$(DEPS)/add_deps.sh

get_deps:
	\$(DEPS)/get_deps.sh

clean_all: clean_libs clean_apps clean_test clean_unity

clean_libs:
	rm -rf \$(MAIN)/\$(OBJ) \$(MAIN)/\$(LIB)

clean_apps:
	rm -rf \$(MAIN)/\$(BIN)

clean_test:
	rm -rf \$(TEST)/\$(BIN)

clean_unity:
#--ADD_TO_CLEAN
	rm -rf \$(MAIN)/\$(SRC)/unity.c
	rm -rf \$(MAIN)/\$(INCLUDE)/unity.h
	rm -rf \$(MAIN)/\$(INCLUDE)/unity_internals.h

\$(MAIN)/\$(OBJ)/%.o: \$(MAIN)/\$(SRC)/%.c \$(MAIN)/\$(INCLUDE)/%.h
	gcc \$(FLAGS) -c \$< -I \$(MAIN)/\$(INCLUDE) -o \$@

\$(MAIN)/\$(BIN)/%: \$(MAIN)/\$(APPS)/%.c
	gcc \$(FLAGS) \$< \$(LIBS) -I \$(MAIN)/\$(INCLUDE) -o \$@

\$(TEST)/\$(BIN)/%: \$(TEST)/\$(TESTS)/%.c
	gcc \$(FLAGS) \$< \$(MAIN)/\$(OBJ)/*.o -I \$(MAIN)/\$(INCLUDE) -o \$@" > main/"${1}"/Makefile
echo "" > main/"${1}"/.info
}

function AddToTestScript() {
  sed -i~ "s#^)#${1}\n)#" ./resources/scripts/test/test_suite.sh
  sed -i~ "s#^)#${1}\n)#" ./resources/scripts/test/build_test_suite.sh
}

function SetNewDS() {
  index=$(_get_DS_count)
  lower=$(_get_lower_name "${1}")
  lib=$(_get_lib_name "${1}")
  dir=$(_get_dir_name "${1}")
  title=$(TitleCaseConverter "${1}")
  sed -i~ "s#^\(\${NO_COLOR}\" \#--DS\)#\${PURPLE}$index\)\${WHITE} $title\n\${NO_COLOR}\" \#--DS#" ./resources/scripts/dependencies/add_deps.sh
  sed -i~ "s#^\#--ADD_NEW_OPT#\t\t\t\t$index \) NEW_DS_FOLDER=\"$dir\";;\n\#--ADD_NEW_OPT#" ./resources/scripts/dependencies/add_deps.sh
  sed -i~ "s#^\(\#--NEW_DS_DIR\)#$lib = \$\(MAIN\)\/$dir\n\#--NEW_DS_DIR#" Makefile
  sed -i~ "s#^\(\#--ADD_NEW_DS\)#ED$index = $lower\n\#--ADD_NEW_DS#" Makefile
  sed -i~ "s#^\#DS$index#\#DS$(( index + 1 ))#" Makefile
  sed -i~ "s#^\(\#--GET_SRC\)#\tcp \$\($lib\)\/\$\(MAIN\)\/\$\(SRC\)\/\$\(ED$index\).c \$\(APP\)\/\$\(AUX\)\/\$\(SRC\)\n\#--GET_SRC#" Makefile
  sed -i~ "s#^\(\#--GET_H\)#\tcp \$\($lib\)\/\$\(MAIN\)\/\$\(INCLUDE\)\/\$\(ED$index\).h \$\(APP\)\/\$\(INCLUDE\)\n\#--GET_H#" Makefile
  sed -i~ "s#^\(\#--ADD_TO_COMPILE\)#\t\$\(APP\)\/\$\(AUX\)\/\$\(OBJ\)\/\$\(ED$index\).o \\\\\n\#--ADD_TO_COMPILE#" Makefile
}

echo "${CYAN}Data Structure Name:${NO_COLOR}"
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
echo "${BLUE}Creating${YELLOW}${FORMATTED_NAME} ${PURPLE}initial application${BLUE}...${NO_COLOR}"
CreateApp "$DIR_NAME" "$LOWER_NAME"
echo "${BLUE}Creating${YELLOW}${FORMATTED_NAME} ${PURPLE}initial test${BLUE}...${NO_COLOR}"
CreateTest "$DIR_NAME" "$LOWER_NAME"
echo "${BLUE}Adding${YELLOW}${FORMATTED_NAME} ${BLUE}to ${PURPLE}test suite${BLUE}...${NO_COLOR}"
AddToTestScript "$DIR_NAME"
echo "${BLUE}Creating ${YELLOW}Makefile${BLUE}...${NO_COLOR}"
CreateMakefile "$DIR_NAME" "$LOWER_NAME" "$LIB_NAME"
echo "${WHITE}Setting new Data Structure...${NO_COLOR}"
SetNewDS "$NAME"
echo "${GREEN}Finishing...${NO_COLOR}"
