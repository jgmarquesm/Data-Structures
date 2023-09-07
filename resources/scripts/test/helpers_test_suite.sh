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

HELPERS=(
ExceptionHandler
Node
Vertex
)

function formatted_helper_name() {
  # shellcheck disable=SC2001
  formatted="$(echo "${1}" | sed 's/\([A-Z]\)/ \1/g')"
  echo "$formatted"
}

function run_test_suite() {
  cd resources/helpers/ || exit 1
  for helper in "${HELPERS[@]}"
  do
    formatted_helper=$(formatted_helper_name "${helper}")
    echo "${BLUE}Executing test for$formatted_helper...${NO_COLOR}"
    cd ./"${helper}" && make run_tests -s
    echo "${YELLOW}Test executed for$formatted_helper...${NO_COLOR}"
    cd ..
  done
}

clear
run_test_suite

echo "${PURPLE}Finishing for Helpers...${NO_COLOR}"
