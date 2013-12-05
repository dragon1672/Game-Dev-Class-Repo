#include "Letter.h"
#include "TextParticalManager.h"
#include "ParticalTextFormat.h"
#include "MyGraphics.h"

void Letter::init(char toMatch, std::string lines[LETTER_HEIGHT]) {
	this->toMatch = toMatch;
	for(int i=0;i<LETTER_HEIGHT;i++) {
		for(int j=0;j<LETTER_WIDTH;j++) {
			bitMap[i][j] = (lines[i][j]==LETTER_BIT_MAP_TRUE);
		}
	}
}
void Letter::initParticals(const Vector2D& pos, ParticalTextFormat * format, TextParticalManager *manager) {
	float size = (float)(format->particalSize*format->particalDensity);
	for(int charWidthIndex = 0; charWidthIndex<LETTER_WIDTH;charWidthIndex++) {
		for(int charHeightIndex = 0; charHeightIndex<LETTER_HEIGHT;charHeightIndex++) {
			if(bitMap[charHeightIndex][charWidthIndex]) {
				Vector2D bitMapOffset((float)(charWidthIndex * size), (float)(charHeightIndex * size));
				for(int i=0;i<format->particalDensity;i++) {
					for(int j=0;j<format->particalDensity;j++) {
						Vector2D pos2Init = pos
											+ bitMapOffset
											+ Vector2D((float)(i*format->particalSize), (float)(j*format->particalSize));//location in bitmap pixal offset
						manager->initPartical(pos2Init, format);
					}
				}
			}
		}
	}
}
char Letter::getMatch() {
	return toMatch;
}
void Letter::draw(MyGraphics& graphics, const Vector2D& pos, TextFormatting * format) {
	float size = (float)(format->particalSize*format->particalDensity);
	for(int charWidthIndex = 0; charWidthIndex<LETTER_WIDTH;charWidthIndex++) {
		for(int charHeightIndex = 0; charHeightIndex<LETTER_HEIGHT;charHeightIndex++) {
			if(bitMap[charHeightIndex][charWidthIndex]) {
				Vector2D bitMapOffset((float)(charWidthIndex * size), (float)(charHeightIndex * size));
				for(int i=0;i<format->particalSize;i++) {
					Vector2D start = pos
									+ bitMapOffset
									+ Vector2D((float)i,0);
					Vector2D end   = start + Vector2D(0,size);
					graphics.drawLine(start,end);
				}
			}
		}
	}
}