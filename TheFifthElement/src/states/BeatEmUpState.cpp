#include "BeatEmUpState.h"
BeatEmUpState::BeatEmUpState() {
	addEntity(new Background("airBackground"));
	player_ = addEntity(new PlayerBEU());
	dialog_ = false;


	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	cmpId_type w = int(INPUTCOMPONENT_H);
	en_ = addEntity(new EnemyBEU(player_, 100, "shroom", "earth"));
	SDLUtils::instance()->soundEffects().at("Battle").play();
	
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