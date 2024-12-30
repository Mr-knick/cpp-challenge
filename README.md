cpp-challenge
================

Program name wordOccurrenceCounter *previously buggy.cxx* will read in SDTIO creating a word list with a count, print said list, then track all calls to the list for number of hits.  

Requirements
------------

- C++23 compiler
- CMake 3.28 or later
- Ninja build system
- Valgrind

Installation
------------

1. Unzip project at desired location
2. Run ./checkAndInstallDependencies.sh from project root.

Build and Test
-----

1. Run ./buildAndTest.sh from project root
2. Verify all tests pass Note* Valgrind will require additional password

Running
-------

1. program is located in ${ProjectRoot}/build
2. run ./wordOccurrenceCounter to start program
3. Once running any word typed into the console (or inserted into STDIO) will be logged into the word list. Only the first word in a line will be counted.
4. Once the word "end" is detected the list of words and their count will be printed to screen.
5. Any word typed now will poll the word list for its count
6. Once EOF is detected (typed via Cntr+d) it will leave the polling and print out number of successful poll operations. 
