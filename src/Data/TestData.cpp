#include "Data/TestData.h"
#include "Algorithm/Random.h"

namespace sglib::data
{
std::vector<int> TestData::CreateAscSortedVector(size_t size)
{
	std::vector<int> sorted_vec;
	if (sorted_vec.empty())
	{
		sorted_vec.resize(size);
		for (int i = 0; i < size; ++i)
		{
			sorted_vec[i] = i;
		}
	}
	return sorted_vec;
}
std::vector<int> TestData::CreateDisorderVector(size_t size)
{
	std::vector<int> shuffled_vec;
	if (shuffled_vec.empty())
	{
		shuffled_vec.resize(size);
		for (int i = 0; i < size; ++i)
		{
			shuffled_vec[i] = algorithm::Random::RangeInt(0, static_cast<int>(size));
		}
	}
	return shuffled_vec;
}

std::vector<int> TestData::CreateDescSortedVector(size_t size)
{
	std::vector<int> sorted_vec;
	if (sorted_vec.empty())
	{
		sorted_vec.resize(size);
		for (int i = 0; i < size; ++i)
		{
			sorted_vec[i] = static_cast<int>(size) - i;
		}
	}
	return sorted_vec;
}
std::vector<int> TestData::Create(DataType type, size_t size)
{
	switch (type)
	{
		case DataType::_ASC_SORTED_:
			return CreateAscSortedVector(size);
		case DataType::_DESC_SORTED_:
			return CreateDescSortedVector(size);
		case DataType::_DISORDER_:
			return CreateDisorderVector(size);
	}
	return CreateDisorderVector(size);
}

}	 // namespace sglib::data