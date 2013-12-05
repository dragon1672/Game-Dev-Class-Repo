#include "Enemy.h"
#include "MoveLogic.h"
#include "GameSpace.h"
#include "MyGraphics.h"

Shape Enemy::defaultStyle = Shape(RGB(255,0,0),
	17,
	5*Vector2D(-1  ,-3.5),
	5*Vector2D( 1  ,-3.5),
	5*Vector2D( 3.5,-1  ),
	5*Vector2D( 3.5, 1  ),
	5*Vector2D( 1  , 3.5),
	5*Vector2D( 1  , 1  ),
	5*Vector2D(-1  , 1  ),
	5*Vector2D(-1  , 3.5),
	5*Vector2D(-3.5, 1  ),
	5*Vector2D(-3.5,-1  ),
	5*Vector2D(-1  ,-3.5),//return to begining
	5*Vector2D(-.75,-4  ),
	5*Vector2D(-.25,-4  ),
	5*Vector2D( 0  ,-3.5),
	5*Vector2D( .25,-4  ),
	5*Vector2D( .75,-4  ),
	5*Vector2D( 1  ,-3.5)
);

void     Enemy::addAcc(const Vector2D& toAdd) {
	vel = vel+(toAdd);
	if(vel.lengthSquared()>getMaxSpeed()*getMaxSpeed())
		vel = (getMaxSpeed()-1) * vel.normalized();
}
void     Enemy::updateMovement(float dt) {
	rotationMatrix = myMovementLogic->rotation(dt);
	addAcc(myMovementLogic->getAcc(dt));
	//world drag
	vel = myMovementLogic->brake(vel,GameSpace::WORLD_DRAG*dt);
	move(dt);
}
void     Enemy::move(float dt) {
	pos = pos+(dt*vel);
	collide(dt);
}
void     Enemy::warp() {
	if(pos.getX() < (*space).getMin().getX()) pos = Vector2D( (*space).getMax().getX()-1, pos.getY());
	if(pos.getY() < (*space).getMin().getY()) pos = Vector2D( pos.getX(),                 (*space).getMax().getY()-1);
	if(pos.getX() > (*space).getMax().getX()) pos = Vector2D( (*space).getMin().getX()+1, pos.getY());
	if(pos.getY() > (*space).getMax().getY()) pos = Vector2D( pos.getX(),                 (*space).getMin().getY()+1);
}
void     Enemy::collide(float dt) {
	//multiply vel by dt 
	HitInfo temp = space->collideVector(pos,vel*dt);
	if(temp.hasHit) {
		vel = temp.vel/dt;
		pos = temp.pos;
	}
	warp();//just in case
}
void     Enemy::update(float dt) {
	updateMovement(dt);
	childUpdate(dt);
}
void     Enemy::draw(MyGraphics& graphics) {
	getStyle()->draw(graphics,getTransMatrix());
	childDraw(graphics);
}
Matrix3D Enemy::getTransMatrix() {
	return Matrix3D::translate(pos) * rotationMatrix;
}
Matrix3D Enemy::getRotationMat() {
	return rotationMatrix;
}
Vector2D Enemy::getPos() {
	return pos;
}
int      Enemy::getTeam() {
	return TeamInfo::ENEMY_TEAM;
}
	
//REQUIRED FOR CHILDREN
float  Enemy::getMaxSpeed() {
	return 400;//spaceship is 1,000
}
float Enemy::getAcc() {
	return 200;//ship is 300
}
Shape *Enemy::getStyle() {
	return &defaultStyle;
}
//so children can implement say a turret
void Enemy::childUpdate(float dt) {
	dt;//default to do nothing
}
void Enemy::childDraw(MyGraphics& graphics) {
	graphics;//default to do nothing
}
float Enemy::getStartingHealth() {
	return 5;
}
//required for initilization
void Enemy::setSpace(GameSpace* toSet) {
	space = toSet;
}
void Enemy::setMovementLogic(MoveLogic* toSet) {
	myMovementLogic = toSet;
}
void Enemy::setPosition(const Vector2D& toSet) {
	pos = toSet;
	warp();
}