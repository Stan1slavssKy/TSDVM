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

set(CORRECTOR_TEST_OUTPUT corrector_test)

add_executable(${CORRECTOR_TEST_OUTPUT} typo_corrector_test.cpp)
target_include_directories(${CORRECTOR_TEST_OUTPUT} PUBLIC typo_corrector)
target_link_libraries(${CORRECTOR_TEST_OUTPUT} typo_corrector gtest_main)

include(GoogleTest)
gtest_discover_tests(${CORRECTOR_TEST_OUTPUT})

if(ADD_SANITIZERS)
    message("-- [Build typo_corrector with sanitizers]")
    target_compile_options(${CORRECTOR_TEST_OUTPUT} PUBLIC -fsanitize=address -g)
    set_target_properties(${CORRECTOR_TEST_OUTPUT}  PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()

add_custom_target(run_${CORRECTOR_TEST_OUTPUT}
    COMMENT "Running tests to typo corrector"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${CORRECTOR_TEST_OUTPUT}
)

add_dependencies(run_${CORRECTOR_TEST_OUTPUT} ${CORRECTOR_TEST_OUTPUT})
