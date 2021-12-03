#include "../list_impl/queue_impl.hpp"
#include <benchmark/benchmark.h>

using namespace s1ky::list_queue;

static void push_in_list_queue(benchmark::State& state)
{
    for (auto _ : state)
    {
        Queue<double> qu;

        for (size_t i = 0; i < state.range(0); i++) { qu.push(2.30); }
    }
}

BENCHMARK(push_in_list_queue)->RangeMultiplier(2)->Range(1 << 15, 1 << 20)->Unit(benchmark::kMillisecond);

static void pop_from_list_queue(benchmark::State& state)
{
    for (auto _ : state)
    {
        Queue<double> qu;
        for (size_t i = 0; i < state.range(0); i++)
        {
            qu.push(1);
            qu.push(1);
            qu.pop();
        }
    }
}
BENCHMARK(pop_from_list_queue)->RangeMultiplier(2)->Range(1 << 15, 1 << 20)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();