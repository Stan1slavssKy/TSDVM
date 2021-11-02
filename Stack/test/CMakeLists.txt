cmake_minimum_required(VERSION 3.8)
project("test" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(ADD_TESTING ON)
set(ADD_SANITIZERS ON)

if(ADD_TESTING)
    set(OUTPUT test)
    set(RUN_TEST_NAME run_${OUTPUT})

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(${OUTPUT} stack_test.cpp)

    target_link_libraries(${OUTPUT} gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${OUTPUT})

    add_custom_target(${RUN_TEST_NAME} 
        COMMENT "Running tests to stack"
        COMMAND ./${OUTPUT}
    )

    add_dependencies(${RUN_TEST_NAME} ${OUTPUT})

    if(ADD_SANITIZERS)
        target_compile_options(${OUTPUT} PUBLIC -fsanitize=address -g)
        set_target_properties(${OUTPUT}  PROPERTIES LINK_FLAGS "-fsanitize=address")
    endif()

    set_target_properties(${OUTPUT} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_CLANG_TIDY        clang-tidy;
                          -header-filter=.hpp;
                          -checks=*;
    )

endif()