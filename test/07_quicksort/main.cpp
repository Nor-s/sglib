#include <sglib.h>
#include <algorithm>

#include <benchmark/benchmark.h>
#include <random>
#include <iostream>
#include <functional>

#define TEST_DATA_SIZE 1'000
using namespace sglib::algorithm;

enum class DataType
{
	_ASC_SORTED_,
	_DESC_SORTED_,
	_SHUFFLED_
};

class TestData
{
public:
	static std::vector<int> create_asc_sorted_vector()
	{
		static std::vector<int> sorted_vec;
		if (sorted_vec.empty())
		{
			sorted_vec.resize(TEST_DATA_SIZE);
			for (size_t i = 0; i < TEST_DATA_SIZE; ++i)
			{
				sorted_vec[i] = i;
			}
		}
		return sorted_vec;
	}
	static std::vector<int> create_shuffle_vector()
	{
		static std::vector<int> shuffled_vec;
		if (shuffled_vec.empty())
		{
			shuffled_vec.resize(TEST_DATA_SIZE);
			for (size_t i = 0; i < TEST_DATA_SIZE; ++i)
			{
				shuffled_vec[i] = Random::RangeInt(0, TEST_DATA_SIZE);
			}
		}
		return shuffled_vec;
	}

	static std::vector<int> create_desc_sorted_vector()
	{
		static std::vector<int> sorted_vec;
		if (sorted_vec.empty())
		{
			sorted_vec = create_asc_sorted_vector();
			std::reverse(sorted_vec.begin(), sorted_vec.end());
		}
		return sorted_vec;
	}
	static std::vector<int> create(DataType type)
	{
		switch (type)
		{
			case DataType::_ASC_SORTED_:
				return create_asc_sorted_vector();
			case DataType::_DESC_SORTED_:
				return create_desc_sorted_vector();
			case DataType::_SHUFFLED_:
				return create_shuffle_vector();
		}
	}
};

using enum PivotSelectionMode;
using enum DataType;

template <DataType _DataType, PivotSelectionMode _Mode>
static void BM_quicksort(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		std::vector<int> vec = TestData::create(_DataType);
		QuickSort(vec.begin(), vec.end(), _Mode);
	}
}

BENCHMARK(BM_quicksort<_ASC_SORTED_, FIRST>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, LAST>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, MIDDLE>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, MEDIAN_OF_THREE>);
BENCHMARK(BM_quicksort<_ASC_SORTED_, RANDOM>);

BENCHMARK(BM_quicksort<_DESC_SORTED_, FIRST>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, LAST>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, MIDDLE>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, MEDIAN_OF_THREE>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, RANDOM>);

BENCHMARK(BM_quicksort<_SHUFFLED_, FIRST>);
BENCHMARK(BM_quicksort<_SHUFFLED_, LAST>);
BENCHMARK(BM_quicksort<_SHUFFLED_, MIDDLE>);
BENCHMARK(BM_quicksort<_SHUFFLED_, MEDIAN_OF_THREE>);
BENCHMARK(BM_quicksort<_SHUFFLED_, RANDOM>);

int main(int argc, char** argv)
{
	std::vector<std::string> args(argv, argv + argc);
	args.push_back("--benchmark_out=benchmark_results.csv");
	args.push_back("--benchmark_out_format=csv");

	std::vector<char*> c_args;
	for (auto& arg : args)
	{
		c_args.push_back(arg.data());
	}

	int new_argc = c_args.size();
	char** new_argv = c_args.data();

	::benchmark::Initialize(&new_argc, new_argv);
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
	return 0;
}