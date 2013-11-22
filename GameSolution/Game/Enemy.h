#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "LivingGameEntity.h"
#include "MoveLogic.h"
#include "GameSpace.h"

class Enemy : public LivingGameEntity {
private:
	static const float MAX_SPEED;
	Vector2D pos;
	Vector2D vel;
	float angle;
	GameSpace *space;
	MoveLogic *myMovementLogic;
	//add Effects Later
	void  addAcc(const Vector2D& toAdd, float scalar) {
		vel = vel+(scalar*toAdd);
		if(vel.lengthSquared()>getMaxSpeed()*getMaxSpeed())
			vel = (getMaxSpeed()-1) * vel.normalized();
	}
	void  updateMovement(float dt) {
		angle+=myMovementLogic->angleAcc(dt);
		addAcc(myMovementLogic->getAcc(dt));
		//world drag
		vel = myMovementLogic->brake(vel,GameSpace::WORLD_DRAG*dt);
	}
	void  move(float dt) {
		pos = pos+(dt*vel);
		collide(dt);
	}
	void     warp() {
		if(pos.getX() < (*space).getMin().getX()) pos = Vector2D( (*space).getMax().getX(), pos.getY());
		if(pos.getY() < (*space).getMin().getY()) pos = Vector2D( pos.getX(),               (*space).getMax().getY() );
		if(pos.getX() > (*space).getMax().getX()) pos = Vector2D( (*space).getMin().getX(), pos.getY());
		if(pos.getY() > (*space).getMax().getY()) pos = Vector2D( pos.getX(),               (*space).getMin().getY() );
	}
	void     collide(float dt) {
		//multiply vel by dt 
		HitInfo temp = space->collideVector(pos,vel*dt);
		if(temp.hasHit) {
			vel = temp.vel/dt;
			pos = temp.pos;
		}
		warp();//just in case
	}
public:
	void  update(float dt) {
		updateMovement(dt);
		childUpdate(dt);
	}
	void  draw(Core::Graphics& graphics) {
		getStyle()->draw(graphics,getTransMatrix());
		childDraw(graphics);
	}
	Matrix3D getTransMatrix() {
		return Matrix3D::translate(pos) * Matrix3D::rotationMatrix(angle);
	}
	Matrix3D getRotationMat() {
		return Matrix3D::rotationMatrix(angle);
	}
	Vector2D getPos() {
		return pos;
	}
	int      getTeam() {
		return ENEMY_TEAM;
	}
	
	//REQUIRED FOR CHILDREN
	virtual  float getMaxSpeed();
	virtual  Shape* getStyle();
	virtual  void childUpdate(float dt);
	virtual  void childDraw(Core::Graphics&);
protected: //required for initilization
	void setSpace(GameSpace* toSet) {
		space = toSet;
	}
	void setMovementLogic(MoveLogic* toSet) {
		myMovementLogic = toSet;
	}
};

#endif