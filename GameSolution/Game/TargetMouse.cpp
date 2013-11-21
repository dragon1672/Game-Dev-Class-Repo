#include "TargetMouse.h"
#include "Core.h"

Vector2D TargetMouse::getPos() {
	return Vector2D(Core::Input::GetMouseX(),Core::Input::GetMouseY());
}