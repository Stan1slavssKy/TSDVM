# Cmake minimal version
cmake_minimum_required(VERSION 3.8)

# project characteristics
project("StackLibrary" LANGUAGES CXX)

#=========================================================================
# executable file

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

#=========================================================================
# static library

set(LIBRARY_NAME "stack")

add_library(${LIBRARY_NAME} STATIC ${SOURCES})

#=========================================================================
# assembly options

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

#=========================================================================
# add clang-format

# file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
# add_custom_target(
#    clang_format
#    COMMAND clang-format
#    -i
#    ${ALL_SOURCE_FILES}
#)

