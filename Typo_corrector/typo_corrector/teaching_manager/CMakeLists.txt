cmake_minimum_required(VERSION 3.8)
project(Typo_corrector)
set(CMAKE_CXX_STANDART 17)

add_library(teaching_manager STATIC teaching_manager.cpp)
target_include_directories(teaching_manager PUBLIC ../../texts_for_teaching)
