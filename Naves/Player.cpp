#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) {
	audioShoot = new Audio("res/efecto_disparo.wav", false);
}

void Player::update() {
	if (shootTime > 0) {
		shootTime--;
	}

	x = x + vx;
	y = y + vy;
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::shoot() {
	if (shootTime == 0 && numberOfShoots > 0) {
		audioShoot->play();
		shootTime = shootCadence;
		numberOfShoots--;
		return new Projectile(x, y, game);
	}
	else {
		return NULL;
	}
	
}

bool Player::isDead() {
	return life == 0;
}

void Player::takeLife() {
	life--;
}

void Player::addShoot() {
	numberOfShoots++;
}

void Player::recargar() {
	numberOfShoots += 10;
}



