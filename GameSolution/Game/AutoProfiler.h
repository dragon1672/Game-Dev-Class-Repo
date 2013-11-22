#pragma once
#ifndef AUTO_PROFILE_H
#define AUTO_PROFILE_H

#include "Timer.h"
#include "AutoProfileManager.h"

class AutoProfile {
private:
	const char* profileName;
	Timer myTimer;
	void printToFile();
public:
	AutoProfile(const char* name) {
		profileName = name;
		myTimer.start();
	}
	~AutoProfile() {
		myTimer.stop();
		AutoProfileManager::addEntry(profileName,myTimer.getElapsedTime());
	}
};

#endif