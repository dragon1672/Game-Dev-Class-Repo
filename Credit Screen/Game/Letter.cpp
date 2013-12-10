#include "Letter.h"
#include "TextParticalManager.h"

void Letter::init(char toMatch, std::string lines[LETTER_HEIGHT]) {
	this->toMatch = toMatch;
	for(int i=0;i<LETTER_HEIGHT;i++) {
		for(int j=0;j<LETTER_WIDTH;j++) {
			bitMap[i][j] = (lines[i][j]==LETTER_BIT_MAP_TRUE);
		}
	}
}
void Letter::initParticals(const Vector2D& pos, int particalWidth, int particalPerSquare, TextParticalManager * manager) {
	for(int charWidth = 0; charWidth<LETTER_WIDTH;charWidth++) {
		for(int charHeight = 0; charHeight<LETTER_HEIGHT;charHeight++) {
			if(bitMap[charHeight][charWidth]) {
				for(int i=0;i<particalPerSquare;i++) {
					for(int j=0;j<particalPerSquare;j++) {
						Vector2D pos2Init = pos+Vector2D((float)(charWidth * particalWidth*particalPerSquare), (float)(charHeight * particalWidth*particalPerSquare)) + Vector2D((float)(i*particalWidth), (float)(j*particalWidth));
						manager->initPartical(pos2Init, particalWidth);
					}
				}
			}
		}
	}
}
char Letter::getMatch() {
	return toMatch;
}