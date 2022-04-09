cmake_minimum_required(VERSION 3.16.3)
project(Typo_corrector)
set(CMAKE_CXX_STANDART 17)

add_library(typo_corrector STATIC typo_corrector.cpp)

target_include_directories(typo_corrector PUBLIC dictionary teaching_manager)

target_link_libraries(typo_corrector dictionary teaching_manager)

add_subdirectory(dictionary)
add_subdirectory(teaching_manager)
