#pragma once
#ifndef Partical_Text_Format_h
#define Partical_Text_Format_h

#include "TextFormatting.h"
#include "DynamicPosition.h"

class ParticalTextFormat : public TextFormatting {
public:
	bool slowEffect;
	DynamicPosition *spawnLocation;
};

#endif