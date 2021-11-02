cmake_minimum_required(VERSION 3.8)
project("StackLibrary" LANGUAGES CXX)

set(OUTPUT "stack_lib_output")

set(HEADER_FILES
    stack.hpp
    stack_impl.hpp
    stack_bool_impl.hpp
)

set(SOURCE_FILES
    main.cpp
)

add_executable(${OUTPUT} ${SOURCE_FILES})

set_target_properties(${OUTPUT} PROPERTIES
    CXX_STANDARD          20
    CXX_STANDARD_REQUIRED ON
)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

set(LIBRARY_NAME "stack")

add_library(${LIBRARY_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})