cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDART 11)

find_package(benchmark REQUIRED)

set(QUEUE_BENCHMARK run_queue_bench)
set(STACK_OUTPUT stack_bench)
set(LIST_OUTPUT list_bench)

add_executable(${STACK_OUTPUT} queue_list_bench.cpp)
target_link_libraries(${STACK_OUTPUT} benchmark::benchmark)
set_target_properties(${STACK_OUTPUT} PROPERTIES COMMENT "run stack impl bench")

add_executable(${LIST_OUTPUT} queue_stack_bench.cpp)
target_link_libraries(${LIST_OUTPUT} benchmark::benchmark)
set_target_properties(${LIST_OUTPUT} PROPERTIES COMMENT "run list impl bench")

add_custom_target(${QUEUE_BENCHMARK}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${STACK_OUTPUT}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${LIST_OUTPUT} 
)

add_dependencies(${QUEUE_BENCHMARK} ${STACK_OUTPUT} ${LIST_OUTPUT})

if(ADD_SANITIZERS)
    target_compile_options(${QUEUE_BENCHMARK}  PUBLIC -fsanitize=address -g)
    set_target_properties(${QUEUE_BENCHMARK}   PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()