#pragma once

#include "Letter.h"

const int MAX_LETTERS = 200;

class Font {//transforms char* to letters and inits
public:
	static Font defaultFont;
private:
	static Letter defaultLetter;//if the character passed is unknown
	static Letter blankLetter;//for spaces
	Letter letters[MAX_LETTERS];
	int numOfLetters;
	static Letter constructLetterFromStream(std::istream& input);
	static void   consumeBlankLines(std::istream& input);
	void constructFontFromStream(std::istream& input);
public:
	Font()  {}
	Font(const char* fileName)  {
		init(fileName);
	}
	Font(std::istream& input)   {
		init(input);
	}
	void    init(const char* fileName);
	void    init(std::istream& input);
	Letter *getCharacter(char toFind);
};