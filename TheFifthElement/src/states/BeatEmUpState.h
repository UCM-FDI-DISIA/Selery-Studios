#pragma once
#include "GameState.h"
#include "../Entities/Npc.h"
#include "../Entities/PlayerBEU.h"
#include "../Entities/Enemy.h"
#include "../components/InputComponent.h"
#include "../Entities/DialogBox.h"
#include "../Entities/EnemyBEU.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/Background.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/LifeBar.h"
#include <unordered_map>
using name = string;
using damage = int;
class BeatEmUpState	 : public Manager {
private:
	PlayerBEU* player_;
	InputComponentBEU* in_;
	bool dialog_;
	RandomNumberGenerator* r;
	int n_enemies = 0;

	EnemyBEU* en_;
	LifeBar* lb_;

public:
	string getStateID(); // stringID
	BeatEmUpState();
	void AddEnemies(int i);
	string getEnemyType(int i);
	void finishBEU();
	void handleEvents();
	//void update();
	~BeatEmUpState() {}
};

