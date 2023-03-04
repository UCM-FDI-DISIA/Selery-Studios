#include "BeatEmUpState.h"


BeatEmUpState::BeatEmUpState() {
	addEntity(new Background("airBackground"));
	player_ = addEntity(new PlayerBEU());
	dialog_ = false;
	r = &SDLUtils::instance()->rand();

	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	cmpId_type w = int(INPUTCOMPONENT_H);
	//addEntity(new EnemyBEU(player_, 100, "bat", "fire"));
	/*SDLUtils::instance()->soundEffects().at("Battle").play();*/

	/*n_enemies = r->nextInt(1, 11);
	AddEnemies(n_enemies);*/

	
}
void BeatEmUpState::AddEnemies(int i) {
	for (int i = 0; i < n_enemies; ++i) {
		int character = r->nextInt(0, 4);

		int element = r->nextInt(0, 4);
		Vector2D pos={ (float)r->nextInt(50,WIN_WIDTH - 80),(float)r->nextInt(50,WIN_HEIGHT - 50) };
		if (character == 0) {

			addEntity(new EnemyBEU(pos,player_, 100, "bat", getEnemyType(element)));
		}
		else if (character == 1) {
			addEntity(new EnemyBEU(pos,player_, 100, "skeleton", getEnemyType(element)));
		}
		else if (character == 2) {
			addEntity(new EnemyBEU(pos,player_, 100, "shroom", getEnemyType(element)));
		}
		else {
			addEntity(new EnemyBEU(pos,player_, 100, "goblin", getEnemyType(element)));
		}


	}
}
string BeatEmUpState::getEnemyType(int i) {
	if (i == 0) {

		return "fire";
	}
	else if (i == 1) {
		return "water";
	}
	else if (i == 2) {
		return "earth";
	}
	else {
		return "wind";
	}

}

void BeatEmUpState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		in_->handleEvents(event);
		
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_V)) {
			finishBEU();
		}
}

void BeatEmUpState::finishBEU() {
	GameManager::instance()->goTopDown();
	SDLUtils::instance()->soundEffects().at("Battle").haltChannel();
	cout << "si";
}

string BeatEmUpState::getStateID() {
	return "BeatEmUpState";
}