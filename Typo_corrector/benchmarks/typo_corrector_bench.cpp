#include "../typo_corrector/typo_corrector.hpp"

#include <benchmark/benchmark.h> // NOLINT
#include <cstdio>

using namespace s1ky; //NOLINT

void multithreaded_fix (size_t threads_nmb)
{
    Typo_corrector test_corrector(threads_nmb);
    test_corrector.start_correcting("../../benchmarks/war_and_peace_bench.txt", test_corrector.REPLACE_ALL);
    std::remove("../../benchmarks/war_and_peace_bench_output.txt");
}

static void BM_multithreaded_fix(benchmark::State& state) // NOLINT
{
    for (auto _ : state) // NOLINT
    {
        multithreaded_fix(static_cast<size_t>(state.range(0)));
    }
}

void one_threaded_fix (size_t threads_nmb)
{
    Typo_corrector test_corrector(threads_nmb);
    test_corrector.start_correcting("../../benchmarks/war_and_peace_bench.txt", test_corrector.REPLACE_ALL);
    std::remove("../../benchmarks/war_and_peace_bench_output.txt");
}

static void BM_one_threaded_fix(benchmark::State& state) // NOLINT
{
    for (auto _ : state) // NOLINT
    {
        one_threaded_fix(static_cast<size_t>(state.range(0)));
    }
}

BENCHMARK(BM_one_threaded_fix)->Arg(1)->Unit(benchmark::kMillisecond); // NOLINT
BENCHMARK(BM_multithreaded_fix)->RangeMultiplier(2)->DenseRange(2, 20, 1)->Unit(benchmark::kMillisecond); // NOLINT

BENCHMARK_MAIN(); // NOLINT