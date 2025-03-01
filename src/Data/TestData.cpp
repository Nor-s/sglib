#include "Data/TestData.h"
#include "Algorithm/Random.h"

namespace sglib::data
{
std::vector<int> TestData::create_asc_sorted_vector(size_t size)
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
std::vector<int> TestData::create_shuffle_vector(size_t size)
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

std::vector<int> TestData::create_desc_sorted_vector(size_t size)
{
	std::vector<int> sorted_vec;
	if (sorted_vec.empty())
	{
		sorted_vec = create_asc_sorted_vector(size);
		std::reverse(sorted_vec.begin(), sorted_vec.end());
	}
	return sorted_vec;
}
std::vector<int> TestData::create(DataType type, size_t size)
{
	switch (type)
	{
		case DataType::_ASC_SORTED_:
			return create_asc_sorted_vector(size);
		case DataType::_DESC_SORTED_:
			return create_desc_sorted_vector(size);
		case DataType::_SHUFFLED_:
			return create_shuffle_vector(size);
	}
	return create_shuffle_vector(size);
}

}	 // namespace sglib::data