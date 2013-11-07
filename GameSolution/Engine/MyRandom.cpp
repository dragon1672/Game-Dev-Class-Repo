#include "MyRandom.h"
#include <random>
int Random::randomnumber(int low, int high) {
	std::random_device rd;//dont like making multiple engines
	std::mt19937 mt(rd()); //seed
	std::uniform_int_distribution<int>dist(low,high);
	return dist(mt);
}
float Random::randomFloat(float low, float high) {
	std::random_device rd;//dont like making multiple engines
	std::mt19937 mt(rd()); //seed
	std::uniform_int_distribution<int>dist((int)low,(int)high);
	return (float)dist(mt);
}
void Random::init() {
	//startupSeeds and stuch
}