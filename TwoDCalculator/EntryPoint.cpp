#include "RenderUI.h"
#include "glm/glm.hpp"
#include "glm/gtx/projection.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef glm::vec2 Vector2D;
typedef glm::vec3 Vector3D;
typedef glm::mat2x2 Matrix2D;
typedef glm::mat3x3 Matrix3D;
typedef glm::mat4x4 Matrix4D;

//#define DEBUG

//tab_1 BASIC
namespace tab_one {
	Vector2D left;
	Vector2D right;
	Vector2D result;
	void myBasicVectorEquationCallback(const BasicVectorEquationInfo& info) {
		left   = info.scalar1 * Vector2D(info.x1,info.y1);
		right  = info.scalar2 * Vector2D(info.x2,info.y2);
		result = (info.add)? left + right : left - right;
	}
}
//tab 2 PERP
namespace tab_two {
	Vector2D orginal;
	Vector2D norm;
	Vector2D perpCw;
	Vector2D perpCWW;
	void myPerpendicularDataCallback(const PerpendicularData& info) {
		orginal = Vector2D(info.x,info.y);
		norm    = glm::normalize(orginal);
		perpCw  = glm::vec2(-orginal.y, orginal.x);
		perpCWW = glm::vec2( orginal.y,-orginal.x);
	}
}
//tab 3 DOT
namespace tab_three {
	Vector2D right;
	Vector2D left;
	Vector2D project;
	Vector2D reject;
	void myDotProductDataCallBack(const DotProductData& info) {
		right   = Vector2D(info.v1i,info.v1j);
		left    = Vector2D(info.v2i,info.v2j);
		project = (info.projectOntoLeftVector)?      glm::proj(left,right) :       glm::proj(right,left);
		reject  = (info.projectOntoLeftVector)? left-glm::proj(left,right) : right-glm::proj(right,left);
	}
}
//tab 4 LERP
namespace tab_four {
	Vector2D left;
	Vector2D right;
	Vector2D subtract;
	Vector2D lerpA;
	Vector2D lerpB;
	Vector2D result;
	void myLerpDataCallback(const LerpData& info) {
		left     = Vector2D(info.a_i,info.a_j);
		right    = Vector2D(info.b_i,info.b_j);
		subtract = right - left;
		lerpA    = (1-info.beta) * left;
		lerpB    = info.beta * right;
		result   = (1-info.beta) * left + info.beta * right;
	}
}
//tab 5 Matrix Vector Mult
namespace tab_five {
	Vector2D result;
	void LinearTransformationCallback(const LinearTransformationData& info) {
		Matrix2D input(info.m00,info.m10,
					   info.m01, info.m11);
		result = input * Vector2D(info.v0,info.v1);
	}
}
//tab 6
namespace tab_six {
	float resultVectors[15];
	void myAffineTransformationCallback(const AffineTransformationData& info) {
		Vector3D row1(*(info.data+0),*(info.data+3),*(info.data+6));
		Vector3D row2(*(info.data+1),*(info.data+4),*(info.data+7));
		Vector3D row3(*(info.data+2),*(info.data+5),*(info.data+8));
		Matrix3D max(row1,row2,row3);
		for(int i=0;i<5;i++) {
			Vector3D source(*(info.data+i*3+9),*(info.data+i*3+10),*(info.data+i*3+11));
			Vector3D result = max * source;
			resultVectors[i*3+0] = result.x;
			resultVectors[i*3+1] = result.y;
			resultVectors[i*3+2] = result.z;
		}
	}
}
//tab 7
namespace tab_seven {
	Vector2D star[] = {
						.5f * Vector2D(   .7f, -1.0f ),
						.5f * Vector2D(  0.0f,  1.0f ),
						.5f * Vector2D(  -.6f, -1.0f ),
						.5f * Vector2D(  1.0f,   .25f),
						.5f * Vector2D( -1.0f,   .25f)
					};
	Vector2D lines[] = {
		star[0], star[1],
		star[1], star[2],
		star[2], star[3],
		star[3], star[4],
		star[4], star[0]
	};
	int numLines = (sizeof(lines) / sizeof(*lines))/2;
	int maxMatrixId = 0;
	Matrix3D matrices[5];
	//float* matrices;
	Matrix3D currentTransform;
	void myMatrixTransformCallback2D(const MatrixTransformData2D& info) {
		int id = info.selectedMatrix;
		maxMatrixId = (id>maxMatrixId)? id : maxMatrixId;

		glm::mat4x4 temp;
		temp  = glm::mat4x4(1,0,0,0,
							0,1,0,0,
							info.translateX,info.translateY,1,0,
							0,0,0,1);
		float convertedAngle = -(info.rotate*180)/3.14f;
		temp *= glm::rotate(convertedAngle,Vector3D(0,0,1));
		temp *= glm::scale(Vector3D(info.scaleX,info.scaleY,1));

		matrices[id] = Matrix3D(temp[0][0],temp[1][0],temp[2][0],
								temp[0][1],temp[1][1],temp[2][1],
								temp[0][2],temp[1][2],temp[2][2]);

		currentTransform = Matrix3D();
		for(int i=0;i<maxMatrixId+1;i++) {
			currentTransform = currentTransform * matrices[i];
		}
	}
	//*/
}
//tab 8
namespace tab_eight {

#define RAD2DEG(x) -(x*180)/3.14f

