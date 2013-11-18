#include "ExtendedGraphics.h"
#include "MyRandom.h"
#include "Vector 2.h"

float catAtRange(float val, float min, float max) {
	if(val<min) return min;
	if(val>max) return max;
	return val;
}
int   capAtRange(int   val, int   min, int   max) {
	if(val<min) return min;
	if(val>max) return max;
	return val;
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
void      ExtendedGraphics::drawPlane( Core::Graphics graphics, const Vector2D& p1,const Vector2D& p2,const Vector2D& p3,const Vector2D& p4) {
	float maxLength = ( (p1-p4).lengthSquared() > (p2-p3).lengthSquared() )? (p1-p4).length() : (p2-p3).length();
	float interval = 1/maxLength;
	float index = 0;
	while(index<1) {
		Vector2D start = p1.LERP(index,p2);
		Vector2D end   = p4.LERP(index,p3);
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		index+=interval;
	}
}
void      ExtendedGraphics::drawSquare(Core::Graphics graphics, const Vector2D& p1,const Vector2D& p2) {
	drawPlane(graphics, p1,Vector2D(p1.getX(),p2.getY()),p2,Vector2D(p2.getX(),p1.getY()));
}
void      ExtendedGraphics::textInABox(Core::Graphics graphics, Core::RGB backCol, Core::RGB textCol, char* text, int x, int y, int width, int height) {
	graphics.SetBackgroundColor(backCol);
	graphics.SetColor(backCol);
	drawSquare(graphics,Vector2D(x,y),Vector2D(x,y) + Vector2D(width,height));
	int strLength = strlen(text) * CHAR_SPACING;
	int strHeight = CHAR_HEIGHT;
	graphics.SetColor(textCol);
	graphics.DrawString(x + (width-strLength)/2 , y + (height-strHeight)/2, text);
	graphics.SetBackgroundColor(RGB(0,0,0));
}
Core::RGB ExtendedGraphics::randomColor() {
	return RGB(Random::randomInt(0,255),Random::randomInt(0,255),Random::randomInt(0,255));
}
Core::RGB ExtendedGraphics::brightness(Core::RGB col, float percent) {
	int r = capAtRange(GetRValue(col) * percent,0,255);
	int g = capAtRange(GetGValue(col) * percent,0,255);
	int b = capAtRange(GetBValue(col) * percent,0,255);
	return RGB(r,g,b);
}
Core::RGB ExtendedGraphics::varyColor( Core::RGB col, int variance) {
	int r = capAtRange(GetRValue(col) + Random::randomInt(-variance,variance) ,0,255);
	int g = capAtRange(GetGValue(col) + Random::randomInt(-variance,variance) ,0,255);
	int b = capAtRange(GetBValue(col) + Random::randomInt(-variance,variance) ,0,255);
	return RGB(r,g,b);
}