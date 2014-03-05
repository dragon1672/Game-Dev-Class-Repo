#pragma once
#ifndef DEBUG_TIMER_H
#define DEBUG_TIMER_H

#include "Timer.h"

#define START_GLOBAL_TIMER DebugTimer::init()
#define END_GLOBAL_TIMER DebugTimer::shutdown()
#define GET_GLOBAL_TIME DebugTimer::getTime()

class DebugTimer {
private:
	static Timer myTimer;
public:
	static void  init();
	static float getTime();
	static void  shutdown();
};

#endif