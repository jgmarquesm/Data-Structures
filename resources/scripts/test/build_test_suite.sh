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

DS=(
Array
SinglyLinkedList
DoublyLinkedList
CircularDoublyLinkedList
StaticStack
DynamicStack
StaticQueue
DynamicQueue
Matrix
UndirectedWeightedGraph
)

function formatted_ds_name() {
  # shellcheck disable=SC2001
  formatted="$(echo "${1}" | sed 's/\([A-Z]\)/ \1/g')"
  echo "$formatted"
}

function run_helpers_test_suite() {
  echo "${BLUE}Executing test for Helpers...${NO_COLOR}"
  resources/scripts/test/helpers_test_suite.sh
  echo "${BLUE}Executing test for Data Structures...${NO_COLOR}"
}

function run_test_suite() {
  cd main/ || exit 1
  for ds in "${DS[@]}"
  do
    formatted_ds=$(formatted_ds_name "${ds}")
    echo "${BLUE}Executing test for$formatted_ds...${NO_COLOR}"
    cd ./"${ds}" && make run_tests -s || exit 1
    echo "${YELLOW}Test executed for$formatted_ds...${NO_COLOR}"
    cd ..
  done
}

clear
run_helpers_test_suite
run_test_suite

echo "${PURPLE}Finishing...${NO_COLOR}"
