#pragma once

#include "Renderer.h"
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <ShapeData.h>
#include <ShapeGenerator.h>
#include "NUShapeEditor.h"
#include <vector>
#include <limits>

typedef unsigned short ushort;

class DebugShapeManager {
private:
	struct DebugShapeData {
		GeometryInfo * whatGeo;
		ShaderProgram * howShader;
		glm::mat4 transform;
		glm::vec4 overrideColor;
		float lifetime;
		bool ignoreDepthTest;
		std::vector<ShaderUniformPram> prams;
		void init(ShaderProgram * theOne) {
			ShaderUniformPram toAdd;
			toAdd.init(theOne,"model2WorldTransform",ParameterType::PT_MAT4,&transform[0][0]);		prams.push_back(toAdd);
			toAdd.init(theOne,"overrideColor",ParameterType::PT_VEC4,&overrideColor[0]);			prams.push_back(toAdd);
			toAdd.init(theOne,"ignoreDepthTest",ParameterType::PT_BOOLEAN,(int*)&ignoreDepthTest);	prams.push_back(toAdd);
		}
	};
	std::vector<DebugShapeData *> shapes;
	struct DebugLineData {
		GeometryInfo * whatGeo;
		ShaderProgram * howShader;
		glm::vec3 start;
		glm::vec3 end;
		glm::vec4 overrideColor; //  doesn't matter for point
		float lifetime;
		bool ignoreDepthTest;
		bool enableOverrideColor; // false for point
		std::vector<ShaderUniformPram> prams;
		void init(ShaderProgram * theOne) {
			ShaderUniformPram toAdd;
			toAdd.init(theOne,"start",ParameterType::PT_VEC3,&start[0]);									prams.push_back(toAdd);
			toAdd.init(theOne,"end",ParameterType::PT_VEC3,&start[0]);										prams.push_back(toAdd);
			toAdd.init(theOne,"overrideColor",ParameterType::PT_VEC4,&overrideColor[0]);					prams.push_back(toAdd);
			toAdd.init(theOne,"enableOverrideColor",ParameterType::PT_BOOLEAN,(int*)&enableOverrideColor);	prams.push_back(toAdd);
			toAdd.init(theOne,"ignoreDepthTest",ParameterType::PT_BOOLEAN,(int*)&ignoreDepthTest);			prams.push_back(toAdd);
		}
	};
	std::vector<DebugLineData *> lineShapes;

	Renderer      * myRenderer;
	GeometryInfo  * sphere;
	ShaderProgram * sphereShader;
	GeometryInfo  * cube;
	ShaderProgram * cubeShader;
	GeometryInfo  * line;
	ShaderProgram * lineShader;
	GeometryInfo  * point;
	ShaderProgram * pointShader;

public:
	void init(Renderer * theRenderer) {
		myRenderer = theRenderer;
		Neumont::ShapeData NUSphere = NUShapeEditor::setColor(glm::vec4(1,1,1,1),Neumont::ShapeGenerator::makeSphere(5));
		Neumont::ShapeData NUCube   = NUShapeEditor::setColor(glm::vec4(1,1,1,1),Neumont::ShapeGenerator::makeCube());
		Neumont::ShapeData NULine;
		NULine.numVerts = 2;
		NULine.numIndices = 2;
		NULine.verts = new Neumont::Vertex[NULine.numVerts];
		NULine.indices = new ushort[NULine.numIndices];
		NULine.indices[0] = 0;
		NULine.verts  [0].color    = glm::vec4(2,2,2,2); // lighter tip
		NULine.verts  [0].position = glm::vec3(0,0,0);
		NULine.verts  [1].position = glm::vec3(1,0,0);
		NULine.verts  [1].color    = glm::vec4(1,1,1,1);
		NULine.indices[1] = 1;

		Neumont::ShapeData NUPoint;
		NUPoint.numVerts = 6;
		NUPoint.numIndices = 6;
		NUPoint.verts = new Neumont::Vertex[NUPoint.numVerts];
		NUPoint.indices = new ushort[NUPoint.numIndices];
		//R
		NUPoint.indices[0] = 0;
		NUPoint.verts  [0].color    = glm::vec4(+1,0,0,0); // r
		NUPoint.verts  [0].position = glm::vec3(+1,0,0);
		NUPoint.verts  [1].position = glm::vec3(-1,0,0);
		NUPoint.verts  [1].color    = glm::vec4(+0,0,0,0);
		NUPoint.indices[1] = 1;
		//G
		NUPoint.indices[2] = 2;
		NUPoint.verts  [2].color    = glm::vec4(0,+1,0,0); // g
		NUPoint.verts  [2].position = glm::vec3(0,+1,0);
		NUPoint.verts  [3].position = glm::vec3(0,-1,0);
		NUPoint.verts  [3].color    = glm::vec4(0,+0,0,0);
		NUPoint.indices[3] = 3;
		//B
		NUPoint.indices[4] = 4;
		NUPoint.verts  [4].color    = glm::vec4(0,0,+1,0); // b
		NUPoint.verts  [4].position = glm::vec3(0,0,+1);
		NUPoint.verts  [5].position = glm::vec3(0,0,-1);
		NUPoint.verts  [5].color    = glm::vec4(0,0,+0,0);
		NUPoint.indices[5] = 5;
		
		//send data down
		sphere = theRenderer->addGeometry(NUSphere,GL_TRIANGLES);
		sphere->NU_VertexStreamedPosition(0);
		sphere->NU_VertexStreamedColor(1);
		cube   = theRenderer->addGeometry(NUCube,  GL_TRIANGLES);
		cube->NU_VertexStreamedPosition(0);
		cube->NU_VertexStreamedColor(1);
		line   = theRenderer->addGeometry(NULine,  GL_LINES);
		line->NU_VertexStreamedPosition(0);
		line->NU_VertexStreamedColor(1);
		point  = theRenderer->addGeometry(NUPoint, GL_LINES);
		point->NU_VertexStreamedPosition(0);
		point->NU_VertexStreamedColor(1);

		//reg shaders
		lineShader = theRenderer->addShader("DebugLineVertexShader.glsl","PassThroughFragShader.glsl");
		sphereShader = theRenderer->addShader("PassThroughVertexShader.glsl","PassThroughFragShader.glsl");
		cubeShader =  sphereShader;
		pointShader = sphereShader;
	}

