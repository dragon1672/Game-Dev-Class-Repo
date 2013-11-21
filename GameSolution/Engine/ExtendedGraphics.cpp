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
void      ExtendedGraphics::drawPlane( Core::Graphics& graphics, const Vector2D& p1,const Vector2D& p2,const Vector2D& p3,const Vector2D& p4) {
	float maxLength = ( (p1-p4).lengthSquared() > (p2-p3).lengthSquared() )? (float)(p1-p4).length() : (float)(p2-p3).length();
	//out of 1 would be 1 line for each pixal, 1.8 is for optimization
	//2 creates visable gaps
	float interval = 1.8f/maxLength;
	float index = 0;
	while(index<1) {
		Vector2D start = p1.LERP(index,p2);
		Vector2D end   = p4.LERP(index,p3);
		graphics.DrawLine(start.getX(),start.getY(),end.getX(),end.getY());
		index+=interval;
	}
}
void      ExtendedGraphics::drawSquare(Core::Graphics& graphics, const Vector2D& p1,const Vector2D& p2) {
	drawPlane(graphics, p1,Vector2D(p1.getX(),p2.getY()),p2,Vector2D(p2.getX(),p1.getY()));
}
void      ExtendedGraphics::textInABox(Core::Graphics& graphics, Core::RGB backCol, Core::RGB textCol, char* text, int x, int y, int width, int height) {
	graphics.SetBackgroundColor(backCol);
	graphics.SetColor(backCol);
	drawSquare(graphics,Vector2D((float)x,(float)y),Vector2D((float)x,(float)y) + Vector2D((float)width,(float)height));
	int strLength = strlen(text) * CHAR_SPACING;
	int strHeight = CHAR_HEIGHT;
	graphics.SetColor(textCol);
	graphics.DrawString(x + (width-strLength)/2 , y + (height-strHeight)/2, text);
	graphics.SetBackgroundColor(RGB(0,0,0));
}
void      ExtendedGraphics::drawLoadingBar(Core::Graphics& graphics, const Vector2D& pos, float percent, int width, int height) {
	float currenHeight = pos.getY();
	float spacing = 1.5;
	while(currenHeight<pos.getY()+height) {
		//draws a percentage of the width
		graphics.DrawLine(pos.getX(),currenHeight,pos.getX()+percent*width,currenHeight);
		currenHeight+= spacing;
	}
	//drawing full outline of box
	Vector2D p1 = pos;
	Vector2D p2 = pos + Vector2D((float)width,0);
	graphics.DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
	p1 = p2;
	p2 = pos + Vector2D((float)width,(float)height);
	graphics.DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
	p1 = p2;
	p2 = pos + Vector2D(0,(float)height);
	graphics.DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
	p1 = p2;
	p2 = pos;
	graphics.DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
}
void      ExtendedGraphics::drawLoadingBar(Core::Graphics& graphics, const Vector2D& pos, float current, float max, int width, int height) {
	drawLoadingBar(graphics,pos,max/current,width,height);
}

//Colors
Core::RGB ExtendedGraphics::randomColor() {
	return RGB(Random::randomInt(0,255),Random::randomInt(0,255),Random::randomInt(0,255));
}
Core::RGB ExtendedGraphics::brightness(Core::RGB col, float percent) {
	int r = capAtRange((int)(GetRValue(col) * percent),0,255);
	int g = capAtRange((int)(GetGValue(col) * percent),0,255);
	int b = capAtRange((int)(GetBValue(col) * percent),0,255);
	return RGB(r,g,b);
}
Core::RGB ExtendedGraphics::addR(Core::RGB col, int amount) {
	int r = capAtRange((GetRValue(col) + amount),0,255);
	int g = GetGValue(col);
	int b = GetBValue(col);
	return RGB(r,g,b);
}
Core::RGB ExtendedGraphics::addG(Core::RGB col, int amount) {
	int r = GetRValue(col);
	int g = capAtRange((GetGValue(col) + amount),0,255);
	int b = GetBValue(col);
	return RGB(r,g,b);
}
Core::RGB ExtendedGraphics::addB(Core::RGB col, int amount) {
	int r = GetRValue(col);
	int g = GetGValue(col);
	int b = capAtRange((GetBValue(col) + amount),0,255);
	return RGB(r,g,b);
}
Core::RGB ExtendedGraphics::varyColor( Core::RGB col, int variance) {
	int r = capAtRange(GetRValue(col) + Random::randomInt(-variance,variance) ,0,255);
	int g = capAtRange(GetGValue(col) + Random::randomInt(-variance,variance) ,0,255);
	int b = capAtRange(GetBValue(col) + Random::randomInt(-variance,variance) ,0,255);
	return RGB(r,g,b);
}