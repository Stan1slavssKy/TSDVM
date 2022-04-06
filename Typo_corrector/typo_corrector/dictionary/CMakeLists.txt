cmake_minimum_required(VERSION 3.8)
project(Typo_corrector)
set(CMAKE_CXX_STANDART 17)

add_library(dictionary STATIC dictionary.cpp)
target_include_directories(dictionary PUBLIC ../../hash_table)
