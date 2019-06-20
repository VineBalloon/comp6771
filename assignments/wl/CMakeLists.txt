cmake_minimum_required(VERSION 3.14)
project(wl)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wl
        BUILD
        lexicon.cpp
        lexicon.h
        main.cpp
        word_ladder.cpp
        word_ladder.h
        word_ladder_test.cpp)
