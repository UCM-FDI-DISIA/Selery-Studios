#include "BeatEmUpState.h"


BeatEmUpState::BeatEmUpState() {
	addEntity(new Background("airBackground"));
	player_ = addEntity(new PlayerBEU());
	dialog_ = false;
	r = &SDLUtils::instance()->rand();

	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	cmpId_type w = int(INPUTCOMPONENT_H);
	en_ = addEntity(new EnemyBEU(Vector2D(0, 0), player_, 3, "bat", "fire"));
	lb_ = addEntity(new LifeBar(3, "earth", en_));
	en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
	//en_->addComponent<LifeComponent>(LIFECOMPONENT_H, 3, lb_)->subLife(3);
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
			addEntity(new EnemyBEU(pos,player_, 3, "bat", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(3, getEnemyType(element), en_));
			en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
		}
		else if (character == 1) {
			addEntity(new EnemyBEU(pos,player_, 3, "skeleton", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(3, getEnemyType(element), en_));
			en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
		}
		else if (character == 2) {
			addEntity(new EnemyBEU(pos,player_, 3, "shroom", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(3, getEnemyType(element), en_));
			en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
		}
		else {
			addEntity(new EnemyBEU(pos,player_, 3, "goblin", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(3, getEnemyType(element), en_));
			en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
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

/*void BeatEmUpState::update() {
	//Manager::refresh();
}*/