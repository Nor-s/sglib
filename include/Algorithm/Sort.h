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

namespace sglib::algorithm
{

template <typename _RandomAccessIter, typename _BufferLeftIter, typename _Pr>
void Merge(_RandomAccessIter first, _RandomAccessIter mid, _RandomAccessIter last, _BufferLeftIter tempBuffer, _Pr pred)
{
	auto left = first;
	auto right = mid;

	auto endIter = tempBuffer + std::distance(first, last);

	for (auto bufferIter = tempBuffer; bufferIter != endIter; bufferIter++)
	{
		// left < right
		if (right == last || (left != mid && pred(*left, *right)))
		{
			*bufferIter = *left;
			left++;
		}
		else
		{
			*bufferIter = *right;
			right++;
		}
	}

	for (auto it = first; it != last; ++it, ++tempBuffer)
	{
		*it = *tempBuffer;
	}
}

template <typename _RandomAccessIter, typename _BufferLeftIter, typename _Pr>
void MergeSort(_RandomAccessIter first, _RandomAccessIter last, _BufferLeftIter tempBuffer, _Pr pred)
{
	if (first + 1 >= last)
	{
		return;
	}
	auto half = std::distance(first, last) >> 1;
	auto mid = std::next(first, half);

	MergeSort(first, mid, tempBuffer, pred);
	MergeSort(mid, last, tempBuffer + half, pred);

	Merge(first, mid, last, tempBuffer, pred);
}

template <typename _RandomAccessIter>
void StableSort(_RandomAccessIter first, _RandomAccessIter last)
{
	using _ValueType = std::iter_value_t<_RandomAccessIter>;

	if (first + 1 >= last)
	{
		return;
	}

	auto size = std::distance(first, last);
	std::vector<_ValueType> tempBuffer(size);
	MergeSort(first, last, tempBuffer.begin(), std::less<>{});
}

template <typename _RandomAccessIter, typename _Pred>
void InsertSort(_RandomAccessIter first, _RandomAccessIter last, _Pred pred)
{
	for (auto it = std::next(first); it != last; ++it)
	{
		auto cur = it;
		for (auto inner = std::prev(cur); inner != std::prev(first); --inner)
		{
			if (pred(*inner, *cur))
			{
				break;
			}
			std::swap(*cur, *inner);
			cur = inner;
		}
	}
}

template <typename _RandomAccessIter>
void InsertSort(_RandomAccessIter first, _RandomAccessIter last)
{
	InsertSort(first, last, std::less<>{});
}

}	 // namespace sglib::algorithm

#endif	  // SGLIB_ALGORITHM_SORT_H
