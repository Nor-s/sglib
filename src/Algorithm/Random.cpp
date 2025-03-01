#include "Algorithm/Random.h"

namespace sglib::algorithm
{

std::random_device Random::rd{};
std::mt19937 Random::mt19937{rd()};

}	 // namespace sglib::algorithm