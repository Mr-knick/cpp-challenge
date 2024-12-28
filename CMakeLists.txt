cmake_minimum_required(VERSION 3.28.3)

project(cpp_challenge)

find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include/)

set(SRC_FILES
        src/wordOccurrenceCounter.cxx
        src/word_processing.cpp)

set(HDR_FILES
        include/word_processing.h)

set(TEST_FILES
        tests/word_processing_test.cpp)

add_executable(wordOccurrenceCounter ${SRC_FILES})

add_executable(word_processing_test ${TEST_FILES} ${SOURCES})

add_test(NAME WordProcessingTest COMMAND word_processing_test)

enable_testing()