	const char* fbxFileName = "DatBrittanyChair.fbx";

	int maxMatrixId = 0;
	Matrix4D matrices[10];
	Matrix4D currentTransform;
	void mySet3DMatrixCallback(const MatrixTransformData3D& info) {
		int id = info.selectedMatrix;
		maxMatrixId = (id>maxMatrixId)? id : maxMatrixId;

		glm::mat4x4 temp;
		temp  = glm::mat4x4(1,0,0,0,
							0,1,0,0,
							0,0,1,0,
							info.translateX,info.translateY,info.translateZ,1);
		
		//rotation
		temp *= glm::rotate(RAD2DEG(info.rotateX),Vector3D(1,0,0));
		temp *= glm::rotate(RAD2DEG(info.rotateY),Vector3D(0,1,0));
		temp *= glm::rotate(RAD2DEG(info.rotateZ),Vector3D(0,0,1));
		
		//scale
		temp *= glm::scale(Vector3D(info.scaleX,info.scaleY,info.scaleZ));

		matrices[id] = temp;

		currentTransform = Matrix4D();

		for(int i=0;i<maxMatrixId+1;i++) {
			currentTransform = currentTransform * matrices[i];
		}
	}
}


int main(int argc, char* argv[]) {
	RenderUI renderUI;
	renderUI.setBasicVectorEquationData(tab_one::myBasicVectorEquationCallback,
										(float *)&tab_one::left,
										(float *)&tab_one::right,
										(float *)&tab_one::result);
	renderUI.setPerpendicularData((float *)&tab_two::orginal,
								  (float *)&tab_two::norm,
								  (float *)&tab_two::perpCw,
								  (float *)&tab_two::perpCWW,
								  tab_two::myPerpendicularDataCallback);
	renderUI.setDotProductData((float *)&tab_three::right,
							   (float *)&tab_three::left,
							   (float *)&tab_three::project,
							   (float *)&tab_three::reject,
							   tab_three::myDotProductDataCallBack);
	renderUI.setLerpData((float *)&tab_four::left,
						 (float *)&tab_four::right,
						 (float *)&tab_four::subtract,
						 (float *)&tab_four::lerpA,
						 (float *)&tab_four::lerpB,
						 (float *)&tab_four::result, 
						 tab_four::myLerpDataCallback);
	//renderUI.setLineEquationData(
	renderUI.setLinearTransformationData((float *)&tab_five::result,
										 tab_five::LinearTransformationCallback);
	renderUI.setAffineTransformationData(tab_six::resultVectors,
										 tab_six::myAffineTransformationCallback);
	renderUI.set2DMatrixVerticesTransformData((float *)tab_seven::lines, 
											  tab_seven::numLines, 
											  (float *)tab_seven::matrices,
											  (float *)&tab_seven::currentTransform,
											  tab_seven::myMatrixTransformCallback2D);
	renderUI.set3DMatrixCallback((float *)&tab_eight::matrices,
								(float *)&tab_eight::currentTransform,
								 tab_eight::fbxFileName,
								 tab_eight::mySet3DMatrixCallback);
	/*
	renderUI.set2DMatrixVerticesTransformData(
			const float* lines, int numLines, 
			const float* matrices,
			const float* currentTransform,
			MatrixTransformCallback2D uiChangedCallback);
	//*/
	
	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}