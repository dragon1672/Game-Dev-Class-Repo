#include <cmath>
#include "Vector3D.h"
#include "Vector 2.h"
#define MATRIX3D_LENGTH 3

class Matrix3D {
	float matrix[MATRIX3D_LENGTH][MATRIX3D_LENGTH];
public:
	Matrix3D() {
		for(int i=0;i<MATRIX3D_LENGTH;i++){
			for(int j=0;j<MATRIX3D_LENGTH;j++) {
				if(i==j) matrix[i][j] = 1;
				else     matrix[i][j] = 0;
			}
		}
	}
	Matrix3D(const Vector3D& row1, const Vector3D& row2, const Vector3D& row3) {
		matrix[0][0] = row1.getX();
		matrix[0][1] = row1.getY();
		matrix[0][2] = row1.getZ();

		matrix[1][0] = row2.getX();
		matrix[1][1] = row2.getY();
		matrix[1][2] = row2.getZ();

		matrix[2][0] = row3.getX();
		matrix[2][1] = row3.getY();
		matrix[2][2] = row3.getZ();
	}
	float get(int i, int j) const {
		return matrix[i][j];
	}
	inline Vector3D getRow(int i) const {
		return Vector3D(matrix[i][0],matrix[i][1],matrix[i][2]);
	}
	inline Vector3D getCol(int j) const {
		return Vector3D(matrix[0][j],matrix[1][j],matrix[2][j]);
	}
	inline static Matrix3D rotationMatrix(float angle) {
		Vector3D rowOne(cos(angle),-sin(angle),0);
		Vector3D rowTwo(sin(angle),cos(angle),0);
		Vector3D rowThree(0,0,1);
		return Matrix3D(rowOne,rowTwo,rowThree);
	}
	/*
	Matrix3D transpose(Matrix3D max) {
		Matrix3D result;
		for(int i=0;i<MATRIX3D_LENGTH;i++) {
			for(int j=0;j<MATRIX3D_LENGTH;j++) {
				result.matrix[i][j] = max.get(j,i);
			}
		}
		return result;
	}
	//*/
	inline static Matrix3D scaleX(float alpha) {
		Vector3D rowOne(alpha,0,0);
		Vector3D rowTwo(0,1,0);
		Vector3D rowThree(0,0,1);
		return Matrix3D(rowOne,rowTwo,rowThree);
	}
	inline static Matrix3D scaleY(float alpha) {
		Vector3D rowOne(1,0,0);
		Vector3D rowTwo(0,alpha,0);
		Vector3D rowThree(0,0,1);
		return Matrix3D(rowOne,rowTwo,rowThree);
	}
	inline static Matrix3D scale(float alpha) {
		Vector3D rowOne(alpha,0,0);
		Vector3D rowTwo(0,alpha,0);
		Vector3D rowThree(0,0,alpha);
		return Matrix3D(rowOne,rowTwo,rowThree);
	}
	inline static Matrix3D translate(float x, float y) {
		Vector3D rowOne(1,0,x);
		Vector3D rowTwo(0,1,y);
		Vector3D rowThree(0,0,1);
		return Matrix3D(rowOne,rowTwo,rowThree);
	}
	inline static Matrix3D translate(const Vector2D& toTrans) {
		return translate(toTrans.getX(),toTrans.getY());
	}
	friend inline std::ostream& operator<<(std::ostream& stream, const Matrix3D& right);
	//friend inline Matrix3D operator+ (const Matrix3D& left, const Matrix3D& right);
	//friend inline Matrix3D operator- (const Matrix3D& left, const Matrix3D& right);
	friend inline Matrix3D operator* (const Matrix3D& left, const Matrix3D& right);
	friend inline Vector3D operator* (const Matrix3D& left, const Vector3D& right);
	friend inline Vector3D operator* (const Matrix3D& left, const Vector2D& right);
};

std::ostream& operator<<(std::ostream& stream, const Matrix3D& max) {
	std::cout << "{ {" << max.get(0,0) << ", " << max.get(0,1) << "}, {" << max.get(1,0) << ", " << max.get(1,1) << "} }";
	return stream;
}
/*
inline Matrix3D operator+ (const Matrix3D& left, const Matrix3D& right) {
	Vector3D rowOne(left.get(0,0)+right.get(0,0),left.get(0,1)+right.get(0,1));
	Vector3D rowTwo(left.get(1,0)+right.get(1,0),left.get(1,1)+right.get(1,1));
	return Matrix3D(rowOne,rowTwo);
}
inline Matrix3D operator- (const Matrix3D& left, const Matrix3D& right) {
	Vector3D rowOne(left.get(0,0)-right.get(0,0),left.get(0,1)-right.get(0,1));
	Vector3D rowTwo(left.get(1,0)-right.get(1,0),left.get(1,1)-right.get(1,1));
	return Matrix3D(rowOne,rowTwo);
}//*/
inline Matrix3D operator* (const Matrix3D& left, const Matrix3D& right) {
	Matrix3D result;
	for(int i=0;i<MATRIX3D_LENGTH;i++) {
		for(int j=0;j<MATRIX3D_LENGTH;j++) {
			result.matrix[i][j] = left.getRow(i).dot(right.getCol(j));
		}
	}
	return result;
}
inline Vector3D operator* (const Matrix3D& left, const Vector3D& right) {
	float x = left.getRow(0).dot(right);
	float y = left.getRow(1).dot(right);
	float z = left.getRow(2).dot(right);
	return Vector3D(x,y,z);
}
inline Vector3D operator* (const Matrix3D& left, const Vector2D& right) {
	return left * Vector3D(right.getX(),right.getY(),1);
}