#!/bin/zsh

ARRAY="Array"
SLL="SinglyLinkedList"
DLL="DoublyLinkedList"
CLL="CircularDoublyLinkedList"
SS="StaticStack"
DS="DynamicStack"
SQ="StaticQueue"
DQ="DynamicQueue"

cd DSs1/$ARRAY && make clean_all && make run_tests && make clean_all || exit 1
cd ../$SLL && make clean_all && make run_tests && make clean_all || exit 1
cd ../$DLL && make clean_all && make run_tests && make clean_all || exit 1
cd ../$CLL && make clean_all && make run_tests && make clean_all || exit 1
cd ../$SS && make clean_all && make run_tests && make clean_all || exit 1
cd ../$DS && make clean_all && make run_tests && make clean_all || exit 1
cd ../$SQ && make clean_all && make run_tests && make clean_all || exit 1
cd ../$DQ && make clean_all && make run_tests && make clean_all || exit 1
