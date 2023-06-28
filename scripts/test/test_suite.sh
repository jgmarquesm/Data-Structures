#!/bin/zsh

cd DSs1/Array && make clean_all && make run_tests && make clean_all
cd ../SinglyLinkedList && make clean_all && make run_tests && make clean_all
cd ../DoublyLinkedList && make clean_all && make run_tests && make clean_all
cd ../CircularDoublyLinkedList && make clean_all && make run_tests && make clean_all
cd ../StaticStack && make clean_all && make run_tests && make clean_all
cd ../DynamicStack && make clean_all && make run_tests && make clean_all
cd ../StaticQueue && make clean_all && make run_tests && make clean_all
cd ../DynamicQueue && make clean_all && make run_tests && make clean_all
