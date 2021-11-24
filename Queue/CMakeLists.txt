cmake_minimum_required(VERSION 3.8)
project(Queque)
set(CMAKE_CXX_STANDART 11)

add_compile_options(
    #-Werror
    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo

    -fno-elide-constructors
)

file(GLOB_RECURSE ALL_SOURCES_FILES *.cpp *.hpp)
add_custom_target(
    clang_format
    COMMAND clang-format
    -i
    ${ALL_SOURCES_FILES}
)

add_subdirectory(test)
add_subdirectory(list_impl)