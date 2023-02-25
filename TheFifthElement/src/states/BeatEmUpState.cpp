#include "BeatEmUpState.h"
BeatEmUpState::BeatEmUpState() {
	mngr_->addEntity(new Background());
	player_ = mngr_->addEntity(new PlayerBEU());
	dialog_ = false;


	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	mngr_->addEntity(new EnemyBEU(player_, 100));
}


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