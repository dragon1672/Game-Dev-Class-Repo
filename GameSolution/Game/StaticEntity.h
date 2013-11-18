#pragma once
#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "GameEntity.h"

Shape StaticEntity_defaultStyle(RGB(100,100,100),Matrix3D::scaleY(-1) * Matrix3D::scale(30),
	41,
	Vector2D(1     , 0.800000000f),
	Vector2D(0.9f  , 1.107658554f),
	Vector2D(0.8f  , 1.195541753f),
	Vector2D(0.7f  , 1.240642296f),
	Vector2D(0.6f  , 1.259677335f),
	Vector2D(0.5f  , 1.258505748f),
	Vector2D(0.4f  , 1.239176537f),
	Vector2D(0.3f  , 1.201329407f),
	Vector2D(0.2f  , 1.141607594f),
	Vector2D(0.1f  , 1.048972162f),
	Vector2D(0     , 0.800000000f),
	Vector2D(-0.1f , 1.048972162f),
	Vector2D(-0.2f , 1.141607594f),
	Vector2D(-0.3f , 1.201329407f),
	Vector2D(-0.4f , 1.239176537f),
	Vector2D(-0.5f , 1.258505748f),
	Vector2D(-0.6f , 1.259677335f),
	Vector2D(-0.7f , 1.240642296f),
	Vector2D(-0.8f , 1.195541753f),
	Vector2D(-0.9f , 1.107658554f),
	Vector2D(-1    , 0.800000012f),
	Vector2D(-0.9f , 0.410234723f),
	Vector2D(-0.8f , 0.235541753f),
	Vector2D(-0.7f , 0.098013747f),
	Vector2D(-0.6f ,-0.020322665f),
	Vector2D(-0.5f ,-0.127134898f),
	Vector2D(-0.4f ,-0.227247686f),
	Vector2D(-0.3f ,-0.324973315f),
	Vector2D(-0.2f ,-0.426065841f),
	Vector2D(-0.1f ,-0.543007737f),
	Vector2D(0     ,-0.800000000f),
	Vector2D(0.1f  ,-0.543007737f),
	Vector2D(0.2f  ,-0.426065841f),
	Vector2D(0.3f  ,-0.324973315f),
	Vector2D(0.4f  ,-0.227247686f),
	Vector2D(0.5f  ,-0.127134898f),
	Vector2D(0.6f  ,-0.020322665f),
	Vector2D(0.7f  , 0.098013747f),
	Vector2D(0.8f  , 0.235541753f),
	Vector2D(0.9f  , 0.410234723f),
	Vector2D(1     , 0.800000000f)
);

class StaticEntity : GameEntity {
	Matrix3D translation;
public:
	StaticEntity() { ; }
	StaticEntity(const Vector2D& pos) {
		init(pos);
	}
	inline void init(const Vector2D& pos) {
		translation = Matrix3D::translate(pos);
	}
	inline Shape* getStyle() {
		return &StaticEntity_defaultStyle;
	}
	inline Matrix3D getTransMatrix() {
		return translation;
	}
	inline void update(float dt) {
		dt;
	}
};

#endif