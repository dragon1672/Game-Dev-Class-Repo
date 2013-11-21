#include "BasicTurret.h"
#include "Bullet.h"
#include <cmath>
#include "MyRandom.h"
const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape BasicTurretStyle( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		11,
		Vector2D(-3,-2),	Vector2D( 3,-2),	Vector2D( 3, 2),	Vector2D( 1, 2),
		Vector2D( 1, 4),	Vector2D( 3, 4),	Vector2D( 0,13),	Vector2D(-3, 4),
		Vector2D(-1, 4),	Vector2D(-1, 2),	Vector2D(-3, 2)
);

//for bullet
Shape Heart(RGB(255,0,255), Matrix3D::scale(4) * Cartesian2Screen,
	22,
	Vector2D(1     , 0.800000000f),
	Vector2D(0.9f  , 1.107658554f),
	Vector2D(0.8f  , 1.195541753f),
	Vector2D(0.5f  , 1.258505748f),
	Vector2D(0.4f  , 1.239176537f),
	Vector2D(0.2f  , 1.141607594f),
	Vector2D(0     , 0.800000000f),//tip
	Vector2D(-0.2f , 1.141607594f),
	Vector2D(-0.4f , 1.239176537f),
	Vector2D(-0.5f , 1.258505748f),
	Vector2D(-0.8f , 1.195541753f),
	Vector2D(-0.9f , 1.107658554f),
	Vector2D(-1    , 0.800000012f),//left (V bottom V)
	Vector2D(-0.9f , 0.410234723f),
	Vector2D(-0.6f ,-0.020322665f),
	Vector2D(-0.5f ,-0.127134898f),
	Vector2D(-0.2f ,-0.426065841f),
	Vector2D(0     ,-0.800000000f),//butt tip
	Vector2D(0.2f  ,-0.426065841f),
	Vector2D(0.5f  ,-0.127134898f),
	Vector2D(0.6f  ,-0.020322665f),
	Vector2D(0.9f  , 0.410234723f)
);

Shape *BasicTurret::getStyle() {
	return &BasicTurretStyle;
}

void BasicTurret::fireBullet() {
	Bullet createdBullet;
	createdBullet.pos   = myPos->getPos() + tipOfTurret();
	createdBullet.setVel((defaultBulletSpeed*direction) + Random::randomIntVector(-1,1));
	createdBullet.style = &Heart;
	shoot(&createdBullet);
}
float BasicTurret::getFireSpeed() {
	return .6;
}