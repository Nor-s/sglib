#ifndef SGLIB_ALGORITHM_SORT_H
#define SGLIB_ALGORITHM_SORT_H

#include <numeric>
#include "Random.h"

namespace sglib::algorithm
{

enum class PivotSelectionMode
{
	FIRST,
	LAST,
	MIDDLE,
	RANDOM,
	MEDIAN_OF_THREE
};

template <typename _RandomAccessIter>
_RandomAccessIter MedianOfThree(_RandomAccessIter first, _RandomAccessIter last)
{
	auto half = std::distance(first, last) >> 1;
	last--;

	if (first < last)
	{
		_RandomAccessIter mid = std::next(first, half);
		if ((*mid > *first) != (*mid > *last))
			return mid;
		if ((*last > *first) != (*last > *mid))
			return last;
	}
	return first;
}

template <typename _RandomAccessIter>
_RandomAccessIter GetPivot(_RandomAccessIter first, _RandomAccessIter last, PivotSelectionMode mode)
{
	using enum PivotSelectionMode;
	switch (mode)
	{
		case FIRST:
			return first;
		case LAST:
			return last - 1;
		case MIDDLE:
			return first + (std::distance(first, last) >> 1);
		case RANDOM:
			return first + Random::RangeInt(0, std::distance(first, last - 1));
		case MEDIAN_OF_THREE:
			return MedianOfThree(first, last);
	}
}

template <typename _RandomAccessIter>
_RandomAccessIter Partition(_RandomAccessIter first, _RandomAccessIter last, PivotSelectionMode mode)
{
	_RandomAccessIter pivot = GetPivot(first, last, mode);
	std::swap(*first, *pivot);
	pivot = first;

	_RandomAccessIter left = std::next(first);
	for (_RandomAccessIter i = left; i != last; ++i)
	{
		if (*i <= *pivot)
		{
			std::swap(*i, *left);
			left++;
		}
	}

	std::swap(*pivot, *std::prev(left));

	return std::prev(left);
}

template <typename _RandomAccessIter>
void QuickSort(_RandomAccessIter first, _RandomAccessIter last, PivotSelectionMode mode = PivotSelectionMode::MIDDLE)
{
	using enum PivotSelectionMode;
	if (first >= last)
	{
		return;
	}

	_RandomAccessIter pivot = Partition(first, last, mode);

	QuickSort(first, pivot, mode);
	QuickSort(pivot + 1, last, mode);
}

}	 // namespace sglib::algorithm

#endif	  // SGLIB_ALGORITHM_SORT_H
