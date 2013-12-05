#include "TextFormatting.h"
#include "Letter.h"
#include <cstring>
#include "Core.h"

int TextFormatting::instancesOf(char ch, const char* source) {
	int count = 0;
	for(unsigned int i=0;i<strlen(source);i++) if(source[i]==ch) count++;
	return count;
}
void TextFormatting::init(int particalSize, int particalDensity, Core::RGB color, int characterPadding) {
	this->particalSize     = particalSize;
	this->particalDensity  = particalDensity;
	this->color            = color;
	this->characterPadding = characterPadding;
}
int TextFormatting::getCharacterWidth() {
	return particalDensity * particalSize * Letter::LETTER_WIDTH;
}
int TextFormatting::getCharacterHeight() {
	return particalDensity * particalSize * Letter::LETTER_HEIGHT;
}
int TextFormatting::widthOfString(const char* str) {
	int longestLine = 0;
	int currentLine = 0;
	for(unsigned int i=0;i<strlen(str);i++) {
		if(str[i]=='\n') {
			currentLine = 0;
		} else {
			currentLine++;
		}
		longestLine = (longestLine<currentLine)? currentLine : longestLine;
	}
	return (getCharacterWidth()+characterPadding) * longestLine;
}
int TextFormatting::heightOfString(const char* str) {
	int lineReturns = instancesOf('\n',str);
	return (getCharacterHeight()+characterPadding) * (lineReturns + 1);
}