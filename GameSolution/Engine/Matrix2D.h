#pragma once
#include "Vector 2.h"
#include <cmath>
class Matrix2D {
	float matrix[2][2];
public:
	Matrix2D() {
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++) {
				if(i==j) matrix[i][j] = 1;
				else     matrix[i][j] = 0;
			}
		}
	}
	Matrix2D(const Vector2D& row1, const Vector2D& row2) {
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
	Matrix2D rotationMatrix(float angle) {
		Vector2D rowOne(cos(angle),-sin(angle));
		Vector2D rowTwo(sin(angle),cos(angle));
		return Matrix2D(rowOne,rowTwo);
	}
	Matrix2D transpose(Matrix2D max) {
		Vector2D rowOne(max.get(0,0),max.get(1,0));
		Vector2D rowTwo(max.get(0,1),max.get(1,1));
		return Matrix2D(rowOne,rowTwo);
	}
	Matrix2D scaleX(float alpha) {
		Vector2D rowOne(alpha,0);
		Vector2D rowTwo(0,1);
		return Matrix2D(rowOne,rowTwo);
	}
	Matrix2D scaleY(float alpha) {
		Vector2D rowOne(1,0);
		Vector2D rowTwo(0,alpha);
		return Matrix2D(rowOne,rowTwo);
	}
	Matrix2D scale(float alpha) {
		Vector2D rowOne(alpha,0);
		Vector2D rowTwo(0,alpha);
		return Matrix2D(rowOne,rowTwo);
	}
	friend inline std::ostream& operator<<(std::ostream& stream, const Matrix2D& right);
	//friend inline Matrix2D operator+ (const Matrix2D& left, const Matrix2D& right);
	//friend inline Matrix2D operator- (const Matrix2D& left, const Matrix2D& right);
	friend inline Matrix2D operator* (const Matrix2D& left, const Matrix2D& right);
	friend inline Vector2D operator* (const Matrix2D& left, const Vector2D& right);
};

std::ostream& operator<<(std::ostream& stream, const Matrix2D& max) {
	std::cout << "{ {" << max.get(0,0) << ", " << max.get(0,1) << "}, {" << max.get(1,0) << ", " << max.get(1,1) << "} }";
	return stream;
}
/*
inline Matrix2D operator+ (const Matrix2D& left, const Matrix2D& right) {
	Vector2D rowOne(left.get(0,0)+right.get(0,0),left.get(0,1)+right.get(0,1));
	Vector2D rowTwo(left.get(1,0)+right.get(1,0),left.get(1,1)+right.get(1,1));
	return Matrix2D(rowOne,rowTwo);
}
inline Matrix2D operator- (const Matrix2D& left, const Matrix2D& right) {
	Vector2D rowOne(left.get(0,0)-right.get(0,0),left.get(0,1)-right.get(0,1));
	Vector2D rowTwo(left.get(1,0)-right.get(1,0),left.get(1,1)-right.get(1,1));
	return Matrix2D(rowOne,rowTwo);
}//*/
inline Matrix2D operator* (const Matrix2D& left, const Matrix2D& right) {
	Matrix2D result;
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			result.matrix[i][j] = left.getRow(i).dot(right.getCol(j));
		}
	}
	return result;
}
inline Vector2D operator* (const Matrix2D& left, const Vector2D& right) {
	float x = left.getRow(0).dot(right);
	float y = left.getRow(1).dot(right);
	return Vector2D(x,y);
}
