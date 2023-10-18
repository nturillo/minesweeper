#include "Random.h"

std::mt19937 Random::rand(std::time(0));

const int& Random::Int(const int& min, const int& max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rand);
}
