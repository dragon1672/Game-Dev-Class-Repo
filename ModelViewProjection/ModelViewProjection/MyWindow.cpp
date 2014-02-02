#include <GL\glew.h>
#include "MyWindow.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "MyRandom.h"

#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <Qt/qdebug.h>

#include <ShapeGenerator.h>


using glm::vec3;
using glm::mat4x4;

Neumont::ShapeData singleShape;

float orbitAngle;
float orbitAcc = .2f;

void MyWindow::initializeGL() {
	glewInit();

	glEnable(GL_DEPTH_TEST);

	sendDataToHardWare();
	
	initShaders();

	connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
	myTimer.start(0);
}

void MyWindow::init() {
	//setting defaults
	enableOverrideColor = true;
	displayLightEntity = true;
	myCam.setPos(vec3(17,3.7f,-15),vec3(-50,-13,85));
	overrideColor = vec3(1,1,1);
	ambientLight = vec3(.1,.1,.1);
	diffuseLight = vec3(1,1,1);
	diffusePos = vec3(0,10,0);
	diffuseInFrag = true;
}
void MyWindow::initShaders() {
	myShadyShader.startup();
	myShadyShader.addProgram("VertexShader.glsl",GL_VERTEX_SHADER);
	myShadyShader.addProgram("FragShader.glsl",GL_FRAGMENT_SHADER);
	myShadyShader.compileAndRun();
}

//returns the required size
int initShapeData(int &counter, DrawnObj * theArray) {
	Neumont::ShapeData models[6];
	
	models[0] = Neumont::ShapeGenerator::makeTeapot(10,glm::mat4());
	models[1] = Neumont::ShapeGenerator::makeTorus(10);
	models[2] = Neumont::ShapeGenerator::makeArrow();
	models[3] = Neumont::ShapeGenerator::makeSphere(10);
	models[4] = Neumont::ShapeGenerator::makeCube();
	models[5] = Neumont::ShapeGenerator::makePlane(10);

	counter = 0;
	uint currentOffset = 0;

	for (int i = 0; i < sizeof(models)/sizeof(*models); i++)
	{
		theArray[counter].init(models[i], currentOffset);
		currentOffset = theArray[counter].endOffset();
		
		counter++;
	}

	return currentOffset;
}

void MyWindow::sendDataToHardWare() {
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	numOfGameObjs = 0;
	GLuint requiredBufferSize = initShapeData(numOfShapes,myShapes);
	
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, requiredBufferSize, NULL, GL_STATIC_DRAW);

	for (int i = 0; i < numOfShapes; i++)
	{
		myShapes[i].sendToBuffer(bufferID);
		//myShapes[i].cleanUp();
	}

	for (int i = 0; i < 10; i++)
	{
		int index = RANDOM::randomInt(0,numOfShapes-2);
		myGameObjs[numOfGameObjs].myShape = myShapes[index];

		float x = RANDOM::randomFloat(-range,range);
		float y = 2;//RANDOM::randomFloat(-range,range);
		float z = RANDOM::randomFloat(-range,range);
		float scale = 1;//RANDOM::randomFloat(.1f,10);

		myGameObjs[numOfGameObjs].translation = glm::vec3(x,y,z);
		myGameObjs[numOfGameObjs].scale = scale;
		myGameObjs[numOfGameObjs].accRange = 2;
		myGameObjs[numOfGameObjs].rateToChageAngleACC = 100;
		numOfGameObjs++;
	}

	camEntity.myShape = myShapes[RANDOM::randomInt(1,numOfShapes-1)];
	camEntity.scale = 1;
	camEntity.accRange = 2;

	floor.myShape = myShapes[numOfShapes-1];
	floor.scale = 10;
	floor.translation = vec3(0,-floor.scale,0);
}

void MyWindow::myUpdate() {
	//*
	static uint frames = 0;
	frames++;
	//*/

	if(frames%100==0) {
		//qDebug() << "Cam Pos { " << myCam.getPos().x   <<   ", " << myCam.getPos().y   <<   ", " << myCam.getPos().z   <<   " }";
		//qDebug() << "Cam View{ " << myCam.getViewDir().x << ", " << myCam.getViewDir().y << ", " << myCam.getViewDir().z << " }";
	}

	for (int i = 0; i < numOfGameObjs; i++)
	{
		myGameObjs[i].update(frames);
	}

	camEntity.update(frames);

	repaint();
}
void MyWindow::mouseMoveEvent(QMouseEvent* e) {
	glm::vec2 newPos(e->x(),e->y());
	myCam.updateMousePos(newPos);
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
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float aspectRatio = (float)width()/(float)height();

	mat4x4 viewTransform;
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();
	glUniformMatrix4fv(myShadyShader.getUniform("viewTransform"),1,false,&viewTransform[0][0]);

	glUniform1i(myShadyShader.getUniform("enableOverrideColor"),enableOverrideColor);
	glUniform3fv(myShadyShader.getUniform("overrideColor"),1,&overrideColor[0]);
	glUniform3fv(myShadyShader.getUniform("ambientLight"),1,&ambientLight[0]);
	glUniform3fv(myShadyShader.getUniform("diffuseLight"),1,&diffuseLight[0]);
	glUniform3fv(myShadyShader.getUniform("diffusePos"),1,&diffusePos[0]);
	glUniform1i(myShadyShader.getUniform("diffuseInFrag"),diffuseInFrag);

	bool passThrough = false;
	glUniform1i(myShadyShader.getUniform("passThrough"),passThrough);


	for (int i = 0; i < numOfGameObjs; i++)
	{
		draw(myGameObjs[i]);
	}

	draw(floor);

	passThrough = true;
	glUniform1i(myShadyShader.getUniform("passThrough"),passThrough);

	if(displayLightEntity) {
		camEntity.translation = diffusePos;
		draw(camEntity);
	}

}

void MyWindow::draw(GameObj& entity) {
	DrawnObj toDraw = entity.getShape();
	mat4x4 finalTransform;

	finalTransform *= entity.getTransform();

	glUniformMatrix4fv(myShadyShader.getUniform("model2WorldTransform"),1,false,&finalTransform[0][0]);

	toDraw.printPrep();
	glDrawElements(GL_TRIANGLES,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());
}

void MyWindow::draw(GameObj * blockData, glm::mat4x4 lastTransform, float scale, int depth, int children, glm::vec3 orbitLength, glm::vec3 orbitAxis) {
	if(depth>=0) {
		float averageAngle = 360.0f/children;
		for (int i = 0; i < children; i++)
		{
			DrawnObj& toDraw = myGameObjs[i].getShape();
			//glm::vec4 previousTranslation = lastTransform * glm::vec4(0,0,0,0);
			//glm::mat4x4 transform = glm::translate(glm::vec3(previousTranslation));
			glm::mat4x4 transform = glm::rotate(orbitAngle + i*averageAngle,orbitAxis)
									* glm::translate(scale * orbitLength)
									* glm::scale(glm::vec3(scale,scale,scale));

			//transform = glm::translate(glm::vec3(previousTranslation)) * transform;
			transform = lastTransform * transform;

			glm::mat4x4 finalTrans = transform * blockData->getTransform();
			glUniformMatrix4fv(myShadyShader.getUniform("transformation"),1,false,&finalTrans[0][0]);

			toDraw.printPrep();
			glDrawElements(GL_TRIANGLES,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());

			draw(blockData+1, transform,.6f * scale,depth-1,children, orbitLength, orbitAxis);
		}
	}
}