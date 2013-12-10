#pragma once

#include <string>
#include "Vector2D.h"

class TextParticalManager;

//if these are changed the text file the font is loaded from becomes useless
const int  LETTER_WIDTH  = 5;
const int  LETTER_HEIGHT = 6;
const char LETTER_BIT_MAP_TRUE  = '*';
const char LETTER_BIT_MAP_FALSE = '.';


class Letter {
private:
	char toMatch;
	bool bitMap[LETTER_HEIGHT][LETTER_WIDTH];
public:
	Letter() {}
	Letter(char tomMath, std::string (&lines)[LETTER_HEIGHT]) {
		init(tomMath, lines);
	}
	void init(char tomMath, std::string lines[LETTER_HEIGHT]);
	void initParticals(const Vector2D& pos, int particalWidth, int particalPerSquare, TextParticalManager *manager);
	char getMatch();
};