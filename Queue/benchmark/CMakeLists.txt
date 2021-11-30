cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDART 11)

find_package(benchmark REQUIRED)

set(QUEUE_BENCHMARK queue_bench)

add_executable(${QUEUE_BENCHMARK} queue_impl_bench.cpp)
target_link_libraries(${QUEUE_BENCHMARK} benchmark::benchmark)

if(ADD_SANITIZERS)
    message("-- [Build with sanitizers]")
    target_compile_options(${QUEUE_BENCHMARK} PUBLIC -fsanitize=address -g)
    set_target_properties(${QUEUE_BENCHMARK}  PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()

add_custom_target(run_${QUEUE_BENCHMARK}
    COMMENT "Running benchmark for stack queue"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${QUEUE_BENCHMARK} 
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${QUEUE_BENCHMARK}
)

add_dependencies(run_${QUEUE_BENCHMARK} ${QUEUE_BENCHMARK})