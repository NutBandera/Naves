#include "Recargador.h"

Recargador::Recargador(float x, float y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 40, game) {
	vx = 1;
}

void Recargador::update() {

}