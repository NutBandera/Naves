#include "GameLayer.h"

GameLayer::GameLayer(Game *game)
	: Layer(game) {
	init();
}

void GameLayer::init() {
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);
	textLife = new Text("3", WIDTH * 0.79, HEIGHT * 0.04, game);
	player = new Player(50, 50, game);
	background = new Background("res/fondo.png", WIDTH*0.5, HEIGHT*0.5, -1, game);
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	backgroundLife = new Actor("res/corazon.png", WIDTH * 0.71, HEIGHT * 0.05, 44, 36, game);

	projectiles.clear();

	enemies.clear(); // Vaciar por si reiniciamos el juego
	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new Enemy(300, 200, game));

	recargadores.clear();
	monedas.clear();
	bombas.clear();

}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	//Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}

	}
	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_d: {// derecha
			controlMoveX = 1;
			break;
		}
		case SDLK_a: {// izquierda
			controlMoveX = -1;
			break;
		}
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}

}


void GameLayer::update() {
	background->update();
	// Generar enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY, game));
		newEnemyTime = 110;
	}

	// Generar recargadores
	newRecargadorTime--;
	if (newRecargadorTime <= 0) {
		int rX = (rand() % (400)) + 1 + 50;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		recargadores.push_back(new Recargador(rX, rY, game));
		newRecargadorTime  = 500;
	}

	// Generar monedas
	newMonedaTime--;
	if (newMonedaTime <= 0) {
		int rX = (rand() % (400)) + 1 + 50;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		monedas.push_back(new Moneda(rX, rY, game));
		newMonedaTime = 500;
	}

	// Generar bombas
	newBombaTime--;
	if (newBombaTime <= 0) {
		int rX = (rand() % (400)) + 1 + 50;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		bombas.push_back(new Bomba(rX, rY, game));
		newBombaTime = 1000;
	}

	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
	}


	list<Moneda*> deleteMonedas;
	for (auto const& moneda : monedas) {
		if (player->isOverlap(moneda)) {
			player->addLife();
			textLife->content = to_string(player->life);
			bool mInList = std::find(deleteMonedas.begin(),
				deleteMonedas.end(),
				moneda) != deleteMonedas.end();
			if (!mInList) {
				deleteMonedas.push_back(moneda);
			}
		}
	}

	for (auto const& delMoneda : deleteMonedas) {
		monedas.remove(delMoneda);
	}
	deleteMonedas.clear();

	list<Enemy*> deleteEnemies; // lista enlazada
	list<Bomba*> deleteBombas;
	for (auto const& bomba : bombas) {
		if (player->isOverlap(bomba)) {
			bool mInList = std::find(deleteBombas.begin(),
				deleteBombas.end(),
				bomba) != deleteBombas.end();
			if (!mInList) {
				deleteBombas.push_back(bomba);
			}
			for (auto const& enemy : enemies) {
				points++;
				textPoints->content = to_string(points);
				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();
				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}
			}
		}
	}

	for (auto const& delBomba : deleteBombas) {
		bombas.remove(delBomba);
	}
	deleteMonedas.clear();


	list<Projectile*> deleteProjectiles;

	// Colisiones , Enemy - Player
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			player->takeLife();
			textLife->content = to_string(player->life);
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();
			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
			if (player->isDead()) {
				init();
				return;
			}
			
		}
	}

	list<Recargador*> deleteRecargadores;
	for (auto const& recargador : recargadores) {
		if (player->isOverlap(recargador)) {
			player->recargar();
			bool mInList = std::find(deleteRecargadores.begin(),
				deleteRecargadores.end(),
				recargador) != deleteRecargadores.end();
			if (!mInList) {
				deleteRecargadores.push_back(recargador);
			}
		}
	}

	for (auto const& delRecargador: deleteRecargadores) {
		recargadores.remove(delRecargador);
	}
	deleteRecargadores.clear();

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				enemy->takeLife();
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				if (enemy->isDead()) {
					bool eInList = std::find(deleteEnemies.begin(),
						deleteEnemies.end(),
						enemy) != deleteEnemies.end();

					if (!eInList) {
						deleteEnemies.push_back(enemy);
					}

					points++;
					textPoints->content = to_string(points);
					player->addShoot();
				}

				
			}
			if (projectile->isInRender() == false) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
			}
				
		}
	}

	// ...

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();



	for (const auto& projectile: projectiles) {
		projectile->update();
	}
}

void GameLayer::draw() {
	background->draw();

	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	player->draw();

	for (auto const& recargador : recargadores) {
		recargador->draw();
	}

	for (auto const& moneda : monedas) {
		moneda->draw();
	}

	for (auto const& bomba : bombas) {
		bomba->draw();
	}

	for (auto const& enemy : enemies) {
		enemy->draw();
	}


	backgroundPoints->draw();
	backgroundLife->draw();
	textPoints->draw();
	textLife->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

