cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 11)

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

set(STACK_OUTPUT stack_test)
set(LIST_OUTPUT list_test)

if(ADD_STACK_IMPL_TESTING)
    add_executable(${STACK_OUTPUT} queue_test.cpp ../stack_impl/stack/stack_bool.cpp)
    target_compile_definitions(${STACK_OUTPUT} PUBLIC -DSTACK_IMPL=1)
    target_link_libraries(${STACK_OUTPUT} gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${STACK_OUTPUT})

    if(ADD_SANITIZERS)
        target_compile_options(${STACK_OUTPUT} PUBLIC -fsanitize=address -g)
        set_target_properties(${STACK_OUTPUT}  PROPERTIES LINK_FLAGS "-fsanitize=address")
    endif()

    add_custom_target(run_${STACK_OUTPUT}
        COMMENT "Running tests to stack queue"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${STACK_OUTPUT}
    )
    add_dependencies(run_${STACK_OUTPUT} ${STACK_OUTPUT})
endif()

if(ADD_LIST_IMPL_TESTING)
    add_executable(${LIST_OUTPUT} queue_test.cpp)
    target_compile_definitions(${LIST_OUTPUT} PUBLIC -DLIST_IMPL=1)
    target_link_libraries(${LIST_OUTPUT} gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${LIST_OUTPUT})

    if(ADD_SANITIZERS)
        target_compile_options(${LIST_OUTPUT}  PUBLIC -fsanitize=address -g)
        set_target_properties(${LIST_OUTPUT}   PROPERTIES LINK_FLAGS "-fsanitize=address")
    endif()

    add_custom_target(run_${LIST_OUTPUT}
        COMMENT "Running tests to list queue"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${LIST_OUTPUT}
    )
    add_dependencies(run_${LIST_OUTPUT} ${LIST_OUTPUT})  
endif()
