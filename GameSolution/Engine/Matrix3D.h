#include <cmath>
#include "Vector 2.h"
class Matrix3D {
	float matrix[3][3];
public:
	Matrix3D() {
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++) {
				if(i==j) matrix[i][j] = 1;
				else     matrix[i][j] = 0;
			}
		}
	}
	Matrix3D(const Vector2D& row1, const Vector2D& row2) {
		matrix[0][0] = row1.getX();
		matrix[0][1] = row1.getY();
		matrix[1][0] = row2.getX();
		matrix[1][1] = row2.getY();
	}
	float get(int i, int j) const {
		return matrix[i][j];
	}
	Vector2D getRow(int i) const {
		return Vector2D(matrix[i][0],matrix[i][1]);
	}
	Vector2D getCol(int j) const {
		return Vector2D(matrix[0][j],matrix[1][j]);
	}
	Matrix3D rotationMatrix(float angle) {
		Vector2D rowOne(cos(angle),-sin(angle));
		Vector2D rowTwo(sin(angle),cos(angle));
		return Matrix3D(rowOne,rowTwo);
	}
	Matrix3D transpose(Matrix3D max) {
		Vector2D rowOne(max.get(0,0),max.get(1,0));
		Vector2D rowTwo(max.get(0,1),max.get(1,1));
		return Matrix3D(rowOne,rowTwo);
	}
	Matrix3D scaleX(float alpha) {
		Vector2D rowOne(alpha,0);
		Vector2D rowTwo(0,1);
		return Matrix3D(rowOne,rowTwo);
	}
	Matrix3D scaleY(float alpha) {
		Vector2D rowOne(1,0);
		Vector2D rowTwo(0,alpha);
		return Matrix3D(rowOne,rowTwo);
	}
	Matrix3D scale(float alpha) {
		Vector2D rowOne(alpha,0);
		Vector2D rowTwo(0,alpha);
		return Matrix3D(rowOne,rowTwo);
	}
	friend inline std::ostream& operator<<(std::ostream& stream, const Matrix3D& right);
	//friend inline Matrix3D operator+ (const Matrix3D& left, const Matrix3D& right);
	//friend inline Matrix3D operator- (const Matrix3D& left, const Matrix3D& right);
	friend inline Matrix3D operator* (const Matrix3D& left, const Matrix3D& right);
	friend inline Vector2D operator* (const Matrix3D& left, const Vector2D& right);
};

std::ostream& operator<<(std::ostream& stream, const Matrix3D& max) {
	std::cout << "{ {" << max.get(0,0) << ", " << max.get(0,1) << "}, {" << max.get(1,0) << ", " << max.get(1,1) << "} }";
	return stream;
}
/*
inline Matrix3D operator+ (const Matrix3D& left, const Matrix3D& right) {
	Vector2D rowOne(left.get(0,0)+right.get(0,0),left.get(0,1)+right.get(0,1));
	Vector2D rowTwo(left.get(1,0)+right.get(1,0),left.get(1,1)+right.get(1,1));
	return Matrix3D(rowOne,rowTwo);
}
inline Matrix3D operator- (const Matrix3D& left, const Matrix3D& right) {
	Vector2D rowOne(left.get(0,0)-right.get(0,0),left.get(0,1)-right.get(0,1));
	Vector2D rowTwo(left.get(1,0)-right.get(1,0),left.get(1,1)-right.get(1,1));
	return Matrix3D(rowOne,rowTwo);
}//*/
inline Matrix3D operator* (const Matrix3D& left, const Matrix3D& right) {
	float a00 = left.getRow(0).dot(right.getCol(0));
	float a01 = left.getRow(0).dot(right.getCol(1));
	float a10 = left.getRow(1).dot(right.getCol(0));
	float a11 = left.getRow(1).dot(right.getCol(1));
	Vector2D rowOne(a00,a01);
	Vector2D rowTwo(a10,a11);
	return Matrix3D(rowOne,rowTwo);
}
inline Vector2D operator* (const Matrix3D& left, const Vector2D& right) {
	float x = left.get(0,0)*right.getX() + left.get(0,1)*right.getY();
	float y = left.get(1,0)*right.getX() + left.get(1,1)*right.getY();
	return Vector2D(x,y);
}
