#!/bin/bash

LIB_PATH="./lib"
export LD_RUN_PATH=$LD_RUN_PATH:${LIB_PATH}
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LIB_PATH}

if [ ! -f "./lib_unit_tests.exe" ]; then
    make utestlib 
fi

./lib_unit_tests.exe 
