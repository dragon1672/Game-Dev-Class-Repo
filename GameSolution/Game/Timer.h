#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

class Timer {
private:
	LARGE_INTEGER _start;
	LARGE_INTEGER _stop;
	LARGE_INTEGER _lastInterval;
	LARGE_INTEGER total;//used for pause/resume
	LARGE_INTEGER frequency;
	float LargeInt2Secs( LARGE_INTEGER & L);
public:
	Timer();
	void start();
	void stop();
	void pause();
	void resume();
	float interval();
	float getElapsedTime();
};

#endif