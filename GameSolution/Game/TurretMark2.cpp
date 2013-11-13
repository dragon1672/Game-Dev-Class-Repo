#include "TurretMark2.h"
#include "Bullet.h"
#include <cmath>
float TurretMark2::timeBetweenShots = .5;

const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark2Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		16,
		Vector2D(-3,-2),	Vector2D( 3,-2),	Vector2D( 3, 2),	Vector2D( 1, 2),
		Vector2D( 1, 9),	Vector2D( 3,10),	Vector2D( 3,13),	Vector2D( 1,13),
		Vector2D( 1,11),	Vector2D(-1,11),	Vector2D(-1,13),	Vector2D(-3,13),
		Vector2D(-3,10),	Vector2D(-1, 9),	Vector2D(-1, 2),	Vector2D(-3, 2)
);
const float bulletScale = 4;
Shape defaultBulletStyle(RGB(255,0,255),
	Cartesian2Screen * Matrix3D::scale(bulletScale), 
	5,
	Vector2D(   .7f, -1.0f ),
	Vector2D(  0.0f,  1.0f ),
	Vector2D(  -.6f, -1.0f ),
	Vector2D(  1.0f,   .25f),
	Vector2D( -1.0f,   .25f) 
);

Shape *TurretMark2::getStyle() {
	return &TurretMark2Style;
}

void TurretMark2::update(float dt, const Vector2D& pos) {
	pointToMouse(pos);
	MOUSE.update(dt);
	if(Core::Input::IsPressed( MOUSE.getCheckedElement() )) {
		if(MOUSE.hasBeenClicked()) { 
			Bullet toShoot;
			toShoot.pos   = pos;
			toShoot.vel   = -100*direction.normalized();
			toShoot.style = &defaultBulletStyle;
			shoot(&toShoot);
		}
	}
}