#include "BeatEmUpState.h"


BeatEmUpState::BeatEmUpState() {
	addEntity(new Background("airBackground"));
	player_ = addEntity(new PlayerBEU());
	dialog_ = false;
	r = &SDLUtils::instance()->rand();

	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	cmpId_type w = int(INPUTCOMPONENT_H);
	//en_ = addEntity(new EnemyBEU(Vector2D(0, 0), player_, 3, "bat", "fire"));
	////addEntity(new EnemyBEU(Vector2D(110, 0), player_, 3, "bat", "fire"));
	//lb_ = addEntity(new LifeBar(3, "earth", en_));
	//en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);

	AddEnemies(3);

	atk_ = player_->getComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);

	/*n_enemies = 1;
	AddEnemies(n_enemies);*/
	colMan_ = new ColManager(this);
	//en_->addComponent<LifeComponent>(LIFECOMPONENT_H, 3, lb_)->subLife(3);
	/*SDLUtils::instance()->soundEffects().at("Battle").play();*/

	

	atk_->setContext(player_, this);

	
}
void BeatEmUpState::AddEnemies(int n_enemies) {
	for (int i = 0; i < n_enemies; ++i) {
		int character = r->nextInt(0, 4);

		int element = r->nextInt(0, 4);
		Vector2D pos={ (float)r->nextInt(50,WIN_WIDTH - 80),(float)r->nextInt(50,WIN_HEIGHT - 50) };
		if (character == 0) {
		
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "bat", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(10, getEnemyType(element), en_));
			en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
		}
		else if (character == 1) {
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "skeleton", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(10, getEnemyType(element), en_));
			en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
		}
		else if (character == 2) {
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "shroom", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(10, getEnemyType(element), en_));
			en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
		}
		else {
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "goblin", getEnemyType(element)));
			lb_ = addEntity(new LifeBar(10, getEnemyType(element), en_));
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