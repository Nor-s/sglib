#include <sglib.h>
#include <algorithm>

#include <benchmark/benchmark.h>
#include <random>
#include <iostream>
#include <functional>

#define TEST_DATA_SIZE 1'000
using namespace sglib::algorithm;
using namespace sglib::data;

using enum PivotSelectionMode;
using enum DataType;

template <DataType _DataType>
static void BM_mergesort(benchmark::State& state)
{
	std::vector<int> raw_vec = TestData::Create(_DataType, TEST_DATA_SIZE);
	while (state.KeepRunning())
	{
		std::vector<int> temp_vec = raw_vec;
		StableSort(temp_vec.begin(), temp_vec.end());
	}
}

template <DataType _DataType, PivotSelectionMode _Mode>
static void BM_quicksort(benchmark::State& state)
{
	std::vector<int> raw_vec = TestData::Create(_DataType, TEST_DATA_SIZE);
	while (state.KeepRunning())
	{
		std::vector<int> temp_vec = raw_vec;
		QuickSort(temp_vec.begin(), temp_vec.end(), _Mode);
	}
}

template <DataType _DataType>
static void BM_insertsort(benchmark::State& state)
{
	std::vector<int> raw_vec = TestData::Create(_DataType, TEST_DATA_SIZE);
	while (state.KeepRunning())
	{
		std::vector<int> temp_vec = raw_vec;
		InsertSort(temp_vec.begin(), temp_vec.end());
	}
}

BENCHMARK(BM_mergesort<_ASC_SORTED_>);
BENCHMARK(BM_mergesort<_DESC_SORTED_>);
BENCHMARK(BM_mergesort<_DISORDER_>);

BENCHMARK(BM_quicksort<_ASC_SORTED_, MIDDLE>);
BENCHMARK(BM_quicksort<_DESC_SORTED_, MIDDLE>);
BENCHMARK(BM_quicksort<_DISORDER_, MIDDLE>);

BENCHMARK(BM_insertsort<_ASC_SORTED_>);
BENCHMARK(BM_insertsort<_DESC_SORTED_>);
BENCHMARK(BM_insertsort<_DISORDER_>);

BENCHMARK_MAIN();

// int main()
// {
// 	std::vector<int> temp_vec = TestData::Create(DataType::_DISORDER_, 13);
// 	for (auto a : temp_vec)
// 		std::cout << a << " ";
// 	std::cout << "\n";
// 	InsertSort(temp_vec.begin(), temp_vec.end());
// 	std::cout << "\n";
// 	for (auto a : temp_vec)
// 		std::cout << a << " ";
// 	std::cout << "\n";
// }