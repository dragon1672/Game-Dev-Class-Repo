#pragma once
#ifndef TEXT_FORMATTING_H
#define TEXT_FORMATTING_H

#include "Core.h"

class TextFormatting {
private:
	int instancesOf(char ch, const char* source);
public:
	Core::RGB color;
	int particalSize;
	int particalDensity;
	int characterPadding;
	TextFormatting() {}
	TextFormatting(int particalSize, int particalDensity, Core::RGB color, int characterPadding) {
		init(particalSize,particalDensity, color, characterPadding);
	}
	void init(int particalSize, int particalDensity, Core::RGB color, int characterPadding);
	int getCharacterWidth();
	int getCharacterHeight();
	int widthOfString(const char* str);
	int heightOfString(const char* str);
};

#endif