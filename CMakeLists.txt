cmake_minimum_required(VERSION 3.28.3)

project(cpp_challenge)

set(CMAKE_CXX_STANDARD 23)

set(SRC_FILES src/wordOccurrenceCounter.cxx)

include_directories(include/)

add_executable(wordOccurrenceCounter ${SRC_FILES})

#set(TEST_FILES test/)