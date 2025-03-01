#ifndef SGLIB_DATA_TESTDATA_H
#define SGLIB_DATA_TESTDATA_H

#include <vector>

namespace sglib::data
{

enum class DataType
{
	_ASC_SORTED_,
	_DESC_SORTED_,
	_DISORDER_
};

class TestData
{
public:
	static std::vector<int> CreateAscSortedVector(size_t size);
	static std::vector<int> CreateDisorderVector(size_t size);
	static std::vector<int> CreateDescSortedVector(size_t size);
	static std::vector<int> Create(DataType type, size_t size = 1000);
};
}	 // namespace sglib::data

#endif