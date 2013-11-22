#pragma once
#ifndef GAMESPACE_H
#define GAMESPACE_H

//core
#include "Shape.h"
#include "Boundary.h"
#include "HitInfo.h"
#include "GameEntity.h"
#include "LivingGameEntity.h"
//objects
#include "SpaceShip.h"
#include "Lerper.h"
#include "ExplosionEffect.h"
//managers
#include "BulletManager.h"
#include "ParticalManager.h"


const Core::RGB defaultColor = RGB(255,0,50);
//creates a square world where all game obects will interact in
class GameSpace {
public:
	static const int NO_INDEX = -1;//has to be under 0
private:

	Spaceship myShip;
	Boundary *boundary;
	Lerper myLerp;
	BulletManager myBullets;

	ParticalManager allMyParticals;

	std::vector<LivingGameEntity *> myEntities;

	Vector2D min;
	Vector2D max;
	Shape gameStyle;
	void initObjects();
	bool hasBounds;

	void drawHealthBar(Core::Graphics& graphics, LivingGameEntity *target);
public:
	GameSpace();
	GameSpace(float width, float height, const Vector2D& pos=Vector2D(0,0), Core::RGB color=defaultColor);
	void init(float width, float height, const Vector2D& pos=Vector2D(0,0), Core::RGB color=defaultColor);
	void      draw(Core::Graphics& graphics);
	void      update(float dt);
	//getters
	Boundary *getBoundary();
	Vector2D  getMin();
	Vector2D  getMax();
	HitInfo   collideVector(const Vector2D& pos, const Vector2D& vel);
	Vector2D  randomWorldPoint();
	Vector2D  getCenter();
	//Entities
	LivingGameEntity* getLivingEntity(int id);
	//returns where team does not match
	int getLivingEntityClosest(      const Vector2D& pos,  int team=NO_TEAM, int startingIndex=0);
	int getLivingEntityCollidedWith( const Vector2D& pos,  int team=NO_TEAM, int startingIndex=0);
	int getLivingEntityCollidedWith( const Shape& toCheck, const Vector2D& pos, int team=NO_TEAM, int startingIndex=0);
	//returns where team matches
	int getLivingEntityClosestOfTeam(      const Vector2D& pos,  int team, int startingIndex=0);
	int getLivingEntityCollidedWithOfTeam( const Vector2D& pos,  int team, int startingIndex=0);
	int getLivingEntityCollidedWithOfTeam( const Shape& toCheck, const Vector2D& pos, int team, int startingIndex=0);
	//adding
	void      registerBoundary(Boundary *bounds);
	void      addEffect(int size, ParticalEffect* toAdd);
	void      addBullet(Bullet *toAdd);
	void      addLivingEntity(LivingGameEntity *toAdd);
	void      addExplosion(const Vector2D& pos, int size=5, float lifetime=1.5);

};

#endif