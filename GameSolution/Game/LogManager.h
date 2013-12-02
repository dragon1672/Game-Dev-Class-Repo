#pragma once
#ifndef LOGGING_H
#define LOGGING_H

#include <vector>//used to store logs
#include "LogData.h"

#define LOG_ON

#define LOG( severity, message, verbosity) LogManager::Log( severity, message, __FILE__, __LINE__,verbosity)
#define END_LOG LogManager::shutDown();

#pragma warning ( disable : 4100)

class LogManager {
public:
#ifdef LOG_ON
	LogManager(void);
	~LogManager(void);
	static void StringReplace(std::string& str, const std::string& from, const std::string& to);
	static void Log( Severity severity, const char* message, const char * logFile, int logLine, int verbosity);
	static void shutDown();
	static const int verbosityLevel = 0;
#else
	LogManager(void){}
	~LogManager(void){}
	static void StringReplace(std::string& str, const std::string& from, const std::string& to) {}
	static void Log( Severity severity, const char* message, const char * logFile, int logLine, int verbosity) {}
	static void shutDown() {}
	static const int verbosityLevel = 0;
#endif

private:
#ifdef LOG_ON
	static std::vector <LogData> logList;
	static void WriteFile();
	static std::string Sanitize(std::string str);
	static void Sanitize(LogData * toClean);
	static int indexOfLog(std::string& location, int lineNum, std::string& message, int startingIndex, int endIndex);
	static int indexOfLog(LogData& toFind, int startingIndex, int endIndex);
#endif
};

#pragma warning ( default : 4100)

#endif