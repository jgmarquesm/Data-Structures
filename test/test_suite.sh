#!/bin/zsh

ARRAY="Array"
SLL="SinglyLinkedList"
DLL="DoublyLinkedList"
CLL="CircularDoublyLinkedList"
SS="StaticStack"
DS="DynamicStack"
SQ="StaticQueue"
DQ="DynamicQueue"

cd DSs1/$ARRAY && make clean_all && make run_tests && make clean_all
cd ../$SLL && make clean_all && make run_tests && make clean_all
cd ../$DLL && make clean_all && make run_tests && make clean_all
cd ../$CLL && make clean_all && make run_tests && make clean_all
cd ../$SS && make clean_all && make run_tests && make clean_all
cd ../$DS && make clean_all && make run_tests && make clean_all
cd ../$SQ && make clean_all && make run_tests && make clean_all
cd ../$DQ && make clean_all && make run_tests && make clean_all
