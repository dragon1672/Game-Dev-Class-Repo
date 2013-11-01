#include "Engine.h"
#include "Core.h"
#include "SpaceShip.h"
#include "GameSpace.h"

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const float PAD = 5;
const float topOffset = 30;
const float newWidth  = SCREEN_WIDTH- 2*PAD;
const float newHeight = SCREEN_HEIGHT - topOffset - 2*PAD;
Vector2D worldPos(PAD,topOffset+PAD);
Vector2D boundPoints[] = {
							worldPos,
							worldPos+Vector2D(0,           (worldPos.getY()+newHeight)/2),
							worldPos+Vector2D(25,          (worldPos.getY()+newHeight)-100),
									 Vector2D(.5*newWidth, (worldPos.getY()+newHeight)),
							worldPos+Vector2D(newWidth,    newHeight/2),
							worldPos+Vector2D(newWidth/2,  0)
						};

GameSpace myWorld(newWidth, newHeight,worldPos);
Boundary bounds;
bool update( float dt ) {
	return myWorld.update(dt);
}
void draw( Core::Graphics& graphics ) {
	myWorld.draw(graphics);
}

void startCoreEngine() {
	Core::Init("Space Quest",SCREEN_WIDTH,SCREEN_HEIGHT);
	Core::RegisterDrawFn(draw);
	Core::RegisterUpdateFn(update);
	Core::GameLoop();
}

int main() {

	bounds.init(sizeof(boundPoints)/sizeof(*boundPoints), boundPoints);
	myWorld.registerBoundary(&bounds);
	startCoreEngine();
}

