#include "TextParticalManager.h"

void TextParticalManager::initText(Vector2D& pos, const char* text, Font *style, int size, int particalSize) {
	int charWidth = LETTER_WIDTH * size*particalSize;
	for(unsigned int i=0; i < strlen(text); i++) {
		Vector2D startingPos = pos + Vector2D((float)(i * (charWidth+paddingBetweenCharacters)),0);
		//Vector2D startingPos = pos + Vector2D((float)(i * 50),0);
		style->getCharacter(text[i])->initParticals(startingPos,particalSize,size,this);
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
void TextParticalManager::draw(Core::Graphics& graphics) {
	for(int i=0; i < numOfParticals; i++) {//since all particles are used no lifetime required
		graphics.SetColor(RGB(255,255,0));
		//graphics.SetColor(myParticals[i].color);
		for(int j=0; j < myParticals[i].size; j++) {
			Vector2D start = myParticals[i].pos + Vector2D((float)j,0);
			Vector2D end   = start + Vector2D(0,(float)myParticals[i].size);
			graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		}
	}
}
#include <random>

void TextParticalManager::initPartical(Vector2D& destinationLocation, int particalSize) {
	int index = numOfParticals++;
	myParticals[index].target = destinationLocation;

	myParticals[index].pos    = Vector2D(rand()%1000,rand()%1000);
	//myParticals[index].pos    = Vector2D(500,500);
	//myParticals[index].pos    = Vector2D(0,0);//set to random--------------------------------------------TODO
	myParticals[index].color  = textColor;
	myParticals[index].size   = particalSize;
}