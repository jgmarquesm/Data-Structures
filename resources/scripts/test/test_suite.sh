#!/bin/zsh

DEBUG='off'
BUILD='off'

for opt in "$@"; do
    if [ "$opt" = "--debug" ] || [ "$opt" = "-d" ]; then
      DEBUG='on'
    elif [ "$opt" = "--build" ] || [ "$opt" = "-b" ]; then
      BUILD='on'
    fi
done

start=$(date +%s%N)

RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[1;93m'
BLUE='\033[1;94m'
PURPLE='\033[1;95m'
NO_COLOR='\033[0m'

HELPERS=(
ExceptionHandler
Node
Vertex
) #--H

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
UndirectedWeightedGraph1
) #--DS

function _delta_T_in_ms() {
  delta_t=$(( ($1 - $2)/1000000 ))
  echo "$delta_t"
}

function _get_executed_tests() {
  execs=0
  while read -r line
  do
    e="$( echo "$line" | grep -o -P "^\d+," | rev | cut -c2- | rev )"
    (( execs=execs+$(( e )) ))
  done < ../resources/scripts/test/temp_result.txt
  echo "$execs"
}

function _get_failed_tests() {
  fail=0
  while read -r line
  do
    f="$( echo "$line" | grep -o -P ",\d+$" | cut -c2-)"
    (( fail=fail+$(( f )) ))
  done < ../resources/scripts/test/temp_result.txt
  echo "$fail"
}

function _parse_test_result() {
  sed -i~ -E 's/(.+) Tests (.+) Failures/\1,\2/g' ../resources/scripts/test/temp_result.txt
}

function _title_case_to_snake_case() {
 # shellcheck disable=SC2001
 sed 's/[A-Z]/_\l&/g' <<<"${1}" | cut -c2-
}

function set_suppress_print_error_on() {
  helper=${HELPERS[1]}
  header_file=$(_title_case_to_snake_case "${helper}")
  sed -i~ 's#^\#define __SUPPRESS_PRINT_ERROR__ false#\#define __SUPPRESS_PRINT_ERROR__ true#' ./resources/helpers/"${helper}"/main/include/"${header_file}".h
}

function set_suppress_print_error_off() {
    helper=${HELPERS[1]}
    header_file=$(_title_case_to_snake_case "${helper}")
    sed -i~ 's#^\#define __SUPPRESS_PRINT_ERROR__ true#\#define __SUPPRESS_PRINT_ERROR__ false#' ../resources/helpers/"${helper}"/main/include/"${header_file}".h
}

function formatted_name() {
  # shellcheck disable=SC2001
  formatted="$(echo "${1}" | sed 's/\([A-Z]\)/ \1/g')"
  echo "$formatted"
}

function run_HELPERS_test_suite() {
  cd ./resources/helpers/ || exit 1
    for helper in "${HELPERS[@]}"
    do
      start_for_helper=$(date +%s%N)
      formatted_helper=$(formatted_name "${helper}")
      echo "${BLUE}Executing test for$formatted_helper...${NO_COLOR}"
      cd ./"${helper}" || exit 1
      if [[ $BUILD = "on" ]]; then
        make run_tests -s || exit 1
      else
        if [[ $DEBUG = "on" ]]; then
          make run_tests -s
        fi
        make run_tests -s | grep -o -P '\d+ Test(?:|s) (?:\d+ Failures)' >> ../../scripts/test/temp_result.txt
      fi
      cd ..
      end_for_helper=$(date +%s%N)
      echo "${YELLOW}Test executed for$formatted_helper in $(_delta_T_in_ms "$end_for_helper" "$start_for_helper")ms...${NO_COLOR}"
    done
}

function run_DS_test_suite() {
  cd ../../main/ || exit 1
  for ds in "${DS[@]}"
  do
    start_for_ds=$(date +%s%N)
    formatted_ds=$(formatted_name "${ds}")
    echo "${BLUE}Executing test for$formatted_ds...${NO_COLOR}"
    cd ./"${ds}" || exit 1
    if [[ $BUILD = "on" ]]; then
      make run_tests -s || exit 1
    else
      if [[ $DEBUG = "on" ]]; then
        make run_tests -s
      fi
      make run_tests -s | grep -o -P '\d+ Test(?:|s) (?:\d+ Failures)' >> ../../resources/scripts/test/temp_result.txt
    fi
    cd ..
    end_for_ds=$(date +%s%N)
    echo "${YELLOW}Test executed for$formatted_ds in $(_delta_T_in_ms "$end_for_ds" "$start_for_ds")ms...${NO_COLOR}"
  done
}

rm -rf ../resources/scripts/test/temp_result.txt
clear
set_suppress_print_error_on
run_HELPERS_test_suite
run_DS_test_suite
set_suppress_print_error_off

end=$(date +%s%N)
if [[ $BUILD = "on" ]]; then
  echo "${PURPLE}Tests executed in $(_delta_T_in_ms "$end" "$start")ms ${NO_COLOR}"
else
  _parse_test_result
  executed=$(_get_executed_tests)
  failed=$(_get_failed_tests)
  passed=$(( $executed - $failed ))
  echo "${BLUE}${executed} Tests executed in $(_delta_T_in_ms "$end" "$start")ms ${NO_COLOR}
${GREEN}${passed} Pass${NO_COLOR}
${RED}${failed} Fail${NO_COLOR}"
  rm -rf ../resources/scripts/test/temp_result.txt
fi
