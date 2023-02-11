#!/bin/bash

LIB_PATH="./lib/libarray.so"
APP_PATH="./app"

if [ ! -f ${LIB_PATH} ]; then
    make buildlib
fi

cd ${APP_PATH} || exit

python3 ./main.py
