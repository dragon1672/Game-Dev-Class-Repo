#pragma once
#ifndef MATRIX3D_H
#define MATRIX3D_H

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
	float get(int i, int j) const;
	inline Vector3D getRow(int i) const;
	inline Vector3D getCol(int j) const;
	inline static Matrix3D rotationMatrix(float angle);
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
	inline static Matrix3D scaleX(float alpha);
	inline static Matrix3D scaleY(float alpha);
	inline static Matrix3D scale(float alpha);
	inline static Matrix3D translate(float x, float y);
	inline static Matrix3D translate(const Vector2D& toTrans);
	friend inline std::ostream& operator<<(std::ostream& stream, const Matrix3D& right);
	friend inline Matrix3D operator+ (const Matrix3D& left, const Matrix3D& right);
	friend inline Matrix3D operator- (const Matrix3D& left, const Matrix3D& right);
	friend inline Matrix3D operator* (const Matrix3D& left, const Matrix3D& right);
	friend inline Vector3D operator* (const Matrix3D& left, const Vector3D& right);
	friend inline Vector2D operator* (const Matrix3D& left, const Vector2D& right);
	friend inline Vector3D operator*=(const Matrix3D& left, const Vector2D& right);
	inline operator float*();
};

#include "Matrix3D.inl"

#endif