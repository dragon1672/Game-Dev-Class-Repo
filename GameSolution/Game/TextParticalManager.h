#pragma once

#include "ParticalWithDestination.h"
#include "Font.h"
#include "MyGraphics.h"

class ParticalTextFormat;

class TextParticalManager {
private:
	static const int MAX_PARTICALS = 20000;
	int paddingBetweenCharacters;
	ParticalWithDestination myParticals[MAX_PARTICALS];
	int numOfParticals;
public:
	TextParticalManager() {
		paddingBetweenCharacters = 3;
		numOfParticals = 0;
	}
	Core::RGB textColor;
	void initText(Vector2D& pos, const char* text, Font *style, ParticalTextFormat * format);
	void update(float dt);
	void draw(MyGraphics& graphics);
	void initPartical(Vector2D& destinationLocation, ParticalTextFormat * format);
	void reset();
};