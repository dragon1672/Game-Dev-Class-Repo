#pragma once

#include <Engine/WidgetRenderer.h>

class LibNoise : public WidgetRenderer {
public:
	void init();

	void nextFrame(float dt);
};