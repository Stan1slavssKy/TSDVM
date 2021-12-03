# To use cmake for queue project with all flags use this command:
# cmake .. -DADD_SANITIZERS=ON -DADD_CLANG_TIDY=ON -DADD_BENCHMARK=ON -DADD_STACK_IMPL_TESTING=OFF -DADD_LIST_IMPL_TESTING=OFF

cmake_minimum_required(VERSION 3.8)
project(Queque)
set(CMAKE_CXX_STANDART 11)

add_compile_options(
    #-Werror
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

    -fno-elide-constructors
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
        --checks=*;
        --format-style=file;
    )
endif()

if(ADD_BENCHMARK)
    add_subdirectory(benchmark)
endif()

if(ADD_STACK_IMPL_TESTING OR ADD_LIST_IMPL_TESTING)
    add_subdirectory(test)
endif()