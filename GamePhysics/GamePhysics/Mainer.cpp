#include <Qt/qapplication.h>
#include "Lab01VA\BasicVelocityAndAcc.h"
#include "Lab02FMA\BasicMomentum.h"
#include "Lab03Force\ForceAccumulationGui.h"
#include "Lab04DragForce\DragForceGUI.h"
#include "Lab05Springs\SpringGUI.h"
#include "Lab05Springs\WavesGUI.h"
#include "Lab07Collision\CollisionGUI.h"
#include "Lab09RestingCollision\RestingCollisionGUI.h"
#include "Lab10RestingContact\RestingContactGUI.h"
#include "Lab11ParticleWorld\ParticleWorldGUI.h"
#include "Lab12AngleVel\AngleVelGUI.h"

#define SHOW_IT_OFF(type) type widg; \
						  widg.init(); \
						  widg.show(); \

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	//SHOW_IT_OFF(BasicVelocityAndAcc);
	//SHOW_IT_OFF(BasicMomentum);
	//SHOW_IT_OFF(ForceAccumulationGui);
	//SHOW_IT_OFF(DragForceGUI);
	//SHOW_IT_OFF(SpringGUI);
	//SHOW_IT_OFF(WaveGui);
	//SHOW_IT_OFF(CollisionGUI);
	//SHOW_IT_OFF(RestingCollisionGUI);
	//SHOW_IT_OFF(RestingContactGUI);
	//SHOW_IT_OFF(ParticleWorldGUI);
	SHOW_IT_OFF(AngleVelGUI);

	return app.exec();
}