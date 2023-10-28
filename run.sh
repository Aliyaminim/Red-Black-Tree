#!/bin/bash

rm -rf build
mkdir -p build
cd build/
#cmake ..
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
cd ..
cd ./build/test
./test1