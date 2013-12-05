#include "MyGraphics.h"

void MyGraphics::setGraphic(Core::Graphics *toSet) {
	masterGraphic = toSet;
}
/*
void MyGraphics::setGlobalTrans(const Matrix3D& toSet) {
	globalTrans = toSet;

	//*/
void MyGraphics::setColor(Core::RGB toSet) {
	masterGraphic->SetColor(toSet);
}
void MyGraphics::setBackgroundColor(Core::RGB toSet) {
	masterGraphic->SetBackgroundColor(toSet);
}
void MyGraphics::drawString( int x, int y, const char* string ) {
	masterGraphic->DrawString(x,y,string);
}
void MyGraphics::drawLine(Vector2D p1, Vector2D p2) { //yes copied so I can edit them
	//p1 = globalTrans * p1;
	//p2 = globalTrans * p2;
	masterGraphic->DrawLine(p1.getX(),p1.getY(),p2.getX(),p2.getY());
}
void MyGraphics::drawLine(int x1,int y1, int x2, int y2) {
	Vector2D p1((float)x1,(float)y1);
	Vector2D p2((float)x2,(float)y2);
	drawLine(p1,p2);
}
void MyGraphics::drawLine(float x1,float y1, float x2, float y2) {
	Vector2D p1(x1,y1);
	Vector2D p2(x2,y2);
	drawLine(p1,p2);
}
void MyGraphics::drawDottedLine(const Vector2D& start, const Vector2D& end, float length) {
Vector2D line = end - start;
float lineLength = (float)line.length();
float lerpPercent = length / lineLength;
bool drawing = true;
float currentStep = 0;

while((currentStep+lerpPercent)<=1) {
	if(drawing) {
		Vector2D begin = start.LERP(currentStep,end);
		Vector2D stop  = start.LERP(currentStep+lerpPercent,end);
		drawLine(begin,stop);
	}
	drawing = !drawing; //toggle
	currentStep += 2*lerpPercent;
}
}
void MyGraphics::drawDottedLine(int x1, int y1, int x2, int y2, float length) {
	drawDottedLine(Vector2D((float)x1,(float)y1),Vector2D((float)x2,(float)y2),length);
}
void MyGraphics::drawRainbowText(float x, float y, char* text) {
	for(unsigned int i=0;i<strlen(text);i++) {
		setColor(ExtendedGraphics::randomColor());
		drawString((int)x+i*CHAR_SPACING,(int)y,&text[i]);
	}
}
void MyGraphics::drawPlane( const Vector2D& p1,const Vector2D& p2,const Vector2D& p3,const Vector2D& p4) {
	float maxLength = ( (p1-p4).lengthSquared() > (p2-p3).lengthSquared() )? (float)(p1-p4).length() : (float)(p2-p3).length();
	//out of 1 would be 1 line for each pixal, 1.8 is for optimization
	//2 creates visable gaps
	float interval = 1.8f/maxLength;
	float index = 0;
	while(index<1) {
		Vector2D start = p1.LERP(index,p2);
		Vector2D end   = p4.LERP(index,p3);
		drawLine(start,end);
		index+=interval;
	}
}
void MyGraphics::drawSquare(const Vector2D& p1,const Vector2D& p2) {
	drawPlane(p1,Vector2D(p1.getX(),p2.getY()),p2,Vector2D(p2.getX(),p1.getY()));
}
void MyGraphics::textInABox(Core::RGB backCol, Core::RGB textCol, const char* text, int x, int y, int width, int height) {
	setBackgroundColor(backCol);
	setColor(backCol);
	drawSquare(Vector2D((float)x,(float)y),Vector2D((float)x,(float)y) + Vector2D((float)width,(float)height));
	int strLength = strlen(text) * CHAR_SPACING;
	int strHeight = CHAR_HEIGHT;
	setColor(textCol);
	drawString(x + (width-strLength)/2 , y + (height-strHeight)/2, text);
	setBackgroundColor(RGB(0,0,0));
}
void MyGraphics::drawLoadingBar(const Vector2D& pos, float percent, int width, int height, Core::RGB boarderColor, Core::RGB barColor) {
	float currenHeight = pos.getY();
	float spacing = 1.5;
	setColor(barColor);
	while(currenHeight<pos.getY()+height) {
		//draws a percentage of the width
		drawLine(pos.getX(),currenHeight,pos.getX()+percent*width,currenHeight);
		currenHeight+= spacing;
	}
	//drawing full outline of box
	setColor(boarderColor);
	Vector2D p1 = pos;
	Vector2D p2 = pos + Vector2D((float)width,0);
	drawLine(p1,p2);
	p1 = p2;
	p2 = pos + Vector2D((float)width,(float)height);
	drawLine(p1,p2);
	p1 = p2;
	p2 = pos + Vector2D(0,(float)height);
	drawLine(p1,p2);
	p1 = p2;
	p2 = pos;
	drawLine(p1,p2);
}
void MyGraphics::drawLoadingBar(const Vector2D& pos, float current, float max, int width, int height, Core::RGB boarderColor, Core::RGB barColor) {
	drawLoadingBar(pos,max/current,width,height,boarderColor, barColor);
}