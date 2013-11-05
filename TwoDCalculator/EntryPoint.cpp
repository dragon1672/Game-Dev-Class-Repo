#include "RenderUI.h"
#include "Engine.h"
#include "Matrix2D.h"
#include <Vector 2.h>

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
		norm    = orginal.normalized();
		perpCw  = orginal.perpCW();
		perpCWW = orginal.perpCCW();
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
		project = (info.projectOntoLeftVector)? left.projection(right) : right.projection(left);
		reject  = (info.projectOntoLeftVector)? left.rejection (right) : right.rejection (left);
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
		lerpA    = (1-info.beta) * left;//don't like hard code here
		lerpB    = info.beta* right;//don't like hard code here
		result   = Vector2D::LERP(info.beta,left, right);
	}
}
//tab 5 Matrix Vector Mult
namespace tab_five {
	Vector2D result;
	void LinearTransformationCallback(const LinearTransformationData& info) {
		Matrix2D input(Vector2D(info.m00,info.m01),Vector2D(info.m10, info.m11));
		result = input * Vector2D(info.v0,info.v1);
	}
}
//tab 6
namespace tab_six {
	Vector2D result;
	void myAffineTransformationCallback(const AffineTransformationData& info) {
		info.data;
	}
}
//tab 7
namespace tab_seven {

}
#ifdef DEBUG
#include <iostream>
#include "SquareMatrix.h"
using namespace std;

void testing() {
	SquareMatrix max(4);
	max.set( 1,0,0);	max.set( 3,0,1);	max.set( 5,0,2);	max.set( 2,0,3);
	max.set( 0,1,0);	max.set(-1,1,1);	max.set( 3,1,2);	max.set( 4,1,3);
	max.set( 2,2,0);	max.set( 1,2,1);	max.set( 9,2,2);	max.set( 6,2,3);
	max.set( 3,3,0);	max.set( 2,3,1);	max.set( 4,3,2);	max.set( 8,3,3);
	cout << max.calcDetermant(max) << endl;
}
#endif //DEBUG

int main(int argc, char* argv[]) {
#ifdef DEBUG
	testing();
	return 0;
#else
	Engine::Init();
	RenderUI renderUI;
	renderUI.setBasicVectorEquationData(tab_one::myBasicVectorEquationCallback,
										tab_one::left,
										tab_one::right,
										tab_one::result);
	renderUI.setPerpendicularData(tab_two::orginal,
								  tab_two::norm,
								  tab_two::perpCw,
								  tab_two::perpCWW,
								  tab_two::myPerpendicularDataCallback);
	renderUI.setDotProductData(tab_three::right,
							   tab_three::left,
							   tab_three::project,
							   tab_three::reject,
							   tab_three::myDotProductDataCallBack);
	renderUI.setLerpData(tab_four::left,
						 tab_four::right,
						 tab_four::subtract,
						 tab_four::lerpA,
						 tab_four::lerpB,
						 tab_four::result, 
						 tab_four::myLerpDataCallback);
	//renderUI.setLineEquationData(
	renderUI.setLinearTransformationData(tab_five::result,
									 tab_five::LinearTransformationCallback);
	renderUI.setAffineTransformationData(tab_six::result,
										 tab_six::myAffineTransformationCallback);
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
#endif // !DEBUG
}