#include <Qt/qapplication.h>
#include "LabOne.h"
#include "DebugMenuDemo.h"
#include "AlphaBlending.h"
#include "NormalMaps.h"
#include "TangentSpace.h"
#include "Orge.h"
#include <Engine\BasicGui.h>
#include "LibNoiseDemo.h"
#include "noise.h"

#include "UsingNoise.h"
#include "PassInfoDemo.h"
#include "Shadows.h"
#include "CubeMap.h"

#include <Engine\SceneManager.h>

#define ADD_SCENE(uniqueName,type) type uniqueName; widg.addScene(&uniqueName)


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	BasicGui GUI;

	//LabOne widg;
	//DebugMenuDemo widg;
	//AlphaBlending widg;
	//NormalMaps widg;
	//TangentSpace widg;
	//Orge widg;
	//LibNoise widg;
	//Noise widg;
	
	//*
	SceneManager widg;
	ADD_SCENE(tab2,PassInfoDemo);
	ADD_SCENE(tab1,UsingNoise);
	ADD_SCENE(tab3,Shadows);
	ADD_SCENE(tab4,CubeMap);
	//*/

	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}