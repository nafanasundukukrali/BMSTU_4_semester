#!/bin/bash

export LD_RUN_PATH=D_RUN_PATH:./lib
export LD_LIBRARY_PATH=D_LIBRARY_PATH:./lib

if [ "$1" == "debug" ] || [ "$1" == "valgrind" ]; then
	make clean
	make utestlib mode=debug

	if [ "$1" == "valgrind" ]; then
		valgrind --tool=memcheck ./lib_unit_tests.exe
	else
		gdb ./lib_unit_tests.exe
	fi
else
    	make utestlib 
	./lib_unit_tests.exe
fi
