#include "ExtendedGraphics.h"
#include "MyRandom.h"
#include "Vector 2.h"

Core::RGB ExtendedGraphics::randomColor() {
	return RGB(Random::randomInt(0,255),Random::randomInt(0,255),Random::randomInt(0,255));
}
void      ExtendedGraphics::drawDottedLine(Core::Graphics& graphics, const Vector2D& start, const Vector2D& end, float length) {
	Vector2D line = end - start;
	float lineLength = (float)line.length();
	float lerpPercent = length / lineLength;
	bool drawing = true;
	float currentStep = 0;

	while((currentStep+lerpPercent)<=1) {
		if(drawing) {
			Vector2D begin = start.LERP(currentStep,end);
			Vector2D stop  = start.LERP(currentStep+lerpPercent,end);
			graphics.DrawLine(begin.getX(),begin.getY(),stop.getX(),stop.getY());
		}
		drawing = !drawing;  /*(Luis) Include comments in sections of code like this to specify that this is toggling. */
		currentStep += 2*lerpPercent;
	}
}
void      ExtendedGraphics::drawDottedLine(Core::Graphics& graphics, int x1, int y1, int x2, int y2, float length) {
	drawDottedLine(graphics,Vector2D((float)x1,(float)y1),Vector2D((float)x2,(float)y2),length);
}
void      ExtendedGraphics::drawRainbowText(Core::Graphics& graphics, float x, float y, char* text) {
	for(unsigned int i=0;i<strlen(text);i++) {
		graphics.SetColor(randomColor());
		graphics.DrawString((int)x+i*CHAR_SPACING,(int)y,&text[i]);
	}
}