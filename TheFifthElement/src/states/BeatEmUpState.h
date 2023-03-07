#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "../ColManager.h"
#include "../components/AttackBoxComponent.h"
#include "../components/AnimationEnemyBEUComponent.h"
#include "../components/Transform.h"
#include "../components/InputComponent.h"
#include "../components/LifeComponent.h"
#include "../components/MovementComponent.h"
#include "../components/EnemyBEUDirectionComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/ColDetectorComponent.h"

using name = string;
using damage = int;
class BeatEmUpState: public Manager {
private:
	//PLAYER
	Entity* player_;
	Transform* trans_player_;
	InputComponentBEU* in_;
	//BACKGROUND
	Entity* background_;
	RandomNumberGenerator* random;
	//ENEMIGOS
	Entity* enemy_;
	AnimationEnemyBEUComponent* animation_;
	//COLISIONES
	//ColManager* colManager_;
	
	LifeBar* lifebar_;
	float camOffset_ = 300.0f;
	float enemy_width=0, enemy_height=0;
	

public:
	BeatEmUpState();
	~BeatEmUpState() {}
	string getStateID(); // stringID
	void AddEnemies(int i);
	string getEnemyType(int i);
	void finishBEU();
	void handleEvents();
	//ColManager* getColManager() { return colManager_; }
	void update();
};

