#pragma once
#ifndef AUTO_PROFILE_MANAGER_H
#define AUTO_PROFILE_MANAGER_H

#include "ProfileCategory.h"

const int MAX_CATEGORIES = 20;
#define PROFILE_FILE_NAME "../Profile.csv"


//ENABLE PROFILING?????
#define ENABLE_PROFILING


class AutoProfile;

class AutoProfileManager {
#ifdef ENABLE_PROFILING
private:
	static int numberOfProfiles;
	static ProfileCategory categories[MAX_CATEGORIES];
		
	static void addNewProfile(const char* description, float time);
	static int  indexOfProfile(const char* description);
	static void addToProfile(int i, float time);
public:
	static void startup();//sets numberOfProfiles to 0
	static void shutdown();//not currently required
	//will create a new profile if needed
	static void addEntry(const char* description, float time);
	static void writeToFile();
#else 
	private:
	static int numberOfProfiles;
	static ProfileCategory categories[MAX_CATEGORIES];
		
	static void addNewProfile(const char* description, float time) {}
	static int  indexOfProfile(const char* description) {}
	static void addToProfile(int i, float time) {}
public:
	static void startup() {}
	static void shutdown() {}
	static void addEntry(const char* description, float time) {}
	static void writeToFile() {}
#endif
};

#include "AutoProfiler.h"
#include "AutoProfileManagerMacros.h"

#endif