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

add_subdirectory(list_impl)
add_subdirectory(stack_impl)

if(ADD_STACK_IMPL_TESTING OR ADD_LIST_IMPL_TESTING)
    if(ADD_STACK_IMPL_TESTING)
        set(TESTING_IMPLIMINTATION STACK_IMPL)
        add_definitions(-DSTACK_IMPL=1)
        message("-- [Build with stack impl tests]")
    
    elseif(ADD_LIST_IMPL_TESTING)
        set(TESTING_IMPLIMINTATION ) 
        add_definitions(-DLIST_IMPL=1)
        message("-- [Build with list impl tests]")

    endif()

    add_subdirectory(test)
endif()