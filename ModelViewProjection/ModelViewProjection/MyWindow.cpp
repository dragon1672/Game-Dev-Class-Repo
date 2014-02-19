#include <GL\glew.h>
#include "MyWindow.h"
#include "MyRandom.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

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
	myRender.init();

	glEnable(GL_DEPTH_TEST);

	myRender.mainShader->buildBasicProgram("VertexShader.glsl","FragShader.glsl");

	sendDataToHardWare();
	
	//myRender.mainShader->buildBasicProgram("VertexShader.glsl","FragShader.glsl");

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
	specColor = vec3(1,0,1);
	specPower = 50;

	objectsMoving = true;
	enableTexture = true;
	enableLighting = true;
}

//returns the required size

bool isAllVal(glm::vec3 vec, float val=0) {
	return vec.x == val
			&& vec.y == val
			&& vec.z == val;
}

Neumont::ShapeData fixTeaPotNormals(Neumont::ShapeData& obj) {
	obj.verts[obj.numVerts-1].normal = glm::vec3(0,1,0);
	/*
	for (uint i = 0; i < obj.numVerts; i++) {
		float len = glm::length(obj.verts[i].normal);
		if(isAllVal(obj.verts[i].normal,0)) {
			obj.verts[i].normal = obj.verts[i-1].normal;
		}
	}
	//*/
	return obj;
}
Neumont::ShapeData setModColor(Neumont::ShapeData& obj, int mod=1) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % mod == 0) {
			int r = RANDOM::randomFloat(0,1);
			int g = RANDOM::randomFloat(0,1);
			int b = RANDOM::randomFloat(0,1);
			int a = RANDOM::randomFloat(0,1);
			obj.verts[i].color = glm::vec4(r,g,b,1);
		}
	}
	return obj;
}
Neumont::ShapeData setColor(glm::vec4& toSet, Neumont::ShapeData& obj, int mod = 1) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % mod == 0) {
			obj.verts[i].color = toSet;
		}
	}
	return obj;
}
Neumont::ShapeData initUVData(Neumont::ShapeData& obj) {
	int size = sqrt(obj.numVerts);
	float divisor = size-1;
	for(unsigned int i = 0; i<obj.numVerts; i++)
	{
		int row = (i/size);
		int column = (i%size);
		obj.verts[i].uv = glm::vec2(row/divisor, column/divisor);
	}
	return obj;
}

int sendTextures(Renderer& myRender) {
	int numOfTextures;
	numOfTextures = myRender.addTexture("\\Textures\\075.jpg.png");
	numOfTextures = myRender.addTexture("\\Textures\\1231342137298gl5.jpg.png");
	numOfTextures = myRender.addTexture("\\Textures\\1234540124849gd7.jpg.png");
	numOfTextures = myRender.addTexture("\\Textures\\18_abstract.jpg.png");
	numOfTextures = myRender.addTexture("\\Textures\\6283823024_2d4d28c580_o.png");
	numOfTextures = myRender.addTexture("\\Textures\\782_hd_matrix_wallpaper_by_andre_w.jpg.png");
	numOfTextures = myRender.addTexture("\\Textures\\blue-screen-of-death1.jpg.png");
	numOfTextures = myRender.addTexture("\\Textures\\Funny-Humor-21.png");
	numOfTextures = myRender.addTexture("\\Textures\\inObamaWeTrust_bill_crop_5.png");
	numOfTextures = myRender.addTexture("\\Textures\\jamie Avatar.png");
	//numOfTextures = myRender.addTexture("\\Textures\\Metal_Hole_08.png");
	numOfTextures = myRender.addTexture("\\Textures\\Smile.png");
	//numOfTextures = myRender.addTexture("\\Textures\\windows_coding.jpg.png");
	return numOfTextures;
}

