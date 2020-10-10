#include "Bomba.h"

Bomba::Bomba(float x, float y, Game* game)
	: Actor("res/asteroide.png", x, y, 50, 51, game) {
	vx = 1;
}

void Bomba::update() {

}
