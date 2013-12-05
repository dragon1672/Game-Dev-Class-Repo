#include "Button.h"

Core::RGB Button::DEFAULT_hoverColor   = RGB(150,150,150);
Core::RGB Button::DEFAULT_defaultColor = RGB(100,100,100);

void Button::init(DynamicPosition * cursor, Vector2D& pos, const char* text, int width, int height, Core::RGB setHoverColor, Core::RGB setDefaultColor) {
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
	return mouseWithinBounds() && Core::Input::IsPressed(Core::Input::BUTTON_LEFT);
}

Core::RGB Button::currentColor() {
	if(mouseWithinBounds()) return hoverColor;
	return defaultColor;
}