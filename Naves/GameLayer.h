#pragma once
#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Audio.h"
#include "Recargador.h"
#include "Moneda.h"
#include "Bomba.h"
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	int newEnemyTime = 0;
	int newRecargadorTime = 0;
	int newMonedaTime = 0;
	int newBombaTime = 0;

	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor * backgroundLife;
	Audio* audioBackground;

	Text* textPoints;
	Text* textLife;
	int points;


	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<Recargador*> recargadores;
	list<Moneda*> monedas;
	list<Bomba*> bombas;
};