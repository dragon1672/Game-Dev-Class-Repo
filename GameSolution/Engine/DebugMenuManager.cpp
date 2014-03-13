#include "DebugMenuManager.h"

void DebugMenuManager::init(QLayout * toAdd) {
	toAdd->addItem(&mainLayout);
	mainLayout.addLayout(&floatWatchCol);
	mainLayout.addLayout(&floatSlideCol);
	mainLayout.addLayout(&boolCol);
	mainLayout.addLayout(&vecWatchCol);
	mainLayout.addLayout(&vecSlideCol);
}
void DebugMenuManager::update() {
	for (int i = 0; i < floatWatchers.size(); i++) { floatWatchers[i]->update();          }
	for (int i = 0; i < floatSliders.size();  i++) { floatSliders[i]->updateGUItoModel(); }
	for (int i = 0; i < bools.size();         i++) { bools[i]->updateGUItoModel();        }
	for (int i = 0; i < vecWatchers.size();   i++) { vecWatchers[i]->update();            }
	for (int i = 0; i < vecSliders.size();    i++) { vecSliders[i]->updateGUItoModel();   }
}
void DebugMenuManager::watchFloat (char * name, float& toWatch)	  {
	DebugMenuControllers::WatchFloatController * toAdd;
	toAdd->init(name,&toWatch);
	floatWatchers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(&(toAdd->label));
	floatWatchCol.addLayout(newRow);
}
void DebugMenuManager::slideFloat (char * name, float& toWatch)	  {
	DebugMenuControllers::SlideFloatController * toAdd;
	toAdd->init(name,&toWatch);
	floatSliders.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(&(toAdd->label));
	newRow->addWidget(&(toAdd->slider));
	floatWatchCol.addLayout(newRow);
}
void DebugMenuManager::toggleBool (char * name, bool& toWatch)	  {
	DebugMenuControllers::BoolToggleController * toAdd;
	toAdd->init(name,&toWatch);
	bools.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(&(toAdd->checkBox));
	boolCol.addLayout(newRow);
}
void DebugMenuManager::watchVector(char * name, glm::vec3& toWatch) {
	DebugMenuControllers::WatchVectorController * toAdd;
	toAdd->init(name,&toWatch);
	vecWatchers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(&(toAdd->label));
	vecWatchCol.addLayout(newRow);
}
void DebugMenuManager::slideVector(char * name, glm::vec3& toWatch, float min, float max) {
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