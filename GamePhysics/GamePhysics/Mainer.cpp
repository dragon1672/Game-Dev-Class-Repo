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
#include "Lab13RigidBodyRotation\RigidBodyRotation.h"
#include "Lab14Torque\TorqueGUI.h"

#define SHOW(type) type widg; \
						  widg.init(); \
						  widg.show(); \

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	//SHOW(BasicVelocityAndAcc);
	//SHOW(BasicMomentum);
	//SHOW(ForceAccumulationGui);
	//SHOW(DragForceGUI);
	//SHOW(SpringGUI);
	//SHOW(WaveGui);
	//SHOW(CollisionGUI);
	//SHOW(RestingCollisionGUI);
	//SHOW(RestingContactGUI);
	//SHOW(ParticleWorldGUI);
	//SHOW(AngleVelGUI);
	//SHOW(RigidBodyRotation);	
	SHOW(TorqueGUI);	

	return app.exec();
}