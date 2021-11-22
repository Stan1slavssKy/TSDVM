cmake_minimum_required(VERSION 3.8)
project("test" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(ADD_TESTING ON)

if(ADD_TESTING)
    set(OUTPUT test)
    set(RUN_TEST_NAME run_${OUTPUT})

    include(FetchContent)
    FetchContent_Declare(
        googletest QUIET
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(BUILD_GTEST ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(${OUTPUT} queue_test.cpp)

    target_link_libraries(${OUTPUT} gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${OUTPUT})

    add_custom_target(${RUN_TEST_NAME} 
        COMMENT "Running tests to queue"
        COMMAND ./${OUTPUT}
    )

    add_dependencies(${RUN_TEST_NAME} ${OUTPUT})

    if(ADD_SANITIZERS)
        message("-- [Build with sanitizers]")
        target_compile_options(${OUTPUT} PUBLIC -fsanitize=address -g)
        set_target_properties(${OUTPUT}  PROPERTIES LINK_FLAGS "-fsanitize=address")
    endif()

    set_target_properties(${OUTPUT} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    )

endif()