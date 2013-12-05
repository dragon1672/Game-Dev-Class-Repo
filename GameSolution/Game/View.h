#pragma once
#ifndef VIEW_H
#define VIEW_H

#include "Core.h"

class View {
public:
	virtual bool update(float dt)=0;//true mean it is complete
	virtual void draw(Core::Graphics& graphics)=0;
};

#endif