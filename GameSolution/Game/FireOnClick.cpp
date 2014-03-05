#include "FireOnClick.h"
#include "Core.h"

void FireOnClick::setKey(int toSet) {
	key = toSet;
}

bool FireOnClick::fired() {
	return Core::Input::IsPressed( key );
}