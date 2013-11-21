#include "StaticPos.h"

void StaticPos::setPos(const Vector2D& pos) {
	this->pos = pos;
}
Vector2D StaticPos::getPos() {
	return pos;
}