#include "LogManager.h"
#include <fstream>

int  LogManager::getEntry(const char* location, const char *file, const const char *message, int startingIndex) {
	for(int i=startingIndex;i<numOfLogs;i++) {
		if(myLogs[i].message == message
			&& myLogs[i].location == location
			&& myLogs[i].file == file) return i;
	}
	return -1;
}
void LogManager::addNewLog(const char *location, const char *file, const char *message, Severity severity, int verbosity) {
	int index = numOfLogs++;
	updateLog(index,location,file,message,severity,verbosity);

}
void LogManager::updateLog(int index, const char *location, const char *file, const char *message, Severity severity, int verbosity) {
	myLogs[index].location  = location;
	myLogs[index].file      = file;
	myLogs[index].message   = message;
	myLogs[index].severity  = severity;
	myLogs[index].verbosity = verbosity;
	myLogs[index].timeStamp = myTimer.getCurrentTime();
}
void LogManager::addEntriy(const char *location, const char *file, const char *message, Severity severity, int verbosity) {
	int index = getEntry(location,file,message);
	if(index<0) {
		addNewLog(location,file,message,severity,verbosity);
	} else if(storeDuplicates) {
		addNewLog(location,file,message,severity,verbosity+1);
	}
}

const char* severity2Col(Severity input) {
	switch (input) {
	case Severity::Info:
		return "0x0099FF"; // blue
		break;
	case Severity::Warning:
		return "0xFFCC00"; // orange
		break;
	case Severity::Error:
		return "0xFF0000"; // red
		break;
	case Severity::Severe:
		return "0xCC0000"; // dark red
		break;
	}
	return "???";
}
namespace LOG_HTML_CONSTS {
	const char* HTML_LOG_START = "<HTML>\n<head>\n<title>Game Log File</title>\n</head>\n<body>\n";
	const char* HTML_LOG_END   = "</body>\n</HTML>";
	const char* FOOTER = "<center>Created By:<br/>Anthony Corbin</center>";
}

void LogManager::writeToFile() {
	std::ofstream logFile;
	logFile.open (LOG_OUTPUT_FILE);
	//headers
	logFile << LOG_HTML_CONSTS::HTML_LOG_START;
	//headers
	logFile << "<table>\n<tr>\n"
			<< "<td><b>Severity  </b></td>\n"
			<< "<td><b>Location  </b></td>\n"
			<< "<td><b>File      </b></td>\n"
			<< "<td><b>Message   </b></td>\n"
			<< "<td><b>Timestamp </b></td>\n"
			<< "<td><b>Verbosity </b></td>\n"
			<< "</tr>\n";
	for(int i=0;i<numOfLogs;i++) {
		logFile << "<tr>\n";
		logFile << "<td><font color=\"" << severity2Col(myLogs[i].severity) << "\">" << myLogs[i].severity  << "</font></td>\n"
				<< "<td><font color=\"" << severity2Col(myLogs[i].severity) << "\">" << myLogs[i].location  << "</font></td>\n"
				<< "<td><font color=\"" << severity2Col(myLogs[i].severity) << "\">" << myLogs[i].file      << "</font></td>\n"
				<< "<td><font color=\"" << severity2Col(myLogs[i].severity) << "\">" << myLogs[i].message   << "</font></td>\n"
				<< "<td><font color=\"" << severity2Col(myLogs[i].severity) << "\">" << myLogs[i].timeStamp << "</font></td>\n"
				<< "<td><font color=\"" << severity2Col(myLogs[i].severity) << "\">" << myLogs[i].verbosity << "</font></td>\n";
		logFile << "</tr>\n";
	}
	logFile << "</table>\n";
	
	logFile << LOG_HTML_CONSTS::FOOTER;
	logFile << LOG_HTML_CONSTS::HTML_LOG_END;
	logFile.close();
}