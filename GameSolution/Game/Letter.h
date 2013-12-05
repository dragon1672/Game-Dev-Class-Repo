#pragma once

#include <string>
#include "Vector 2.h"

//if these are changed the text file the font is loaded from becomes useless
const char LETTER_BIT_MAP_TRUE  = '*';
const char LETTER_BIT_MAP_FALSE = '.';

class TextParticalManager;
class ParticalTextFormat;
class MyGraphics;
class TextFormatting;

class Letter {
public:
	static const int  LETTER_WIDTH  = 5;
	static const int  LETTER_HEIGHT = 6;
private:
	char toMatch;
	bool bitMap[LETTER_HEIGHT][LETTER_WIDTH];
public:
	Letter() {}
	Letter(char tomMath, std::string (&lines)[LETTER_HEIGHT]) {
		init(tomMath, lines);
	}
	void init(char tomMath, std::string lines[LETTER_HEIGHT]);
	void initParticals(const Vector2D& pos, ParticalTextFormat * format, TextParticalManager *manager);
	char getMatch();
	void draw(MyGraphics& graphics, const Vector2D& pos, TextFormatting * format);
};