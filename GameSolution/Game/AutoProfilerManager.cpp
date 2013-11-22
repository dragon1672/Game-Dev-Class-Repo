#include "AutoProfileManager.h"
#include <iostream>
#include <fstream>


void AutoProfileManager::startup() {

}
void AutoProfileManager::shutdown() {

}
void AutoProfileManager::writeToFile() {
	std::ofstream profileOutput;
	profileOutput.open (PROFILE_FILE_NAME);
	//profileOutput << profileName << "," << myTimer.getElapsedTime() << "\n";
	profileOutput.close();
}
void AutoProfileManager::addEntry(const char* description, float time) {

}