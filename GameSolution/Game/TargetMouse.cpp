#include "TargetMouse.h"
#include "Core.h"

Vector2D TargetMouse::getPos() {
	return Vector2D((float)Core::Input::GetMouseX(),(float)Core::Input::GetMouseY());
}