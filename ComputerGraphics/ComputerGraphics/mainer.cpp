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

#include <Engine\SceneManager.h>



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
	PassInfoDemo tab2; widg.addScene(&tab2);
	UsingNoise tab1; widg.addScene(&tab1);
	//*/

	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}