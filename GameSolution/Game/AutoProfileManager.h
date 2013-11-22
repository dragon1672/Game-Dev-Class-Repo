#pragma once
#ifndef AUTO_PROFILE_MANAGER_H
#define AUTO_PROFILE_MANAGER_H



//#define ENABLE_PROFILING
#define PROFILE_FILE_NAME "Profile.csv"


#ifdef ENABLE_PROFILING
	#define START_PROFILING AutoProfileManager::startup();
	#define PROFILE(a) {AutoProfile(a); //starting Profile
	#define END_PROFILE } //end the last Profile
	#define LOG_CURRENT_PROFILE AutoProfileManager.writeToFile();
	#define STOP_PROFILING AutoProfileManager.shutdown();
#else
	#define START_PROFILING
	#define PROFILE(a)
	#define END_PROFILE
	#define LOG_CURRENT_PROFILE
	#define STOP_PROFILING
#endif


class AutoProfileManager {
public:
	static void startup();
	static void shutdown();
	static void writeToFile();
	static void addEntry(const char* description, float time);
};

#endif