#pragma once
#ifndef AUTO_PROFILE_H
#define AUTO_PROFILE_H

#include "Timer.h"

#define ENABLE_PROFILING

#ifdef ENABLE_PROFILING
	#define PROFILE_FILE_NAME "Profile.csv"
	#define PROFILE(a) {AutoProfile(#a); //starting Profile
	#define END_PROFILE } //end the last Profile
#else
	#define PROFILE_FILE_NAME "Profile.csv"
	#define PROFILE(a)
	#define END_PROFILE
#endif

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
		printToFile();
	}
};

#endif