#include "AutoProfiler.h"
#include <iostream>
#include <fstream>


void AutoProfile::printToFile() {
	std::ofstream profileOutput;
	profileOutput.open (PROFILE_FILE_NAME);
	profileOutput << profileName << "," << myTimer.getElapsedTime() << "\n";
	profileOutput.close();
}