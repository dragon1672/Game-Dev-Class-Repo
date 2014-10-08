#pragma once

#include <ShapeGenerator.h>
#include <Engine\Systems\Scene.h>
#include <noise\noise.h>
#include <Engine\Tools\NUShapeEditor.h>

class SceneTwo : public Scene {
public:
	SceneTwo() : Scene("SceneTwo") {}

	struct {
		Renderable * renderable;
		int noiseTexture;
		float percent;
		float discardThreshold;
		glm::vec3 rotAcc;
	} bears[4];

	struct {
		Renderable * Teapot;
		int noiseTexture;
		glm::vec2 uvOffset;
		float magnitude;
	} teapot;

	PassInfo * meEpicTexture;

	int testing;
	glm::vec4 testVec;

	virtual void windowResized(int newWidth,int newHeight) {
		meEpicTexture->updateTextureSize(newWidth,newHeight);
	}

	void addToFakeOutput(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		myCam.lookAt(glm::vec3(0,1,-7),glm::vec3(0,0,0));
		teapot.magnitude = .6f;
		menu->edit("magnitude",teapot.magnitude,0,2);

		ShaderProgram * deformWithTexture = renderer->addShader("./../shaders/NoiseMapDeformv.glsl","./../shaders/NoiseMapDeformF.glsl");
		renderer->saveViewTransform(deformWithTexture,"viewTransform");
		
		auto  teaPotGeo = renderer->addGeometry((NUShapeEditor::rotate(Neumont::ShapeGenerator::makeTeapot(30,glm::mat4()),-90,0,0)),GL_TRIANGLES);
		teapot.noiseTexture = renderer->addTexture("./../textures/seamlessNoise.png");
		
		teapot.Teapot = renderer->addRenderable(teaPotGeo,deformWithTexture,teapot.noiseTexture);
		teapot.Teapot->saveMatrixInfo("model2WorldTransform");
		teapot.Teapot->saveTexture("myTexture");
		teapot.Teapot->addUniformParameter("noiseMap",ParameterType::PT_TEXTURE,&teapot.noiseTexture);
		teapot.Teapot->addUniformParameter("uvOffset",ParameterType::PT_VEC2,&teapot.uvOffset[0]);
		teapot.Teapot->addUniformParameter("magnitude",teapot.magnitude);
		teapot.Teapot->transformData.scale = glm::vec3(.75,.75,.75);
		teapot.Teapot->transformData.position.y = -.5;

		int bearTexture = renderer->addTexture("./../textures/ToonTeddyBear.png");
		auto bearGeo = renderer->addGeometry(BinaryToShapeLoader::loadFromFile("./../models/TeddyBear.bin"),GL_TRIANGLES);// doo it
		auto bearShader = renderer->addShader("./../shaders/NoiseMapDissolveV.glsl","./../shaders/NoiseMapDissolveF.glsl");
		renderer->saveViewTransform(bearShader,"viewTransform");

		for (int i = 0; i < sizeof(bears) / sizeof(*bears); i++)
		{
			bears[i].noiseTexture = genTexture(renderer,Random::randomInt(0,20));
			bears[i].percent = (float)i/(sizeof(bears) / sizeof(*bears));
			bears[i].discardThreshold = .01f;
			bears[i].renderable = renderer->addRenderable(bearGeo,bearShader,bearTexture);

			bears[i].renderable->transformData.scale = glm::vec3(4,4,4);
			bears[i].renderable->transformData.rotation.y = 90;

			bears[i].renderable->saveMatrixInfo("model2WorldTransform");
			bears[i].renderable->saveTexture("myTexture");
			bears[i].renderable->addUniformParameter("noiseMap",ParameterType::PT_TEXTURE,&bears[i].noiseTexture);
			bears[i].renderable->addUniformParameter("discardThreshold",ParameterType::PT_FLOAT,&bears[i].discardThreshold);
			bears[i].rotAcc = Random::randomFloat(180,360) * Random::glmRand::randomUnitVector();
		}


		menu->watch("rot",bears[0].renderable->transformData.getRotMat());

		//menu->watch("Matrix",teapot.Teapot->transformData.genRotMat());
	}

