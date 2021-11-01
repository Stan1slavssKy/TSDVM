# Cmake minimal version
cmake_minimum_required(VERSION 3.8)

# project characteristics
project("Stack" LANGUAGES CXX)

add_subdirectory(stack)
add_subdirectory(test)

file(GLOB_RECURSE ALL_SOURCES_FILES *.cpp *.h)
add_custom_target(
    clang_format
    COMMAND clang-format
    -i
    ${ALL_SOURCES_FILES}
)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --format-style=file;
    --header-filter=*.hpp;
)

set_target_properties(${OUTPUT} PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")

if(ADD_SANITIZERS)
    target_compile_options(${OUTPUT} PUBLIC -fsanitize=address -g)
    set_target_properties(${OUTPUT} PROPERTIES LINK_FLAGS "-fsanitize=address")
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