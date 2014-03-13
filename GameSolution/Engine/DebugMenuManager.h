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
#ifdef _DEBUG
private:
	QHBoxLayout mainLayout;
	std::vector<DebugMenuControllers::WatchFloatController  *> floatWatchers;	QVBoxLayout floatWatchCol;
	std::vector<DebugMenuControllers::SlideFloatController  *> floatSliders;	QVBoxLayout floatSlideCol;
	std::vector<DebugMenuControllers::BoolToggleController  *> bools;			QVBoxLayout boolCol;
	std::vector<DebugMenuControllers::WatchVectorController *> vecWatchers;		QVBoxLayout vecWatchCol;
	std::vector<DebugMenuControllers::SlideVectorController *> vecSliders;		QVBoxLayout vecSlideCol;

	//stuff and things
public:
	void init(QLayout * toAdd) {
		toAdd->addItem(&mainLayout);
		mainLayout.addLayout(&floatWatchCol);
		mainLayout.addLayout(&floatSlideCol);
		mainLayout.addLayout(&boolCol);
		mainLayout.addLayout(&vecWatchCol);
		mainLayout.addLayout(&vecSlideCol);
	}
	void update() {
		for (int i = 0; i < floatWatchers.size(); i++) { floatWatchers[i]->update();          }
		for (int i = 0; i < floatSliders.size();  i++) { floatSliders[i]->updateGUItoModel(); }
		for (int i = 0; i < bools.size();         i++) { bools[i]->updateGUItoModel();        }
		for (int i = 0; i < vecWatchers.size();   i++) { vecWatchers[i]->update();            }
		for (int i = 0; i < vecSliders.size();    i++) { vecSliders[i]->updateGUItoModel();   }
	}
	void watchFloat (char * name, float& toWatch)	  {
		DebugMenuControllers::WatchFloatController * toAdd;
		toAdd->init(name,&toWatch);
		floatWatchers.push_back(toAdd);

		QHBoxLayout * newRow = new QHBoxLayout();
		newRow->addWidget(&(toAdd->label));
		floatWatchCol.addLayout(newRow);
	}
	void slideFloat (char * name, float& toWatch)	  {
		DebugMenuControllers::SlideFloatController * toAdd;
		toAdd->init(name,&toWatch);
		floatSliders.push_back(toAdd);

		QHBoxLayout * newRow = new QHBoxLayout();
		newRow->addWidget(&(toAdd->label));
		newRow->addWidget(&(toAdd->slider));
		floatWatchCol.addLayout(newRow);
	}
	void toggleBool (char * name, bool& toWatch)	  {
		DebugMenuControllers::BoolToggleController * toAdd;
		toAdd->init(name,&toWatch);
		bools.push_back(toAdd);

		QHBoxLayout * newRow = new QHBoxLayout();
		newRow->addWidget(&(toAdd->checkBox));
		boolCol.addLayout(newRow);
	}
	void watchVector(char * name, glm::vec3& toWatch) {
		DebugMenuControllers::WatchVectorController * toAdd;
		toAdd->init(name,&toWatch);
		vecWatchers.push_back(toAdd);

		QHBoxLayout * newRow = new QHBoxLayout();
		newRow->addWidget(&(toAdd->label));
		vecWatchCol.addLayout(newRow);
	}
	void slideVector(char * name, glm::vec3& toWatch, float min, float max) {
		DebugMenuControllers::SlideVectorController * toAdd;
		toAdd->init(name,&toWatch,min,max);
		vecSliders.push_back(toAdd);

		QHBoxLayout * newRow = new QHBoxLayout();
		newRow->addWidget(&(toAdd->label));
		newRow->addWidget(&(toAdd->xSlider));
		newRow->addWidget(&(toAdd->ySlider));
		newRow->addWidget(&(toAdd->zSlider));
		vecSlideCol.addLayout(newRow);
	}
#else
	void init(/*layout pos pointer*/) {}
	void update() {}
	void watchFloat (char * name, float& toWatch) {} // watches the value in a text text box
	void slideFloat (char * name, float& toWatch) {}//allows slider to change float
	void toggleBool (char * name, bool& toWatch) {} // display a check box
	void watchVector(char * name, glm::vec3& toWatch) {}
	void slideVector(char * name, glm::vec3& toWatch) {}
#endif
};