#include <GL\glew.h>
#include "MyWindow.h"
#include "MyRandom.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"


#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <Qt/qdebug.h>

#include <ShapeGenerator.h>
#include "BinaryToShapeLoader.h"
#include "NUShapeEditor.h"

#include "SingleKeyManager.h"


using glm::vec3;
using glm::vec4;
using glm::mat4x4;


void MyWindow::initializeGL() {
	glewInit();
	myRender.init();
	myDebugShapes.init(&myRender, &viewTransform[0][0]);

	myRender.mainShader->buildBasicProgram("../Shaders/VertexShader.glsl","../Shaders/FragShader.glsl");

	sendDataToHardWare();

	setMouseTracking(true);
	
	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
}

void MyWindow::init() {
	//setting defaults
	myCam.setPos(vec3(20,20,20),vec3(-1,-1,-1));
}
void MyWindow::loadGeo(const char * binaryFilePath) {
	Neumont::ShapeData fromFile = BinaryToShapeLoader::loadFromFile(binaryFilePath);
	levelRenderable->whatGeo = myRender.addGeometry(fromFile,GL_TRIANGLES);
}

void MyWindow::sendDataToHardWare() {
	mainTextureId = myRender.addTexture("\\..\\Textures\\mainTexture.png");

	numOfGameObjs = 0;

	myRender.mainShader -> saveUniform("viewTransform",       ParameterType::PT_MAT4,     &viewTransform[0][0] );
	levelRenderable = myRender.addRenderable(myRender.addGeometry(Neumont::ShapeGenerator::makePlane(30),GL_TRIANGLES),myRender.mainShader,mainTextureId);
	levelRenderable->saveWhereMat("model2WorldTransform");
	levelRenderable->saveTexture("myTexture");

	gameObjs[numOfGameObjs++] = levelRenderable;
}

SingleKeyManager KEY_ADD_NODE         (' '); // add node
SingleKeyManager KEY_SPHERE           ('1'); // sphere
SingleKeyManager KEY_CUBE             ('2'); // cube
SingleKeyManager KEY_POINT            ('3'); // point
SingleKeyManager KEY_VEC              ('4'); // vector orgin to pos
SingleKeyManager KEY_LINE             ('5'); // line orgin to pos
SingleKeyManager KEY_INCREASE_LIFETIME(VK_UP);
SingleKeyManager KEY_DECREASE_LIFETIME(VK_DOWN);
SingleKeyManager KEY_INF_LIFETIME     ('0');
#include <limits>
uint currentLifeTime = 1;
bool lifetimeInf = true;
const uint lifetimeIncrementor = 1;

void MyWindow::addNode() {
	QPoint p = mapFromGlobal(QCursor::pos());
	float x = (2.0f*p.x())/width() - 1.0f;
	float y = 1.0f - (2.0f* p.y())/height();
	float z = -1.0f;

	mat4x4 undoCam = glm::inverse(myCam.getWorld2View());

	vec4 temp = glm::inverse(viewTransform * undoCam) * vec4(x,y,z,0.0);

	vec3 rayDirection = glm::normalize(vec3(undoCam * vec4(temp.x,temp.y,z,0.0)));
	
	vec3 rayOrigin = myCam.getPos();
	

	vec3 planeNormal = vec3(0,1,0);
	float denominator = glm::dot(rayDirection,planeNormal);
	if(denominator != 0) // 
	{
		vec3 planePointToRayOrigin = vec3(0,1,0) - rayOrigin;
		float neumorator = glm::dot(planePointToRayOrigin, planeNormal);
		float distance = neumorator/denominator;
		if(distance >= 0) {
			vec3 positionToPlace = rayOrigin + rayDirection * distance;
			myDebugShapes.addUnitSphere(glm::translate(positionToPlace),vec4(0,0,1,1));
		}
	}
}

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/
	KEY_ADD_NODE.update(.1f);
	KEY_SPHERE.update(.1f);
	KEY_CUBE.update  (.1f);
	KEY_POINT.update (.1f);
	KEY_VEC.update   (.1f);
	KEY_LINE.update  (.1f);
	KEY_INCREASE_LIFETIME.update(.1f);
	KEY_DECREASE_LIFETIME.update(.1f);
	KEY_INF_LIFETIME.update     (.1f);

	float lifetime = (lifetimeInf)? std::numeric_limits<float>::infinity() : currentLifeTime;
	// HIPPO
	if(KEY_SPHERE.hasBeenClicked()) { myDebugShapes.addUnitSphere(glm::translate(myCam.getPos()+myCam.getViewDir()),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_CUBE.hasBeenClicked())   { myDebugShapes.addUnitCube  (glm::translate(myCam.getPos()+myCam.getViewDir()),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_POINT.hasBeenClicked())  { myDebugShapes.addPoint(myCam.getPos()+myCam.getViewDir(),lifetime); }
	if(KEY_VEC.hasBeenClicked())    { myDebugShapes.addUnitVector(glm::vec3(0,0,0),myCam.getPos()+myCam.getViewDir(),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_LINE.hasBeenClicked())   { myDebugShapes.addLine(glm::vec3(0,0,0),myCam.getPos()+myCam.getViewDir(),glm::vec4(0,.5f,1,1),lifetime); }
	if(KEY_INCREASE_LIFETIME.hasBeenClicked())  { currentLifeTime += lifetimeIncrementor; }
	if(KEY_DECREASE_LIFETIME.hasBeenClicked())  { currentLifeTime -= lifetimeIncrementor; }
	if(KEY_INF_LIFETIME.hasBeenClicked())  { lifetimeInf = !lifetimeInf; }
	currentLifeTime = currentLifeTime < 1 ? 1 : currentLifeTime;

	if(KEY_ADD_NODE.hasBeenClicked()) { addNode(); }
	
	
	if(frames%100==0) {
		//qDebug() << "Cam Pos { " << myCam.getPos().x   <<   ", " << myCam.getPos().y   <<   ", " << myCam.getPos().z   <<   " }";
		//qDebug() << "Cam View{ " << myCam.getViewDir().x << ", " << myCam.getViewDir().y << ", " << myCam.getViewDir().z << " }";
	}

	myDebugShapes.update(.1f);

	repaint();
}
void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	if(GetAsyncKeyState(VK_LBUTTON)!=0) {
		glm::vec2 newPos(e->x(),e->y());
		myCam.updateMousePos(newPos);
	}
}
void MyWindow::keyPressEvent(QKeyEvent* e) {
	if(e->key() == Qt::Key::Key_W) {
		myCam.moveForward();
	} else if(e->key() == Qt::Key::Key_S) {
		myCam.moveBackward();
	} else if(e->key() == Qt::Key::Key_A) {
		myCam.moveLeft();
	} else if(e->key() == Qt::Key::Key_D) {
		myCam.moveRight();
	} else if(e->key() == Qt::Key::Key_R) {
		myCam.moveUp();
	} else if(e->key() == Qt::Key::Key_F) {
		myCam.moveDown();
	}
}

void MyWindow::paintGL() {
	myRender.drawPrep(width(),height());
	
	const float aspectRatio = (float)width()/(float)height();
	viewTransform = glm::mat4();
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();


	myRender.resetAllShaders_validPush();
	myRender.mainShader->useProgram();

	for (uint i = 0; i < numOfGameObjs; i++)
	{
		myRender.draw(*gameObjs[i]);
	}

	myDebugShapes.draw();
}