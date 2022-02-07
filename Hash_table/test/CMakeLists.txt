cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)

#=========================================================================================

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

#=========================================================================================

set(HASH_TABLE_OUTPUT hash_table_test)

if(ADD_HASH_TABLE_TESTING)
    message("-- [Build hash table test]")

    add_executable(${HASH_TABLE_OUTPUT} hash_table_test.cpp)
    target_link_libraries(${HASH_TABLE_OUTPUT} gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${HASH_TABLE_OUTPUT})

    if(ADD_SANITIZERS)
        target_compile_options(${HASH_TABLE_OUTPUT} PUBLIC -fsanitize=address -g)
        set_target_properties(${HASH_TABLE_OUTPUT}  PROPERTIES LINK_FLAGS "-fsanitize=address")
    endif()

    add_custom_target(run_${HASH_TABLE_OUTPUT}
        COMMENT "Running tests to hash table"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${HASH_TABLE_OUTPUT}
    )

    add_dependencies(run_${HASH_TABLE_OUTPUT} ${HASH_TABLE_OUTPUT})
endif()