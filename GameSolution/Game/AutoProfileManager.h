#pragma once
#ifndef AUTO_PROFILE_MANAGER_H
#define AUTO_PROFILE_MANAGER_H



#define ENABLE_PROFILING
#define PROFILE_FILE_NAME "Profile.csv"

class AutoProfile;

#ifdef ENABLE_PROFILING//1==1 included to require ';'
	#define START_PROFILING AutoProfileManager::startup()
	#define PROFILE(a) {AutoProfile(a) //starting Profile
	#define END_PROFILE }1==1 //end the last Profile
	#define LOG_CURRENT_PROFILE AutoProfileManager::writeToFile()
	#define STOP_PROFILING AutoProfileManager::shutdown()
#else // filled with dummy data (still requires ';')
	#define START_PROFILING 1==1
	#define PROFILE(a) 1==1
	#define END_PROFILE 1==1
	#define LOG_CURRENT_PROFILE 1==1
	#define STOP_PROFILING 1==1
#endif

const int MAX_CATEGORIES = 20;
const int MAX_FRAMES_TO_MESURE = 50;

struct profileCategory {
	profileCategory() {
		this->name = "";
		timesCalled = 0;
		totalTime = 0;
	}
	const char* name;
	int timesCalled;//also index for data
	float totalTime;
	float data[MAX_FRAMES_TO_MESURE];
	//float averageTime = totalTime / timesCalled;
};

class AutoProfileManager {
private:
	static int numberOfProfiles;
	static profileCategory categories[MAX_CATEGORIES];

	static void addNewProfile(const char* description, float time);
	static int  indexOfProfile(const char* description);
	static void addToProfile(int i, float time);
public:
	static void startup();//sets numberOfProfiles to 0
	static void shutdown();//not currently required
	//will create a new profile if needed
	static void addEntry(const char* description, float time);
	static void writeToFile();
};

#include "AutoProfiler.h"

#endif