#pragma once
#ifndef TWO_COL_TABLE_H
#define TWO_COL_TABLE_H


#include <string>
#include "Core.h"
#include "ExtendedGraphics.h"
#include "Vector 2.h"
#include "myAssert.h"
#include "MyGraphics.h"

//using std::string;

class TwoColTable {
public:
	static const int lineSpacing = ExtendedGraphics::char_height+6;
private:
	static const int MAX_ROWS = 10;
	const char* col1Data[MAX_ROWS+1];//plus 1 for the header
	const char* col2Data[MAX_ROWS+1];
	int currentRows;
	int col1_length;
	int col2_length;
	inline std::string textInArea(const char* text, int width) {
		int maxChars = width/ExtendedGraphics::char_spacing;
		if(strlen(text)<(unsigned)maxChars) return text;
		std::string str(text);
		return str.substr(0,maxChars);
	}
public:
	TwoColTable(const char* col1Title, const char* col2Title) {
		col1Data[0] = col1Title;
		col2Data[0] = col2Title;
		currentRows = 0;
	}
	inline void setCol1Width(int width) {
		col1_length = width;
	}
	inline void setCol2Width(int width) {
		col2_length = width;
	}
	inline void addRow(const char* col1Text, const char* col2Text) {
		ASSERT(currentRows<MAX_ROWS);
		col1Data[currentRows] = col1Text;
		col2Data[currentRows] = col2Text;
		currentRows++;
	}
	inline void draw(MyGraphics& graphics, const Vector2D& pos) {
		int xPos = (int)pos.getX();
		int currentHeight = (int)pos.getY();
		graphics.drawDottedLine(xPos, currentHeight + lineSpacing - 2, 
													xPos + col1_length + col2_length,currentHeight + lineSpacing - 2,
													3);
		graphics.drawLine(xPos+col1_length+1,currentHeight,xPos+col1_length+1,currentHeight+lineSpacing*currentRows);
		for(int i=0;i<currentRows;i++) {
			graphics.drawString(xPos,              currentHeight,textInArea(col1Data[i],col1_length).c_str());
			graphics.drawString(xPos+col1_length+3,currentHeight,textInArea(col1Data[i],col2_length).c_str());//+3 pad
			currentHeight += lineSpacing;
		}
	}
};

#endif;