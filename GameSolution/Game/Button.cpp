#include "Button.h"

void Button::init(DynamicPosition * cursor, Vector2D& pos, const char* text, int width, int height, Core::RGB setHoverColor = DEFAULT_hoverColor, Core::RGB setDefaultColor = DEFAULT_defaultColor) {
	this->cursor = cursor;
	this->pos = pos;
	this->text = text;
	this->width = width;
	this->height = height;
	this->hoverColor = setHoverColor;
	this->defaultColor = setDefaultColor;
}
void Button::draw(MyGraphics& graphics) {
	graphics.textInABox(currentColor(),RGB(255,255,0),text,pos.getX(),pos.getY(),width,height);
}

bool Button::mouseWithinBounds() {
	Vector2D toCompare = cursor->getPos() - pos;
	return (0 < toCompare.getX() && toCompare.getX() < width
		&& 0 < toCompare.getY() && toCompare.getY() < height);
}

bool Button::isPressed() {
	if(mouseWithinBounds()) return hoverColor;
}

Core::RGB Button::currentColor() {
	if(mouseWithinBounds()) return hoverColor;
	return defaultColor;
}