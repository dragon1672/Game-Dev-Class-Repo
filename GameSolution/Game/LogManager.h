#pragma once
#ifndef LOGGING_H
#define LOGGING_H

#include <vector>//used to store logs
#include "LogData.h"

#define LOG_ON

#pragma warning(disable:4127)//conditional with constent (aka the while(0))

#define LOG(severity, message, verbosity) LogManager::Log( severity, message, __FILE__, __LINE__,verbosity)

#define LOG_SEVERITY(level) do {												\
								LOG(Info, "-----------------Chaging Severity To: "#level, 0);	\
								LogManager::changeverbosityLevel(level);				\
								} while(0)

#define END_LOG LogManager::shutDown()

#pragma warning ( disable : 4100)

class LogManager {
public:
#ifdef LOG_ON
	LogManager(void);
	~LogManager(void);
	static void StringReplace(std::string& str, const std::string& from, const std::string& to);
	static void Log( Severity severity, const char* message, const char * logFile, int logLine, int verbosity);
	static void shutDown();
	static int  verbosityLevel;
	static void changeverbosityLevel(int toSet);
#else
	LogManager(void){}
	~LogManager(void){}
	static void StringReplace(std::string& str, const std::string& from, const std::string& to) {}
	static void Log( Severity severity, const char* message, const char * logFile, int logLine, int verbosity) {}
	static void shutDown() {}
	static int verbosityLevel;
#endif

private:
#ifdef LOG_ON
	static std::vector <LogData> logList;
	static void WriteFile();
	static std::string Sanitize(std::string str);
	static void Sanitize(LogData * toClean);
#endif
};

#pragma warning ( default : 4100)

#endif