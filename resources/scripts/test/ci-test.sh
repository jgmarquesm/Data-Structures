#!/bin/bash

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
) #--DS

HELPERS=(
ExceptionHandler
Node
Vertex
) #--H

function formatted_name() {
  # shellcheck disable=SC2001
  formatted="$(echo "${1}" | sed 's/\([A-Z]\)/ \1/g')"
  echo "$formatted"
}

function run_HELPER_test_suite() {
  cd ./resources/helpers/ || exit 1
  for helper in "${HELPERS[@]}"
  do
    formatted_helper=$(formatted_name "${helper}")
    echo "Executing test for$formatted_helper..."
    cd ./"${helper}" && make run_tests -s
    echo "Test executed for$formatted_helper..."
    cd ..
  done
}

function run_DS_test_suite() {
  cd ../../main/ || exit 1
  for ds in "${DS[@]}"
  do
    formatted_ds=$(formatted_name "${ds}")
    echo "Executing test for$formatted_ds..."
    cd ./"${ds}" && make run_tests -s || exit 1
    echo "Test executed for$formatted_ds..."
    cd ..
  done
}

clear
run_HELPER_test_suite
run_DS_test_suite

echo "Finishing..."
