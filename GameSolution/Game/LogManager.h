#pragma once
#ifndef LOGGING_H
#define LOGGING_H

//#define LOGGING

enum Severity {
	Info, Warning, Error, Severe
};

#ifndef LOGGING
#else
#endif//LOGGING

/* Verbose Levels
 * 0 - prints the first instance of a log call Verbose 0
 * 1 - prints second instances of a log call Verbose 0 and all first instances of log call Verbose 1
 * 2-n Repeat pattern
 * second instance will automatically increment the passed verbosity level
//*/

struct BasicLog {
	Severity severity;
	const char* location;
	const char* file;
	const char* message;
	int verbosity;
	float timeStamp;
};

#include "Timer.h"
#define LOG_OUTPUT_FILE "../Log Report.html"

class LogManager {
private:
	Timer myTimer;//stores timestamp
	bool storeDuplicates;
	BasicLog myLogs[100];
	int numOfLogs;

	int getEntry(const char *location, const char *file, const char *message, int startingIndex = 0);
	void addNewLog(const char *location, const char *file, const char *message, Severity severity, int verbosity);
	void updateLog(int index, const char *location, const char *file, const char *message, Severity severity, int verbosity);
public:
	LogManager() {
		numOfLogs = 0;
		storeDuplicates = true;
	}
	void addEntriy(const char *location, const char *file, const char *message, Severity severity, int verbosity=0);
	void writeToFile();
};

#endif