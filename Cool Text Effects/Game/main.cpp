#include "Engine.h"
#include "Core.h"
#include "TextParticalManager.h"

using Core::Input;
using Core::RGB;
using Core::Graphics;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

Font myText;
TextParticalManager welcomeText;


bool Update(float dt)
{
	if ( Input::IsPressed( Input::KEY_ESCAPE )) {
		return true;
	}
	welcomeText.update(dt);
	return false;
}

void Draw( Graphics& graphics )
{
	welcomeText.draw(graphics);
	graphics.SetColor( RGB(255,255,255) );
}


int main()
{
	myText.init("../FONT.txt");//not loading from file
	Vector2D textPos = Vector2D(100,100);
	welcomeText.initText(textPos,"#_-=+;:'\"\\/?.,[]!",&myText,5,1);
	welcomeText.initText(Vector2D(50,50),"Welcome to Space Wars's  :D &",&myText,2);
	welcomeText.initText(Vector2D(700,600),"Hi",&myText,10,2);

	Core::Init( "Creating Awesome Text", SCREEN_WIDTH, SCREEN_HEIGHT );
	Core::RegisterUpdateFn( Update );
	Core::RegisterDrawFn ( Draw );
	Core::GameLoop();
}

