#include "Noise.h"

#pragma region MAKING COOBS

Neumont::Vertex stackVerts2[] = 
{
	// Top
	glm::vec3(-1.0f, +1.0f, +1.0f), // 0
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, +1.0f, +1.0f), // 1
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	glm::vec3(+1.0f, +1.0f, -1.0f), // 2
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, +1.0f, -1.0f), // 3
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	
	// Front
	glm::vec3(-1.0f, +1.0f, -1.0f), // 4
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, +1.0f, -1.0f), // 5
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	glm::vec3(+1.0f, -1.0f, -1.0f), // 6
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, -1.0f, -1.0f), // 7
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, -1.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	
	// Right
	glm::vec3(+1.0f, +1.0f, -1.0f), // 8
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(+1.0f, +1.0f, +1.0f), // 9
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(+1.0f, -1.0f, +1.0f), // 10
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, -1.0f, -1.0f), // 11
	glm::vec4(0,0,-1,0),                                // tan
	glm::vec3(+1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	
	// Left
	glm::vec3(-1.0f, +1.0f, +1.0f), // 12
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, +1.0f, -1.0f), // 13
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(-1.0f, -1.0f, -1.0f), // 14
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(-1.0f, -1.0f, +1.0f), // 15
	glm::vec4(0,0,1,0), // tan
	glm::vec3(-1.0f, +0.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	
	// Back
	glm::vec3(+1.0f, +1.0f, +1.0f), // 16
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
	glm::vec3(-1.0f, +1.0f, +1.0f), // 17
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(-1.0f, -1.0f, +1.0f), // 18
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(+1.0f, -1.0f, +1.0f), // 19
	glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f), // Tan
	glm::vec3(+0.0f, +0.0f, +1.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	
	// Bottom
	glm::vec3(+1.0f, -1.0f, -1.0f), // 20
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +1.0f), // UV
	glm::vec3(-1.0f, -1.0f, -1.0f), // 21
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +1.0f), // UV
	glm::vec3(-1.0f, -1.0f, +1.0f), // 22
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+0.0f, +0.0f), // UV
	glm::vec3(+1.0f, -1.0f, +1.0f), // 23
	glm::vec4(1,0,0,0), // tan
	glm::vec3(+0.0f, -1.0f, +0.0f), // Normal
	glm::vec2(+1.0f, +0.0f), // UV
};
unsigned short stackIndices2[] = {
	0,  1,  2,  0,  2,  3, // Top
	4,  5,  6,  4,  6,  7, // Front
	8,  9,  10, 8,  10, 11, // Right 
	12, 13, 14, 12, 14, 15, // Left
	16, 17, 18, 16, 18, 19, // Back
	20, 22, 21, 20, 23, 22, // Bottom
};

Neumont::ShapeData makeCube2() {
	Neumont::ShapeData ret;
	ret.verts = stackVerts2;
	ret.numVerts = sizeof(stackVerts2) / sizeof(*stackVerts2);

	ret.indices = stackIndices2;
	ret.numIndices = sizeof(stackIndices2) / sizeof(*stackIndices2);
	return ret;
}

#pragma endregion

int Noise::genTexture() {
	noise::module::Perlin myModule;
	const uint BYTES_PER_COLOR = 4;
	const uint width  = 256;
	const uint height = 256;
	const int zVal = 20;
	GLubyte * meTexture = new GLubyte[BYTES_PER_COLOR * width * height];
	for (int row= 0; row < height; row++)
	{
		for (int col= 0; col < width; col++) {
			float x = (float)row / height;
			float y = (float)col / width;
			myModule.SetOctaveCount(1);	float valR = myModule.GetValue(x,y,zVal);
			myModule.SetOctaveCount(2);	float valG = myModule.GetValue(x,y,zVal);
			myModule.SetOctaveCount(3);	float valB = myModule.GetValue(x,y,zVal);
			myModule.SetOctaveCount(4);	float valA = myModule.GetValue(x,y,zVal);
			GLubyte * textureStart = &meTexture[row * width * BYTES_PER_COLOR + col*BYTES_PER_COLOR];
			
			textureStart[0] = (valR+1) / 2 * 0xFF;	// R
			textureStart[1] = (valG+1) / 2 * 0xFF;	// G
			textureStart[2] = (valB+1) / 2 * 0xFF;	// B
			textureStart[3] = (valA+1) / 2 * 0xFF;	// A
		}
	}
	return addTexture(meTexture,width,height);
}

