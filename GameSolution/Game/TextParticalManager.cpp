#include "TextParticalManager.h"
#include "ParticalTextFormat.h"
#include "MyRandom.h"


void TextParticalManager::initText(Vector2D& pos, const char* text, Font *myFont, ParticalTextFormat * format) {
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
			myFont->getCharacter(text[i])->initParticals(charPos,format,this);
			offset += charWidth;
		}
	}
}
float mouseRadius = 50;
void TextParticalManager::update(float dt) {
	Vector2D mouse = Vector2D((float)Core::Input::GetMouseX(),(float)Core::Input::GetMouseY());
	for(int i=0; i < numOfParticals; i++) {//since all particles are used no lifetime required
		Vector2D difference = mouse - myParticals[i].pos;
		if(difference.lengthSquared()<mouseRadius*mouseRadius) {
			Vector2D posAwayFromMouse = myParticals[i].pos-difference;
			myParticals[i].updateVelToPos(posAwayFromMouse);
		} else {
			myParticals[i].updateVelToTarget();
		}

		myParticals[i].update(dt);
	}
}
void TextParticalManager::draw(MyGraphics& graphics) {
	for(int i=0; i < numOfParticals; i++) {//since all particles are used no lifetime required
		graphics.setColor(RGB(255,255,0));
		//graphics.SetColor(myParticals[i].color);
		for(int j=0; j < myParticals[i].size; j++) {
			Vector2D start = myParticals[i].pos + Vector2D((float)j,0);
			Vector2D end   = start + Vector2D(0,(float)myParticals[i].size);
			graphics.drawLine(start,end);
		}
	}
}

void TextParticalManager::initPartical(Vector2D& destinationLocation, ParticalTextFormat * format) {
	int index = numOfParticals++;
	myParticals[index].target = destinationLocation;
	myParticals[index].pos    = format->spawnLocation->getPos();
	myParticals[index].color  = format->color;
	myParticals[index].size   = format->particalSize;
	myParticals[index].slowAtRange = format->slowEffect;
}
void TextParticalManager::reset() {
	numOfParticals = 0;
}