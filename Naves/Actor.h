#pragma once
#include "Game.h"

class Actor {
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw();
	bool isOverlap(Actor* actor);
	bool isInRender();
	SDL_Texture* texture;
	float x;
	float y;
	float vx; // velocidad eje x
	float vy; // velocidad eje y
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game;
};
