#!/usr/bin/env bash

mkdir build
cd build
cmake ../ -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$PWD/../
cd ..
cmake --build build -- -j32
