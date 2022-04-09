cmake_minimum_required(VERSION 3.16.3)
project(Typo_corrector)
set(CMAKE_CXX_STANDART 17)

add_compile_options(
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

    -fpermissive
    
    -fno-elide-constructors
    -g3
)

file(GLOB_RECURSE ALL_SOURCES_FILES *.cpp *.hpp)

add_custom_target(
    clang_format
    COMMAND clang-format
    -i
    ${ALL_SOURCES_FILES}
)

if(ADD_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        --format-style=file;
        --header-filter=*.hpp;
    )
    message("-- [Build with clang tidy]")
endif()

if(ADD_BENCH)
    set(RUNBENCH_OUT ${CMAKE_CURRENT_BINARY_DIR})
    add_subdirectory(benchmarks)
endif()

add_executable(corrector main.cpp)
target_include_directories(corrector PUBLIC typo_corrector)
target_link_libraries(corrector typo_corrector)

add_subdirectory(typo_corrector)
add_subdirectory(test)
