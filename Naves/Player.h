#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Audio.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	int shootCadence = 20;
	int shootTime = 0;
	void takeLife();
	bool isDead();
	int life = 3;
	int numberOfShoots = 10;
	void addShoot();
	void recargar();
	Projectile* shoot();
	Audio* audioShoot;
};

