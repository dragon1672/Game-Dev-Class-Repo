#pragma once

#include <glm\glm.hpp>
#include <QtGui\QHBoxLayout>
#include <QtGui\QVBoxLayout>
#include <QtGui\qgridlayout.h>
#include <QtGui\qwidget.h>
#include "ExportHeader.h"

#include "WatchFloatController.h"
#include "SlideFloatController.h"
#include "BoolToggleController.h"
#include "WatchVectorController.h"
#include "SlideVectorController.h"
#include <vector>

class ENGINE_SHARED DebugMenuManager {
	static DebugMenuManager singleTon;
	//inline DebugMenuManager * getSingleTon() { &singleTon; }
#ifdef _DEBUG
	QHBoxLayout mainLayout;
	std::vector<DebugMenuControllers::WatchFloatController  *> floatWatchers;	QVBoxLayout floatWatchCol;
	std::vector<DebugMenuControllers::SlideFloatController  *> floatSliders;	QVBoxLayout floatSlideCol;
	std::vector<DebugMenuControllers::BoolToggleController  *> bools;			QVBoxLayout boolCol;
	std::vector<DebugMenuControllers::WatchVectorController *> vecWatchers;		QVBoxLayout vecWatchCol;
	std::vector<DebugMenuControllers::SlideVectorController *> vecSliders;		QVBoxLayout vecSlideCol;

	//stuff and things
public:
	
	void init(QLayout * toAdd);
	void update();
	void watchFloat (char * name, float& toWatch);
	void slideFloat (char * name, float& toWatch);
	void toggleBool (char * name, bool& toWatch);
	void watchVector(char * name, glm::vec3& toWatch);
	void slideVector(char * name, glm::vec3& toWatch, float min, float max);
#else
public:
	void init(/*layout pos pointer*/) {}
	void update() {}
	void watchFloat (char * name, float& toWatch) {} // watches the value in a text text box
	void slideFloat (char * name, float& toWatch) {}//allows slider to change float
	void toggleBool (char * name, bool& toWatch) {} // display a check box
	void watchVector(char * name, glm::vec3& toWatch) {}
	void slideVector(char * name, glm::vec3& toWatch) {}
#endif
};