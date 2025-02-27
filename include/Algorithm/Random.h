#ifndef SGLIB_ALGORITHM_RANDOM_H
#define SGLIB_ALGORITHM_RANDOM_H

#include <random>

namespace sglib::algorithm
{

class Random
{
	static std::random_device rd;
	static std::mt19937 mt19937;

public:
	static int RangeInt(int min, int max)
	{
		std::uniform_int_distribution dis(min, max);
		return dis(mt19937);
	}
	static double RangeDouble(double min, double max)
	{
		std::uniform_real_distribution dis(min, max);
		return dis(mt19937);
	}
};

std::random_device Random::rd{};
std::mt19937 Random::mt19937{rd()};

}	 // namespace sglib::algorithm

#endif	  // SGLIB_ALGORITHM_RANDOM_H
