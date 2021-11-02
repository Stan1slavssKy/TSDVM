cmake_minimum_required(VERSION 3.8)
project("test" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

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
set(ADD_TESTING ON)

if(ADD_TESTING)
    set(TEST_TAGET_NAME stack_test)

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
        test
        stack_test.cpp
    )

    target_link_libraries(
        test
        gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(test)


    add_custom_target(${TEST_TAGET_NAME}
        COMMENT "Running tests to stack"
        COMMAND ./test
    )

    add_dependencies(${TEST_TAGET_NAME} test)
endif()