void Noise::init() {
	//myCam.lookAt(glm::vec3(0,2,1),glm::vec3(0,0,0));
	myCam.setPos(glm::vec3(-.5,1,.5), glm::vec3(0,-1,-.3));
	myCam.MOVEMENT_SPEED *= .4;

	layer = 1;
	updateRate = 2;

	ShaderProgram * meShader = addShader("./../shaders/NoiseMapDemoV.glsl","./../shaders/NoiseMapDemoF.glsl");
	saveViewTransform(meShader,"viewTransform");
	meShader->saveUniform("layer",ParameterType::PT_FLOAT,&layer);
	meShader->saveUniform("baseColor", ParameterType::PT_VEC3,&color[0]);

	auto meGeo = addGeometry(Neumont::ShapeGenerator::makePlane(2),GL_TRIANGLES);

	int textureID = genTexture();

	auto meRenderable = addRenderable(meGeo,meShader,textureID);
	meRenderable->saveTexture("myTexture");
	meRenderable->saveMatrixInfo("model2WorldTransform");
	meRenderable->transformData.scale = glm::vec3(5,5,5);
	 
	menu->setDefaultTab("noise");
	menu->edit("OctaveCount: ",layer,1,4);
	menu->edit("UpdateRate: ",updateRate,0,3);
	menu->watch("Color: ",color);
	menu->edit("NoisePlane",meRenderable->visible);


	myCam.lookAt(glm::vec3(0,3,15),glm::vec3(0,0,0));

	specPower = 100;
	lightColor = glm::vec3(1,1,1);

	whiteAsTexture = false;

	meGeo =  addGeometry(NUShapeEditor::scale(makeCube2(),5),GL_TRIANGLES);
	auto cameraGeo = addGeometry(Neumont::ShapeGenerator::makeSphere(50),GL_TRIANGLES);

	lightSrcRenderable = addRenderable(cameraGeo,mainShader,-1);
	lightSrcRenderable->saveMatrixInfo("model2WorldTransform");

	meShader = addShader("./../shaders/tanNormal_V.glsl","./../shaders/tanNormal_F.glsl");
	saveViewTransform(meShader,"viewTransform");
	meShader->saveUniform("diffusePos",   ParameterType::PT_VEC3, &lightSrcRenderable->transformData.position[0]         );
	meShader->saveUniform("lightColor", ParameterType::PT_VEC3, &lightColor[0]         );
	meShader->saveUniform("camPos",     ParameterType::PT_VEC3, &myCam.getPos()[0]     );
	meShader->saveUniform("specPower",  ParameterType::PT_FLOAT, &specPower            );
	meShader->saveUniform("whiteAsTexture", ParameterType::PT_BOOLEAN, &whiteAsTexture );
		
	meCube = addRenderable(meGeo,meShader,addTexture("./../textures/basicNormal.png",false,true));
	meCube->saveTexture("normalMap");
	meCube->saveMatrixInfo("model2WorldTransform");
	meCube->addUniformParameter("modelRotation", cubeRotation );
	
	menu->setDefaultTab("Cube Tans");
	menu->edit("lightPosition",lightSrcRenderable->transformData.position,-20,20);
	//menu->edit("lightColor",lightColor,0,1);
	//menu->edit("specPower",specPower,3,100);
	menu->edit("Cube Rot:",meCube->transformData.rotation,-360,360);
	menu->edit("showLightSrc",lightSrcRenderable->visible);
	menu->edit("whiteAsTexture",whiteAsTexture);
	meCube->visible = false;
	menu->edit("Show Cube",meCube->visible);

	lightSrcRenderable->transformData.position = glm::vec3(0,10,0); // debug menu is corrupting data ?!?
	lightSrcRenderable->transformData.scale = glm::vec3(.2,.2,.2);
}
	
void Noise::nextFrame(float dt) {
	static float timePassed = -1;
	timePassed += dt;
	if(timePassed > updateRate || timePassed < 0) {
		timePassed -= updateRate;
		color = Random::glmRand::randomFloatVectorInBox(1,1,1);
	}
	cubeRotation = meCube->transformData.genRotMat();
}