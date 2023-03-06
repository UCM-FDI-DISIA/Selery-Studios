#pragma once
#include "GameState.h"
#include "../Entities/Enemy.h"
#include "../components/InputComponent.h"
#include "../Entities/EnemyBEU.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/Background.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/LifeBar.h"
#include <unordered_map>
#include "../ColManager.h"
#include "../components/AttackBoxComponent.h"
using name = string;
using damage = int;
class BeatEmUpState: public Manager {
private:
	//PLAYER
	Entity* player_;
	Transform* trplayer_;

	InputComponentBEU* in_;
	bool dialog_;
	RandomNumberGenerator* r;
	//int n_enemies = 0;
	ColManager* colMan_;
	EnemyBEU* en_;
	LifeBar* lb_;
	float camOffset_ = 300.0f;
	AttackBoxComponent* atk_;

public:
	string getStateID(); // stringID
	BeatEmUpState();
	void AddEnemies(int i);
	string getEnemyType(int i);
	void finishBEU();
	void handleEvents();
	//void update();
	~BeatEmUpState() {}

	ColManager* getColManager() { return colMan_; }
	void update();
};

