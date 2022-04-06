cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDART 11)

find_package(benchmark REQUIRED)

set(TYPO_CORRECTOR_OUTPUT typo_corrector_bench)
set(TYPO_CORRECTOR_BENCH run_corrector_bench)

add_executable(${TYPO_CORRECTOR_OUTPUT} typo_corrector_bench.cpp)
target_include_directories(${TYPO_CORRECTOR_OUTPUT} PUBLIC typo_corrector)
target_link_libraries(${TYPO_CORRECTOR_OUTPUT} typo_corrector benchmark::benchmark)

add_custom_target(${TYPO_CORRECTOR_BENCH}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${TYPO_CORRECTOR_OUTPUT}
)

add_dependencies(${TYPO_CORRECTOR_BENCH} ${TYPO_CORRECTOR_OUTPUT})

if(ADD_SANITIZERS)
    target_compile_options(${TYPO_CORRECTOR_OUTPUT} PUBLIC -fsanitize=address -g)
    set_target_properties(${TYPO_CORRECTOR_OUTPUT}  PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()
