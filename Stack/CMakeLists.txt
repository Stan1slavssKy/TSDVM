#########################################################################

# CMAKE MINIMAL VERSION
cmake_minimum_required (VERSION 3.8)

# PROJECT PROPERTIES
project ("Stack" LANGUAGES CXX)

#########################################################################

# EXECUTABLE FILE PROPERTIES
set(FILE_NAME "stack_output")

set(STACK_HEADERS
        stack/stack.hpp
        stack/stack_impl.hpp
        stack/stack_bool_impl.hpp
)

set(STACK_SOURCES
        stack/main.cpp
)

# EXECUTABLE FILE
add_executable(${FILE_NAME} ${STACK_SOURCES})

#########################################################################

# ASSEMBLY OPTIONS
set_target_properties(${FILE_NAME} PROPERTIES
    CXX_STANDARD          14
    CXX_STANDARD_REQUIRED ON
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

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
