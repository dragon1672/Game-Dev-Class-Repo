#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "LivingGameEntity.h"

class MoveLogic;
class GameSpace;

class Enemy : public LivingGameEntity {
private:
	static const float MAX_SPEED;
	static Shape defaultStyle;
	Vector2D pos;
	Vector2D vel;
	Matrix3D rotationMatrix;
	GameSpace *space;
	MoveLogic *myMovementLogic;
	//add Effects Later
	void  addAcc(const Vector2D& toAdd);
	void  updateMovement(float dt);
	void  move(float dt);
	void     warp();
	void     collide(float dt);
public:
	Enemy() {
		this->initFullHealth(getStartingHealth());
	}
	void  update(float dt);
	void  draw(Core::Graphics& graphics);
	Matrix3D getTransMatrix();
	Matrix3D getRotationMat();
	Vector2D getPos();
	int      getTeam();
	//REQUIRED FOR CHILDREN
	virtual  float getMaxSpeed();
	virtual  float getAcc();
	virtual  Shape* getStyle();
	//so children can implement say a turret
	virtual  void  childUpdate(float dt);
	virtual  void  childDraw(Core::Graphics& graphics);
	virtual  float getStartingHealth();
	//required for initilization
	void setPosition(const Vector2D& toSet);
protected:
	void setSpace(GameSpace* toSet);
	void setMovementLogic(MoveLogic* toSet);
};

#endif