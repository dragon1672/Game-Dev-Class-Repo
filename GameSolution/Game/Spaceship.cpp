#include "SpaceShip.h"
#include "GameSpace.h"
#include "PlayerControls.h"

const float worldDrag = 100;
const float Spaceship::brakePower = 1000;
//const Vector2D accX(100, 0);
//const Vector2D accY(0, 100);

float Spaceship::TURRET_LENGTH = 30;
float Spaceship::ACC = 500;
float Spaceship::rotationAcc = 5;
float Spaceship::maxSpeed = 1000;
Core::RGB Spaceship::shipColor = RGB(255,255,0);
const float Spaceship::SHIP_FULL_STARTING_HEALTH = 10;
//*
const float scaler = 3;
Matrix3D cartesian2Screen = Matrix3D::scaleY(-scaler) * Matrix3D::scaleX(scaler);
Shape Spaceship::thisShape( shipColor, cartesian2Screen,
							7,
							Vector2D( 5,-6 ),
							Vector2D( 6,-0 ),
							Vector2D( 4,-4 ),
							Vector2D( 0, 10),//tip
							Vector2D(-4,-4 ),
							Vector2D(-6,-0 ),
							Vector2D(-5,-6 )
							);//*/

#include "BasicTurret.h"
#include "TurretMark2.h"

void  Spaceship::init(float x, float y, GameSpace *space) {
	pos = Vector2D(x,y);
	this->space = space;
	myFiringLogic.setKey(PlayerControls::shoot);
	//have to manually set the array
	turrets[0] = &myBasicTurret;
	turrets[1] = &myMark2Turret;
	turrets[2] = &myMark3Turret;
	turrets[3] = &myMark4Turret;
	turrets[4] = &myMark5Turret;

	for(int i=0;i<SIZE_OF_ARRAY(turrets);i++) {
		turrets[i]->init(space,this,&myTarget,&myFiringLogic,getTeam());
	}
	currentTurret = turrets[0];
	maxAccessibleTurret = 1;
	myEffect.init(this,.5);
	space->addEffect(15,&myEffect);
	turretTimer.start();
	initFullHealth(SHIP_FULL_STARTING_HEALTH);
}
	
//acc
void  Spaceship::addAcc(const Vector2D& toAdd, float scalar) {
	vel = vel+(scalar*toAdd);
	if(vel.lengthSquared()>maxSpeed*maxSpeed)
		vel = (maxSpeed-1) * vel.normalized();
}
void  Spaceship::brake(float scalar, float force) {
	float newX = 0;
	float brakePower = scalar*(force);
	float current = vel.getX();
	if(current!=0) {
		float toSub = (current>0)? brakePower : -brakePower ;
		newX = (abs(toSub)<abs(current))? current-toSub: 0;
	}
	float newY = 0;
	current = vel.getY();
	if(current!=0) {
		float toSub = (current>0)? brakePower : -brakePower ;
		newY = (abs(toSub)<abs(current))? current-toSub: 0;
	}
	vel = Vector2D(newX,newY);
}
void  Spaceship::manageAcc(float dt) {
#ifdef DEBUG_SPACESHIP
	if(Core::Input::IsPressed( Core::Input::KEY_UP        )) addAcc(-Vector2D(0,ACC),dt);
	if(Core::Input::IsPressed( Core::Input::KEY_DOWN      )) addAcc( Vector2D(0,ACC),dt);
	if(Core::Input::IsPressed( Core::Input::KEY_LEFT      )) addAcc(-Vector2D(ACC,0),dt);
	if(Core::Input::IsPressed( Core::Input::KEY_RIGHT     )) addAcc( Vector2D(ACC,0),dt);
#endif
	if(Core::Input::IsPressed( PlayerControls::brake      )) brake (dt);
	if(Core::Input::IsPressed( PlayerControls::accelerate )) addAcc( Matrix3D::rotationMatrix(angle) * -Vector2D(0,ACC),dt);
	if(Core::Input::IsPressed( PlayerControls::decelerate )) addAcc( Matrix3D::rotationMatrix(angle) *  Vector2D(0,ACC),dt);
	//world drag
	brake(dt,worldDrag);
}
//movement
void  Spaceship::move(float dt) {
	pos = pos+(dt*vel);
	if(Core::Input::IsPressed( PlayerControls::warpColision )) warp();
	else collide(dt);
}
//collision
void  Spaceship::warp() {
	if(pos.getX() < (*space).getMin().getX()) pos = Vector2D( (*space).getMax().getX(), pos.getY());
	if(pos.getY() < (*space).getMin().getY()) pos = Vector2D( pos.getX(),               (*space).getMax().getY() );
	if(pos.getX() > (*space).getMax().getX()) pos = Vector2D( (*space).getMin().getX(), pos.getY());
	if(pos.getY() > (*space).getMax().getY()) pos = Vector2D( pos.getX(),               (*space).getMin().getY() );
}
void  Spaceship::collide(float dt) {
	//multiply vel by dt 
	HitInfo temp = space->collideVector(pos,vel*dt);//need to pass dt to accuratly calc if collision will be in bounds again
	if(temp.hasHit) {
		vel = temp.vel/dt;
		pos = temp.pos;
	}
	warp();//just in case
}
void  Spaceship::manageRot(float dt) {
	if(Core::Input::IsPressed(PlayerControls::rotateLeft)) {
		angle -= rotationAcc*dt;
	}
	if(Core::Input::IsPressed(PlayerControls::rotateRight)) {
		angle += rotationAcc*dt;
	}
}
void  Spaceship::updateSelectedTurret() {
	if(turretTimer.getCurrentTime()>3) {
		turretTimer.start();//restart
		if(maxAccessibleTurret<SIZE_OF_ARRAY(turrets))
			maxAccessibleTurret++;
	}
	int numToCheck = this->maxAccessibleTurret;//SIZE_OF_ARRAY(turrets);
	for(int i=0;i<numToCheck;i++) {
		if(Core::Input::IsPressed( '1'+i ))
			currentTurret = turrets[i];
	}
}
void  Spaceship::update(float dt) {
	myEffect.paused = !Core::Input::IsPressed(PlayerControls::accelerate);
	manageAcc(dt);
	manageRot(dt);
	move(dt);
	updateSelectedTurret();
	currentTurret->update(dt);
}
//graphics
Shape* Spaceship::getStyle() {
	return &thisShape;
}
void  Spaceship::draw(Core::Graphics& graphics) {
	getStyle()->draw(graphics,getTransMatrix());
	currentTurret->draw(graphics);

#ifdef DEBUG_SPACESHIP

#endif
}
Matrix3D Spaceship::getTransMatrix() {
	return Matrix3D::translate(pos) * Matrix3D::rotationMatrix(angle);
}
Matrix3D Spaceship::getRotationMat() {
	return Matrix3D::rotationMatrix(angle);
}
Vector2D Spaceship::getPos() {
	return pos;
}
int Spaceship::getTeam() {
	return FRIENLY_TEAM;
}