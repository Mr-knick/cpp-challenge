#!/bin/bash

mkdir build
cd build || exit
cmake .. -GNinja && ninja
cp ../tests/wordOccurrenceCounterTest.sh .
chmod +x wordOccurrenceCounterTest.sh
./wordOccurrenceCounterTest.sh