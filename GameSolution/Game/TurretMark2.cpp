#include "TurretMark2.h"
#include "Bullet.h"
#include <cmath>
float TurretMark2::timeBetweenShots = .125;

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


Shape *TurretMark2::getStyle() {
	return &TurretMark2Style;
}

void TurretMark2::update(float dt, const Vector2D& pos) {
	sinceLastShot+=dt;
	pointToMouse(pos);
	MOUSE.update(dt);
	if(Core::Input::IsPressed( MOUSE.getCheckedElement() )) {
		if(sinceLastShot > timeBetweenShots) { 
			sinceLastShot = 0;
			Bullet toShoot;
			toShoot.pos   = pos + tipOfTurret();
			toShoot.vel   = -100*direction;
			toShoot.style = &defaultBulletStyle;
			toShoot.rotation = 20;
			shoot(&toShoot);
		}
	}
}