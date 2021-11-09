cmake_minimum_required(VERSION 3.8)
project("Stack" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    #-Wctor-dtor-privacy Why google test conflict with this  option?
    
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

file(GLOB_RECURSE ALL_SOURCES_FILES *.cpp *.hpp)
add_custom_target(
    clang_format
    COMMAND clang-format
    -i
    ${ALL_SOURCES_FILES}
)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    #-checks=*;
    --format-style=file;
    --header-filter=.hpp;
    -warnings-as-errors=*;
)

add_subdirectory(test)