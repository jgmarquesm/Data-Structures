#!/bin/bash

start=$(date +%s)

HELPERS=(
ExceptionHandler
Node
Vertex
Edge
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
UndirectedWeightedGraph2
) #--DS

function _title_case_to_snake_case() {
 # shellcheck disable=SC2001
 sed 's/[A-Z]/_\l&/g' <<<"${1}" | cut -c2-
}

function set_suppress_print_error_on() {
  helper=${HELPERS[0]}
  header_file=$(_title_case_to_snake_case "${helper}")
  sed -i~ 's#^\#define __SUPPRESS_PRINT_ERROR__ false#\#define __SUPPRESS_PRINT_ERROR__ true#' ./resources/helpers/"${helper}"/main/include/"${header_file}".h
}

function set_suppress_print_error_off() {
  helper=${HELPERS[0]}
  header_file=$(_title_case_to_snake_case "${helper}")
  sed -i~ 's#^\#define __SUPPRESS_PRINT_ERROR__ false#\#define __SUPPRESS_PRINT_ERROR__ true#' ../resources/helpers/"${helper}"/main/include/"${header_file}".h
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
    start_for_helper=$(date +%s)
    formatted_helper=$(formatted_name "${helper}")
    echo "Executing test for$formatted_helper..."
    cd ./"${helper}" || exit 1
    make run_tests -s || exit 1
    cd ..
    end_for_helper=$(date +%s)
    echo "Test executed for$formatted_helper in $(( end_for_helper - start_for_helper ))s..."
  done
}

function run_DS_test_suite() {
  cd ../../main/ || exit 1
  for ds in "${DS[@]}"
  do
    start_for_ds=$(date +%s)
    formatted_ds=$(formatted_name "${ds}")
    echo "Executing test for$formatted_ds..."
    cd ./"${ds}" || exit 1
    make run_tests -s || exit 1
    cd ..
    end_for_ds=$(date +%s)
    echo "Test executed for$formatted_ds in $(( end_for_ds - start_for_ds ))s..."
  done
}

clear
set_suppress_print_error_on
run_HELPERS_test_suite
run_DS_test_suite
set_suppress_print_error_off

end=$(date +%s)
echo "Tests executed in $(( end - start ))s"
