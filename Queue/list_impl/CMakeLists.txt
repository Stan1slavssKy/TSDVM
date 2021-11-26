cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDART 11)

set(TARGET_NAME list_impl_queue)

add_executable(${TARGET_NAME} main.cpp)

set(CLANG_TIDY_PROPERTIES 
    clang-tidy;
    --checks=*;
    --format-style=file;
    --header-filter=*.hpp;
)

if(ADD_CLANG_TIDY)
    message("-- [Build with clang tidy]")
    
    set_target_properties(${TARGET_NAME}
        PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_PROPERTIES}"
)
else()
    message("-- [Build without clang tidy]")

endif()