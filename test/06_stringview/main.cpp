#include <sglib.h>
#include <string_view>
#include <benchmark/benchmark.h>
#include <iostream>

constexpr int TEST_COUNT = 1'000'000;

// https://stackoverflow.com/questions/40127965/how-exactly-is-stdstring-view-faster-than-const-stdstring
std::string remove_prefix(const std::string& str)
{
	return str.substr(3);
}

std::string_view remove_prefix(std::string_view str)
{
	str.remove_prefix(3);
	return str;
}

static void BM_remove_prefix_string(benchmark::State& state)
{
	std::string example{"asfaghdfgsghasfasg3423rfgasdg"};
	while (state.KeepRunning())
	{
		auto res = remove_prefix(example);
		if (res != "aghdfgsghasfasg3423rfgasdg")
		{
			throw std::runtime_error("bad op");
		}
	}
}

static void BM_remove_prefix_string_view(benchmark::State& state)
{
	std::string_view example{"asfaghdfgsghasfasg3423rfgasdg"};
	while (state.KeepRunning())
	{
		auto res = remove_prefix(std::string_view(example));
		if (res != "aghdfgsghasfasg3423rfgasdg")
		{
			throw std::runtime_error("bad op");
		}
	}
}

void to_buffer_string_view(std::string_view str)
{
	std::stringstream buffer;
	buffer << str;
}

void to_buffer_string(const std::string& str)
{
	std::stringstream buffer;
	buffer << str;
}

static void BM_to_buffer_string_view_long(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		to_buffer_string_view(
			"This is a string long enough to avoid the std::string SBO "
			"----------------------------------------------------------------------");
	}
}
static void BM_to_buffer_string_long(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		to_buffer_string(
			"This is a string long enough to avoid the std::string SBO "
			"----------------------------------------------------------------------");
	}
}

static void BM_to_buffer_string_view_small(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		to_buffer_string_view("T");
	}
}
static void BM_to_buffer_string_small(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		to_buffer_string("T");
	}
}

BENCHMARK(BM_remove_prefix_string);
BENCHMARK(BM_remove_prefix_string_view);
BENCHMARK(BM_to_buffer_string_long);
BENCHMARK(BM_to_buffer_string_view_long);
BENCHMARK(BM_to_buffer_string_small);
BENCHMARK(BM_to_buffer_string_view_small);

BENCHMARK_MAIN();
