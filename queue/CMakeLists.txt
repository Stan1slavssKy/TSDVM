cmake_minimum_required(VERSION 3.8)
project("Queque")
set(CMAKE_CXX_STANDART 20)

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

set(OUTPUT queque)
set(SOURCE_FILES main.cpp)

add_executable(${OUTPUT} ${SOURCE_FILES})

set_target_properties(${OUTPUT} PROPERTIES
    CXX_STANDART 20
    CXX_STANDARD_REQUIRED ON
)

set(ADD_SANITIZERS ON)

if(ADD_SANITIZERS)
    message("-- [Build with sanitizers]")
    target_compile_options(${OUTPUT} PUBLIC -fsanitize=address -g)
    set_target_properties(${OUTPUT}  PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()