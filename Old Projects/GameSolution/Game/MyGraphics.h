#pragma once
#ifndef My_Graphics_h
#define My_graphics_h

#include "Matrix3D.h"
#include "Vector 2.h"
#include "ExtendedGraphics.h"

#define CHAR_SPACING 7//for graphics.drawString()
#define CHAR_HEIGHT 10//for graphics.drawString()

class MyGraphics {
protected:
	//Matrix3D globalTrans;
	Core::Graphics *masterGraphic;
public:
	void setGraphic(Core::Graphics *toSet);
	void setGraphic(MyGraphics *toSet);
	//void setGlobalTrans(const Matrix3D& toSet);
	void setColor(Core::RGB toSet);
	void setBackgroundColor(Core::RGB toSet);
	void drawString( int x, int y, const char* string );
	virtual void drawLine(Vector2D p1, Vector2D p2);
	void drawLine(int   x1,int   y1, int   x2, int   y2);
	void drawLine(float x1,float y1, float x2, float y2);
	void drawDottedLine(const Vector2D& start, const Vector2D& end, float length);
	void drawDottedLine(int x1, int y1, int x2, int y2, float length);
	void drawRainbowText(float x, float y, char* text);
	void drawPlane( const Vector2D& p1,const Vector2D& p2,const Vector2D& p3,const Vector2D& p4);
	void drawSquare(const Vector2D& p1,const Vector2D& p2);
	void textInABox(Core::RGB backCol, Core::RGB textCol, const char* text, int x, int y, int width, int height);
	void drawLoadingBar(const Vector2D& pos, float percent, int width, int height, Core::RGB boarderColor=RGB(255,255,0), Core::RGB barColor=RGB(255,0,0));
	void drawLoadingBar(const Vector2D& pos, float current, float max, int width, int height, Core::RGB boarderColor=RGB(255,255,0), Core::RGB barColor=RGB(255,0,0));

};

#endif