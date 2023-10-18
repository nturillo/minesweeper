#pragma once

#include <random>

class Random {
public:
	static const int Int(const int min, const int max);
private:
	static std::mt19937 rand;
};