void MyWindow::sendDataToHardWare() {
	//setting up textures
	int numOfTextures = sendTextures(myRender);

	numOfGameObjs = 0;

	uint floorGeoID;

	GeometryInfo * randomModels[6];
	uint randomModelCount = 0;
	Neumont::ShapeData models[6];
	uint modelCount = 0;
	int teaPotQuality = RANDOM::randomInt(5,30);
	int randomQuality = 50;//RANDOM::randomInt(5,15);
	models[modelCount++] = fixTeaPotNormals(setModColor(Neumont::ShapeGenerator::makeTeapot(teaPotQuality,glm::mat4()),4));
	models[modelCount++] = initUVData(Neumont::ShapeGenerator::makeTorus(randomQuality));
	models[modelCount++] = initUVData(Neumont::ShapeGenerator::makeArrow());
	models[modelCount++] = initUVData(Neumont::ShapeGenerator::makeSphere(randomQuality));
	models[modelCount++] = Neumont::ShapeGenerator::makeCube();
	
	floorGeoID = modelCount;//setting floor to plane;
	models[modelCount++] = setColor(glm::vec4(1,1,1,1),Neumont::ShapeGenerator::makePlane(10));

	for(uint i=0;i<modelCount;i++) {
		GeometryInfo * justAdded = myRender.addGeometry(models[i].verts,models[i].numVerts,models[i].indices,models[i].numIndices,GL_TRIANGLES);
		justAdded->streamedPosition(0);
		justAdded->streamedColor(1);
		justAdded->streamedNormal(2);
		justAdded->streamedUv(3);
		if(i==floorGeoID) {
			floor.whatGeo = justAdded;
		} else {
			randomModels[randomModelCount++] = justAdded;
		}
	}


	for (int i = 0; i < 20; i++) {
		int index = RANDOM::randomInt(0,randomModelCount-1);
		Renderable * justAdded = myRender.addRenderable(randomModels[index],myRender.mainShader,RANDOM::randomInt(0,numOfTextures-1));
		
		
		float x = RANDOM::randomFloat(-range,range);
		float y = RANDOM::randomFloat(range/2,  range);
		float z = RANDOM::randomFloat(-range,range);
		justAdded->addTranslate(glm::vec3(x,y,z));

		justAdded->saveRotationMat("model2RotationTransform");
		justAdded->saveWhereMat("model2WorldTransform");
		justAdded->saveTexture("myTexture");

		gameObjs[numOfGameObjs++] = justAdded;
	}
	int index = RANDOM::randomInt(0,randomModelCount-1);
	lightSource.init(randomModels[index],myRender.mainShader,true,RANDOM::randomInt(0,numOfTextures-1));
	lightSource.setScale(.75);
	lightSource.randomRange = 2;
	lightSource.saveRotationMat("model2RotationTransform");
	lightSource.saveWhereMat("model2WorldTransform");
	
	floor.init(floor.whatGeo,myRender.mainShader,true,RANDOM::randomInt(0,numOfTextures-1));
	floor.setScale(10);
	floor.addTranslate(vec3(0,-5,0));
	floor.saveRotationMat("model2RotationTransform");
	floor.saveWhereMat("model2WorldTransform");
	floor.saveTexture("myTexture");
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

	if(objectsMoving) {
		for (uint i = 0; i < myRender.getNumOfRenderables(); i++) {
			if(frames%1000==0) myRender.getRenderable(i)->randomACC();
				myRender.getRenderable(i)->rotate();
		}
	}
	if(frames%1000==0) lightSource.randomACC();
		lightSource.rotate();
	repaint();
	if(frames>10000)
		paintGL();
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

void MyWindow::passDataDownToShader(ShaderProgram& prog, bool passthrough) {
	const float aspectRatio = (float)width()/(float)height();

	mat4x4 viewTransform;
	viewTransform *= glm::perspective(60.0f,aspectRatio,.1f,200.0f);
	viewTransform *= myCam.getWorld2View();

	prog.passUniform("viewTransform",ParameterType::PT_MAT4,&viewTransform[0][0]);
	
	prog.passUniform("enableOverrideColor",ParameterType::PT_BOOLEAN,  enableOverrideColor);
	prog.passUniform("overrideColor",      ParameterType::PT_VEC3, &overrideColor[0]   );
	prog.passUniform("ambientLight",       ParameterType::PT_VEC3, &ambientLight[0]    );
	prog.passUniform("diffuseLight",       ParameterType::PT_VEC3, &diffuseLight[0]    );
	prog.passUniform("diffusePos",         ParameterType::PT_VEC3, &diffusePos[0]      );
	prog.passUniform("diffuseInFrag",      ParameterType::PT_BOOLEAN,  diffuseInFrag      );
	
	prog.passUniform("specPower", ParameterType::PT_FLOAT,&specPower);
	prog.passUniform("specColor", ParameterType::PT_VEC3, &specColor[0]);
	prog.passUniform("camPos",    ParameterType::PT_VEC3, &myCam.getPos()[0]);
	
	prog.passUniform("enableTexture",  ParameterType::PT_BOOLEAN, enableTexture);
	prog.passUniform("enableLighting", ParameterType::PT_BOOLEAN, enableLighting);
	prog.passUniform("passThrough", ParameterType::PT_BOOLEAN, passthrough);

}

void MyWindow::paintGL() {
	glViewport(0,0,width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bool passThrough = false;

	myRender.mainShader->useProgram();
	passDataDownToShader(*myRender.mainShader,passThrough);
	
	for (uint i = 0; i < numOfGameObjs; i++)
	{
		draw(*gameObjs[i],passThrough);
	}

	draw(floor,passThrough);

	passThrough = true;

	myRender.mainShader->passUniform("passThrough", ParameterType::PT_BOOLEAN, passThrough);

	if(displayLightEntity) {
		lightSource.setTranslate(diffusePos);
		draw(lightSource,passThrough);
	}

}

void MyWindow::draw(Renderable& entity, bool passthrough) {
	if(entity.visible) {
		if(!entity.howShader->isCurrentProgram()) {
			passDataDownToShader(*entity.howShader,passthrough);
		}
		entity.passUniformsDownDown();
		myRender.draw(*entity.whatGeo);
	}
}