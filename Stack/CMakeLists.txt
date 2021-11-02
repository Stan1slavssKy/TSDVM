cmake_minimum_required(VERSION 3.8)
project("Stack" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(stack)
add_subdirectory(test)

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

#==========================================================================

set(ADD_SANITIZERS ON)

#==========================================================================

# add target clang_format for all cpp and hpp files in the project
file(GLOB_RECURSE ALL_SOURCES_FILES *.cpp *.hpp)
add_custom_target(
    clang_format
    COMMAND clang-format
    -i
    ${ALL_SOURCES_FILES}
)

set_target_properties(stack_test PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")


if(ADD_SANITIZERS)
    target_compile_options(${ALL_SOURCES_FILES} PUBLIC -fsanitize=address -g)
    set_target_properties(${ALL_SOURCES_FILES} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()