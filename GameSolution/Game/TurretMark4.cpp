#include "TurretMark4.h"
#include "Bullet.h"
#include <cmath>
float TurretMark4::timeBetweenShots = 1/50;

const Matrix3D Cartesian2Screen = Matrix3D::scaleY(-1);
const float turretScale = 2.5;
Shape TurretMark4Style( Turret::defaultTurretColor, 
		Cartesian2Screen * Matrix3D::scale(turretScale), 
		13,
		Vector2D(-1,-2),	Vector2D( 1,-2),	Vector2D( 6, 5),	Vector2D( 6,11),
		Vector2D( 3,13),	Vector2D( 1,12),	Vector2D( 3, 9),	Vector2D( 0, 3),
		Vector2D(-3, 9),	Vector2D(-1,12),	Vector2D(-3,13),	Vector2D(-6,11),
		Vector2D(-6, 5)
);


Shape *TurretMark4::getStyle() {
	return &TurretMark4Style;
}

void TurretMark4::update(float dt) {
	sinceLastShot+=dt;
	pointToMouse();
	MOUSE.update(dt);
	if(Core::Input::IsPressed( MOUSE.getCheckedElement() )) {
		if(sinceLastShot > timeBetweenShots) { 
			sinceLastShot = 0;
			Bullet createdBullet;
			createdBullet.pos   = getParentPos() + tipOfTurret();
			createdBullet.setVel(defaultBulletSpeed*direction);
			createdBullet.style = &defaultBulletStyle;
			shoot(&createdBullet);
		}
	}
}