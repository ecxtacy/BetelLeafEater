#!/bin/bash

mkdir build && cd build

cmake ..

cmake --build . && cd ..

./build/BetelLeafEater