#!/bin/bash

mkdir build
cd build || exit
cmake .. -GNinja && ninja
ctest