#include "MyRandom.h"

#include <random>

std::tr1::mt19937 eng;  // a core engine class 
std::uniform_real_distribution<float> randF(0, 1);

namespace RANDOM {

	float randomFloat() {
		return randF(eng);
	}

	float randomFloat(float min, float max) {
		return randomFloat() * (max-min) + min;
	}

	int randomInt(int min, int max) {
		std::uniform_int_distribution<int> rand(min, max);
		return rand(eng);
	}
}