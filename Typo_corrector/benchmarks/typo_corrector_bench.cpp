#include "../typo_corrector/dictionary/dictionary.hpp"
#include "../typo_corrector/typo_corrector.hpp"

#include <benchmark/benchmark.h> // NOLINT
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace s1ky; // NOLINT

constexpr size_t kMaxThreadsNum = 1 << 5;

struct TestClass
{
    TestClass()
    {
        std::string   filepath("../../benchmarks/war_and_peace_bench.txt");
        std::ifstream file(filepath);
        if (file.is_open())
        {
            std::string word;
            while (!file.eof())
            {
                file >> word;
                dictionary_.set_value(word, 0);
            }

            std::cout << "dictionary size : " << dictionary_.get_size() << "\n";
        }
        else
        {
            std::cout << filepath << " not found\n";
            exit(-1);
        }
    }

    void findWord(const std::string& word, size_t threads_nmb)
    {
        dictionary_.threads_number = threads_nmb;
        dictionary_.get_similar_word_thread(word);
    }

private:
    Dictionary dictionary_;
};

TestClass test;

//=================================================================================================================

static void SingleThread(benchmark::State& state)
{
    for (auto _ : state) { test.findWord("casully", 1); }
}
BENCHMARK(SingleThread)->Unit(benchmark::kMillisecond);

static void Paralleling(benchmark::State& state)
{
    for (auto _ : state) { test.findWord("casully", static_cast<size_t>(state.range())); }
}
BENCHMARK(Paralleling)->DenseRange(2, kMaxThreadsNum, 1)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN(); // NOLINT
