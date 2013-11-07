#pragma once
#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include "ExportHeader.h"

namespace Random {
	ENGINE_SHARED int   randomnumber(int low, int high);
	ENGINE_SHARED float randomFloat(float low, float high);
	ENGINE_SHARED void  init();
}

#endif//MY_RANDOM_H
