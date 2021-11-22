cmake_minimum_required(VERSION 3.8)
project(Queque)
set(CMAKE_CXX_STANDART 11)

add_compile_options(
    -Werror

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
)

file(GLOB_RECURSE ALL_SOURCES_FILES *.cpp *.hpp)
add_custom_target(
    clang_format
    COMMAND clang-format
    -i
    ${ALL_SOURCES_FILES}
)

if(ADD_CLANG_TIDY)
    message("-- [Build with clang tidy]")
    set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        --format-style=file;
        --header-filter=*.hpp;
)
else()
    message("-- [Build without clang tidy]")
endif()

add_subdirectory(test)