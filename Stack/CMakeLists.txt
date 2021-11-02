cmake_minimum_required(VERSION 3.8)
project("Stack" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(stack)
add_subdirectory(test)

file(GLOB_RECURSE ALL_SOURCES_FILES *.cpp *.hpp)
add_custom_target(
    clang_format
    COMMAND clang-format
    -i
    ${ALL_SOURCES_FILES}
)