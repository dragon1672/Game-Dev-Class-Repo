#include "EndGameView.h"
#include "MyGraphics.h"

void EndGameView::init(int width, int height) {

}
bool EndGameView::update(float dt) {
	return returnButton.isPressed();
}
void EndGameView::draw(MyGraphics& graphics) {
	returnButton.draw(graphics);
}