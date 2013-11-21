#include "MyRandom.h"
#include <random>
#include <ctime>//for srand seed
#include "Vector 2.h"

int      Random::randomInt(int low, int high) {
	std::random_device rd;//dont like making multiple engines
	std::mt19937 mt(rd()); //seed
	std::uniform_int_distribution<int>dist(low,high);
	return dist(mt);
}
float    Random::randomFloat(float low, float high) {
	return randomFloat() * (high-low) + low;
}
void     Random::init() {
	srand((unsigned)time(0));
}
float    Random::randomFloat() {
	return rand()/(static_cast<float>(RAND_MAX));
}
Vector2D Random::randomUnitVector() {
	return Vector2D(randomFloat(-1,1),randomFloat(-1,1)).normalized();
}
Vector2D Random::randomFloatVector(float low, float high) {
	return Vector2D(randomFloat(low,high),randomFloat(low,high));
}
Vector2D Random::randomIntVector(int   low, int   high) {
	return Vector2D(randomInt(low,high),randomInt(low,high));
}