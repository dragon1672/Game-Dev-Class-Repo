#include "SpaceShip.h"
#include "GameSpace.h"
const float worldDrag = 100;
const float Spaceship::brakePower = 1000;
//const Vector2D accX(100, 0);
//const Vector2D accY(0, 100);

float Spaceship::TURRET_LENGTH = 30;
float Spaceship::ACC = 500;
float Spaceship::rotationAcc = 5;
float Spaceship::maxSpeed = 2000;
Core::RGB Spaceship::shipColor = RGB(255,255,0);
//*
Shape Spaceship::thisShape( shipColor,
							7,
							Vector2D(10,12),
							Vector2D(12, 0 ),
							Vector2D( 8,  8 ),
							Vector2D( 0, -20),//tip
							Vector2D(-8,  8 ),
							Vector2D(-12, 0 ),
							Vector2D(-10, 12)
							);//*/
/*
const Matrix3D SpaceShipTransform = Matrix3D::scaleX(10) * Matrix3D::scaleY(-10);
Shape Spaceship::thisShape( shipColor,
							SpaceShipTransform,
							17,
							Vector2D(-1  ,-3.5),
							Vector2D( 1  ,-3.5),
							Vector2D( 3.5,-1  ),
							Vector2D( 3.5, 1  ),
							Vector2D( 1  , 3.5),
							Vector2D( 1  , 1  ),
							Vector2D(-1  , 1  ),
							Vector2D(-1  , 3.5),
							Vector2D(-3.5, 1  ),
							Vector2D(-3.5,-1  ),
							Vector2D(-1  ,-3.5),//return to begining
							Vector2D(-.75,-4  ),
							Vector2D(-.25,-4  ),
							Vector2D( 0  ,-3.5),
							Vector2D( .25,-4  ),
							Vector2D( .75,-4  ),
							Vector2D( 1  ,-3.5)
);//*/
#ifdef DEBUG_SPACESHIP

#include <sstream>
std::string vec2str(Vector2D input) {
	std::stringstream ss;
	ss << input;
	return ss.str();
}

#endif


void  Spaceship::init(float x, float y, GameSpace *space/*, GameWorld world*/) {
	pos = Vector2D(x,y);
	this->space = space;
	myTurret.init();
	bodyGuards.startup(5);
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
	if(Core::Input::IsPressed( Core::Input::KEY_UP        )) addAcc(-Vector2D(0,ACC),dt);
	if(Core::Input::IsPressed( Core::Input::KEY_DOWN      )) addAcc( Vector2D(0,ACC),dt);
	if(Core::Input::IsPressed( Core::Input::KEY_LEFT      )) addAcc(-Vector2D(ACC,0),dt);
	if(Core::Input::IsPressed( Core::Input::KEY_RIGHT     )) addAcc( Vector2D(ACC,0),dt);
	if(Core::Input::IsPressed( Core::Input::BUTTON_SHIFT  )) brake (dt);
	if(Core::Input::IsPressed( 'W' )) addAcc( Matrix3D::rotationMatrix(angle) * -Vector2D(0,ACC),dt);
	if(Core::Input::IsPressed( 'S' )) addAcc( Matrix3D::rotationMatrix(angle) *  Vector2D(0,ACC),dt);
	//world drag
	brake(dt,worldDrag);
}
//movement
void  Spaceship::move(float dt) {
	pos = pos+(dt*vel);
	if(Core::Input::IsPressed(      'Z' )) warp();
	else if(Core::Input::IsPressed( 'X' )) bounce();
	else {
		collide();
	}
}
//collision
void  Spaceship::warp() {
	if(pos.getX() < (*space).getMin().getX()) pos = Vector2D( (*space).getMax().getX(), pos.getY());
	if(pos.getY() < (*space).getMin().getY()) pos = Vector2D( pos.getX(),               (*space).getMax().getY() );
	if(pos.getX() > (*space).getMax().getX()) pos = Vector2D( (*space).getMin().getX(), pos.getY());
	if(pos.getY() > (*space).getMax().getY()) pos = Vector2D( pos.getX(),               (*space).getMin().getY() );
}
void  Spaceship::bounce() {
	if(pos.getX() < (*space).getMin().getX() || pos.getX() > (*space).getMax().getX()) vel = Vector2D(-vel.getX(), vel.getY());
	if(pos.getY() < (*space).getMin().getY() || pos.getY() > (*space).getMax().getY()) vel = Vector2D( vel.getX(),-vel.getY());
}
void  Spaceship::collide() {
	vel = space->collideVector(pos,vel);//need to pass dt to accuratly calc if collision will be in bounds again
	//warp();//just in case
}
/*
float Spaceship::mouseDistanceFromTurretLine() {
	float mouseX = (float)Core::Input::GetMouseX();
	float mouseY = (float)Core::Input::GetMouseY();
	Vector2D mouse(mouseX,mouseY);
	Vector2D temp = mouse-pos;
	Vector2D anotherTemp = turret.perpCW().normalized();
	float tempFloat = temp.dot(anotherTemp);
	return tempFloat;
}
bool  Spaceship::mouseWithinTurretRange() {
	float mouseX = (float)Core::Input::GetMouseX();
	float mouseY = (float)Core::Input::GetMouseY();
	Vector2D mouse(mouseX,mouseY);
	Vector2D testOne = pos-mouse;
	Vector2D testTwo = (pos+ turret) - mouse;
	return (testOne.dot(testTwo) < 0);
	//return ((mouse-pos).lengthSquared()<turret.lengthSquared());//is within turrent length from shipPos
}
void  Spaceship::updateTurret(float dt) {
	if(Core::Input::IsPressed( Core::Input::BUTTON_LEFT) && mouseWithinTurretRange()) {
		int error=5;
		float mouseDist = mouseDistanceFromTurretLine();
		if(-error<mouseDist && mouseDist<error) {
			float mouseX = (float)Core::Input::GetMouseX();
			float mouseY = (float)Core::Input::GetMouseY();
			Vector2D mouse(mouseX,mouseY);
			turret = TURRET_LENGTH*((mouse-pos).normalized());
			if(turret.isZero()) resetTurret();
		}
	}
}
//*/
void  Spaceship::manageRot(float dt) {
	if(Core::Input::IsPressed('A')) {
		angle -= rotationAcc*dt;
	}
	if(Core::Input::IsPressed('D')) {
		angle += rotationAcc*dt;
	}
}
void  Spaceship::update(float dt) {
	manageAcc(dt);
	manageRot(dt);
	move(dt);
	//updateTurret(dt);
	bodyGuards.update(dt);
	myTurret.update(dt, pos);
}
//graphics
float Spaceship::getMinX() { return pos.getX()+thisShape.getMinX(); }
float Spaceship::getMinY() { return pos.getY()+thisShape.getMinY(); }
float Spaceship::getMaxX() { return pos.getX()+thisShape.getMaxX(); }
float Spaceship::getMaxY() { return pos.getY()+thisShape.getMaxY(); }
void  Spaceship::draw(Core::Graphics& graphics) {
	this->thisShape.draw(graphics,getShipMatrix());
	myTurret.draw(graphics,pos);
	bodyGuards.draw(graphics,getShipMatrix());
#ifdef DEBUG_SPACESHIP

#endif
}
Matrix3D Spaceship::getShipMatrix() {
	return Matrix3D::translate(pos) * Matrix3D::rotationMatrix(angle);
}