cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDART 11)

set(CLANG_TIDY list_impl_clang_tidy)

add_executable(${CLANG_TIDY} main.cpp)

set(CLANG_TIDY_PROPERTIES 
    clang-tidy;
    --checks=*;
    --format-style=file;
    --header-filter=*.hpp;
)

if(ADD_CLANG_TIDY)
    message("-- [Build with clang tidy in list impl]")
    
    set_target_properties(${CLANG_TIDY}
        PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_PROPERTIES}"
)
else()
    message("-- [Build without clang tidy]")

endif()