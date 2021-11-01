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
    --header-filter=*.h;
)
