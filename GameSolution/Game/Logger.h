/*
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

struct BasicLog {
	Severity severity;
	const char* message;
};

class LogManager {
private:
	BasicLog[100];
public:

};

#endif
//*/