	void addUnitSphere(glm::mat4 transform, glm::vec4 color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {
		DebugShapeData * toAdd = new DebugShapeData();
		toAdd->whatGeo = sphere;
		toAdd->howShader = sphereShader;
		toAdd->transform = transform;
		toAdd->overrideColor = color;
		toAdd->lifetime = lifetime;
		toAdd->ignoreDepthTest = !depthTest;
		toAdd->init(sphereShader);
		shapes.push_back(toAdd);
	}
	void addUnitCube(glm::mat4 transform, glm::vec4 color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {
		DebugShapeData * toAdd = new DebugShapeData();
		toAdd->whatGeo = cube;
		toAdd->howShader = cubeShader;
		toAdd->transform = transform;
		toAdd->overrideColor = color;
		toAdd->lifetime = lifetime;
		toAdd->ignoreDepthTest = !depthTest;
		toAdd->init(cubeShader);
		shapes.push_back(toAdd);
	}
	void addUnitVector(glm::vec3 tail, glm::vec3 vector, glm::vec4 color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {
		DebugLineData * toAdd = new DebugLineData();
		toAdd->whatGeo = line;
		toAdd->howShader = lineShader;
		toAdd->start = tail;
		toAdd->end = tail + vector;
		toAdd->overrideColor = color;
		toAdd->lifetime = lifetime;
		toAdd->ignoreDepthTest = !depthTest;
		toAdd->enableOverrideColor = false;
		toAdd->init(lineShader);
		lineShapes.push_back(toAdd);
	}
	void addLine(glm::vec3 start, glm::vec3 end, glm::vec4 color, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {
		DebugLineData * toAdd = new DebugLineData();
		toAdd->whatGeo = line;
		toAdd->howShader = lineShader;
		toAdd->start = start;
		toAdd->end = end;
		toAdd->overrideColor = color;
		toAdd->lifetime = lifetime;
		toAdd->ignoreDepthTest = !depthTest;
		toAdd->enableOverrideColor = true;
		toAdd->init(lineShader);
		lineShapes.push_back(toAdd);
	}
	void addPoint(glm::vec3 pos, float lifetime=std::numeric_limits<float>::infinity(), bool depthTest=true) {
		DebugShapeData * toAdd = new DebugShapeData();
		toAdd->whatGeo = point;
		toAdd->howShader = pointShader;
		toAdd->transform = glm::translate(pos);
		toAdd->overrideColor = glm::vec4(1,1,1,1);
		toAdd->lifetime = lifetime;
		toAdd->ignoreDepthTest = !depthTest;
		toAdd->init(pointShader);
		shapes.push_back(toAdd);
	}
	
	
	void update(float dt) {
		for (unsigned int i = 0; i < lineShapes.size(); i++)
		{
			lineShapes[i]->lifetime -= dt;
			if(lineShapes[i]->lifetime<0) {
				delete lineShapes[i];
				lineShapes.erase(lineShapes.begin()+i--);
			}
		}
		for (unsigned int i = 0; i < shapes.size(); i++)
		{
			shapes[i]->lifetime -= dt;
			if(shapes[i]->lifetime<0) {
				delete shapes[i];
				shapes.erase(shapes.begin()+i--);
			}
		}
	}

	void draw(glm::mat4& viewMatrix) {
		 sphereShader-> passUniform("viewTransform",ParameterType::PT_MAT4,&viewMatrix[0][0]);
		 cubeShader  -> passUniform("viewTransform",ParameterType::PT_MAT4,&viewMatrix[0][0]);
		 lineShader  -> passUniform("viewTransform",ParameterType::PT_MAT4,&viewMatrix[0][0]);
		 pointShader -> passUniform("viewTransform",ParameterType::PT_MAT4,&viewMatrix[0][0]);
		 for (unsigned int i = 0; i < lineShapes.size(); i++) {
			 lineShapes[i]->howShader->useProgram();
			 for (unsigned int j = 0; j < lineShapes[i]->prams.size(); j++)
			 {
				 lineShapes[i]->prams[j].sendData();
			 }
			 myRenderer->draw(*(lineShapes[i]->whatGeo));
		 }
		 for (unsigned int i = 0; i < shapes.size(); i++) {
			 shapes[i]->howShader->useProgram();
			 for (unsigned int j = 0; j < shapes[i]->prams.size(); j++)
			 {
				 shapes[i]->prams[j].sendData();
			 }
			 myRenderer->draw(*(shapes[i]->whatGeo));
		 }
	}
};