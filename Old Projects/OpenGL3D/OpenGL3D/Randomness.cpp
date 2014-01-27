#include "Randomness.h"
#include <random>

float Random::randomFloat() {
	return rand()/(static_cast<float>(RAND_MAX));
}
float Random::randomFloat(float low, float high) {
	return randomFloat() * (high-low) + low;
}
