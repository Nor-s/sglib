#ifndef SGLIB_DATA_TESTDATA_H
#define SGLIB_DATA_TESTDATA_H

#include <vector>

namespace sglib::data
{

enum class DataType
{
	_ASC_SORTED_,
	_DESC_SORTED_,
	_SHUFFLED_
};

class TestData
{
public:
	static std::vector<int> create_asc_sorted_vector(size_t size);
	static std::vector<int> create_shuffle_vector(size_t size);
	static std::vector<int> create_desc_sorted_vector(size_t size);
	static std::vector<int> create(DataType type, size_t size = 1000);
};
}	 // namespace sglib::data

#endif