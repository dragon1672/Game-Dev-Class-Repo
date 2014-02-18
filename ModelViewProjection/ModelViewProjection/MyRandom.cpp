#include "MyRandom.h"

#include <random>

std::random_device eng;

//std::mt19937 eng(seq);  // a core engine class 

namespace RANDOM {

	float randomFloat() {
		std::uniform_real_distribution<float> randF(0, 1);
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