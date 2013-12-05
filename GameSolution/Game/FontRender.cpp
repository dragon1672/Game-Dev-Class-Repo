#include "FontRender.h"

#include "MyGraphics.h"
#include "TextFormatting.h"
#include "Font.h"

void FontRender::draw(MyGraphics& graphics, Vector2D& pos,  Font *myFont, TextFormatting * format, const char* text) {
	Vector2D startingPos = pos;//copy memory

	int charWidth  = format->getCharacterWidth()  + format->characterPadding;
	int charHeight = format->getCharacterHeight() + format->characterPadding;
	int offset = 0;

	for(unsigned int i=0; i < strlen(text); i++) {
		if(text[i]=='\n') {
			startingPos = startingPos + Vector2D(0,(float)charHeight);
			offset = 0;
		} else {
			Vector2D charPos = startingPos + Vector2D((float)offset,0);
			myFont->getCharacter(text[i])->draw(graphics, charPos,format);
			offset += charWidth;
		}
	}
}