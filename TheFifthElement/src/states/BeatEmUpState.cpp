#include "BeatEmUpState.h"
BeatEmUpState::BeatEmUpState() {
	mngr_->addEntity(new Background());
	player_ = mngr_->addEntity(new PlayerBEU());
	dialog_ = false;


	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	mngr_->addEntity(new EnemyBEU(player_, 100));
}

<<<<<<< Updated upstream
=======
void BeatEmUpState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		in_->handleEvents(event);
		
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_V)) {
			finishBEU();
	}
}
>>>>>>> Stashed changes

void BeatEmUpState::finishBEU() {
	GameManager::instance()->goTopDown();
	cout << "si";
}

string BeatEmUpState::getStateID() {
	return "BeatEmUpState";
}

void BeatEmUpState::update() {
	GameState::update();
}

void BeatEmUpState::render() {
	GameState::render();
}