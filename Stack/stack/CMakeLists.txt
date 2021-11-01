
cmake_minimum_required(VERSION 3.8)

project("StackLibrary" LANGUAGES CXX)

set(OUTPUT "stack_library_output")

set(STACK_HEADERS
        stack.hpp
        stack_impl.hpp
        stack_bool_impl.hpp
)

set(SOURCES
        main.cpp
)

add_executable(${OUTPUT} ${SOURCES})

set(LIBRARY_NAME "stack")

add_library(${LIBRARY_NAME} STATIC ${SOURCES})

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

set_target_properties(${OUTPUT} PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")

if(ADD_SANITIZERS)
    target_compile_options(${OUTPUT} PUBLIC -fsanitize=address -g)
    set_target_properties(${OUTPUT} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()