	virtual void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) {
		myCam.lookAt(glm::vec3(10,10,10),glm::vec3());
		meEpicTexture = renderer->addPassInfo(false);
		renderer->setDefaultPassInfo(meEpicTexture);
		meEpicTexture->initTextures(renderer->width(),renderer->height());
		meEpicTexture->cam.enabled = true;
		addToFakeOutput(renderer,meEpicTexture->cam,menu);

		meEpicTexture->clearColor = glm::vec3();

		//renderer->resetDefaultPassInfoToScreen();
		renderer->setDefaultPassInfo(myDefaultPass);

		auto tempRenderable = renderer->addRenderable(renderer->addGeometry(Neumont::ShapeGenerator::makeCube()),renderer->defaultShaders.passThroughTexture, meEpicTexture->colorTexture);
		tempRenderable->saveTexture("myTexture");
		tempRenderable->saveMatrixInfo("model2WorldTransform");
		tempRenderable->transformData.rotation.x = 90;
		tempRenderable->transformData.scale = glm::vec3(5,5,5);
		tempRenderable->transformData.position.y = 2;
		tempRenderable->transformData.position.x = 2;




		testing = 0;

		menu->watch("int test",testing);
		menu->watch("Vec4 test", testVec);
		menu->edit("Vec4 test", testVec,-1,1);
		menu->edit("Testing Int",testing,1,10);


		
	}
	virtual void update(float dt) {
		for (int i = 0; i < sizeof(bears) / sizeof(*bears); i++) bears[i].renderable->transformData.rotation += dt * bears[i].rotAcc;
		float speed = .1f;
		float range = 2;
		static float spotInRange = range/2;
		spotInRange += speed * dt;
		if(spotInRange > range) spotInRange = 0;

		teapot.uvOffset.x = abs(spotInRange - range/2);
		teapot.uvOffset.y = abs(spotInRange - range/2);

		for (int i = 0; i < sizeof(bears) / sizeof(*bears); i++)
		{
			bears[i].percent += .1 * dt;
			if(bears[i].percent > 1) bears[i].percent -= 1;
			float percent = bears[i].percent;
			if(percent < .5) bears[i].discardThreshold = 1 - percent*2;
			else bears[i].discardThreshold = (percent-.5) * 2;

			glm::vec3 left(-1.5,1,-6);
			glm::vec3 right(0,0,-1);
			bears[i].renderable->transformData.position = (1-percent) * right + (percent * left);
		}
	}

	int genTexture(Renderer * renderer, int zVal = 20, bool seemless = true) {
		noise::module::Perlin myModule;
		const uint BYTES_PER_COLOR = 4;
		const uint width  = 256;
		const uint height = 256;
		GLubyte * meTexture = new GLubyte[BYTES_PER_COLOR * width * height];
		for (int row= 0; row < height; row++)
		{
			for (int col= 0; col < width; col++) {
				float x = (float)row / height;
				float y = (float)col / width;
				myModule.SetOctaveCount(4);	float valR = myModule.GetValue(x,y,zVal);
				myModule.SetOctaveCount(3);	float valG = myModule.GetValue(x,y,zVal);
				myModule.SetOctaveCount(2);	float valB = myModule.GetValue(x,y,zVal);
				myModule.SetOctaveCount(1);	float valA = myModule.GetValue(x,y,zVal);
				GLubyte * textureStart = &meTexture[row * width * BYTES_PER_COLOR + col*BYTES_PER_COLOR];
			
				textureStart[0] = (valR+1) / 2 * 0xFF;	// R
				textureStart[1] = (valG+1) / 2 * 0xFF;	// G
				textureStart[2] = (valB+1) / 2 * 0xFF;	// B
				textureStart[3] = (valA+1) / 2 * 0xFF;	// A
			}
		}
		return renderer->addTexture(meTexture,width,height);
	}
};