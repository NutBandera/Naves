#pragma once
#include "Actor.h"
class Recargador :
	public Actor
{
public:
	Recargador(float x, float y, Game* game);
	void update();
};

