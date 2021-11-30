#include <benchmark/benchmark.h>

#ifdef STACK_BENCHMARK
#include "../list_impl/queue_impl.hpp"
#endif

#ifdef LIST_BENCHMARK
#include "../stack_impl/queue/queue_impl.hpp"
#endif

#include "../stack_impl/queue/queue_impl.hpp"

static void push_in_queue(benchmark::State& state)
{
    for(auto _ : state)
    {
        s1ky::Queue<double> qu;
        
        for(size_t i = 0; i < state.range(0); i++)
        {
            qu.push(2.30);
        }
    }
}

BENCHMARK(push_in_queue)->RangeMultiplier(2)->Range(1 << 15, 1 << 20)->Unit(benchmark::kMillisecond);

static void pop_from_queue(benchmark::State& state)
{
    for (auto _ : state)
    {
        s1ky::Queue<double> qu;
        for (size_t i = 0; i < state.range(0); i++)
        {
            qu.push(1);
            qu.push(1);
            qu.pop();
        }
    }
}
BENCHMARK(pop_from_queue)->RangeMultiplier(2)->Range(1 << 15, 1 << 20)->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();