#include "BeatEmUpState.h"
BeatEmUpState::BeatEmUpState() {
	addEntity(new Background());
	player_ = addEntity(new PlayerBEU());
	dialog_ = false;


	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	addEntity(new EnemyBEU(player_, 100));
}


void BeatEmUpState::finishBEU() {
	GameManager::instance()->goTopDown();
	cout << "si";
}

string BeatEmUpState::getStateID() {
	return "BeatEmUpState";
}