#include "TargetMouse.h"
#include "Core.h"

void     TargetMouse::init(const Vector2D& offset) {
	this->offset = offset;
}
Vector2D TargetMouse::getPos() {
	return offset + Vector2D((float)Core::Input::GetMouseX(),(float)Core::Input::GetMouseY());
}