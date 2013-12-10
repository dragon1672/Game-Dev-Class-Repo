#pragma once

#include "ParticalWithDestination.h"
#include "Font.h"
#include "Core.h"

const int MAX_PARTICALS = 99999;

class TextParticalManager {
private:
	int paddingBetweenCharacters;
	ParticalWithDestination myParticals[MAX_PARTICALS];
	int numOfParticals;
public:
	TextParticalManager() {
		paddingBetweenCharacters = 3;
	}
	Core::RGB textColor;
	void initText(Vector2D& pos, const char* text, Font *style, int size=1, int particalSize=1);
	void update(float dt);
	void draw(Core::Graphics& graphics);
	void initPartical(Vector2D& destinationLocation, int particalWidth);
};