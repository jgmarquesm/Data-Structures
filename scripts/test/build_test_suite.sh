#!/bin/zsh

cd DSs1/Array && make clean_all && make run_tests && make clean_all || exit 1
cd ../SinglyLinkedList && make clean_all && make run_tests && make clean_all || exit 1
cd ../DoublyLinkedList && make clean_all && make run_tests && make clean_all || exit 1
cd ../CircularDoublyLinkedList && make clean_all && make run_tests && make clean_all || exit 1
cd ../StaticStack && make clean_all && make run_tests && make clean_all || exit 1
cd ../DynamicStack && make clean_all && make run_tests && make clean_all || exit 1
cd ../StaticQueue && make clean_all && make run_tests && make clean_all || exit 1
cd ../DynamicQueue && make clean_all && make run_tests && make clean_all || exit 1
