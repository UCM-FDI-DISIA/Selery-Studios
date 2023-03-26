#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "Image.h"
#include <cstdlib> 
#include "AnimationEnemyBEUComponent.h"
#include "MovementComponent.h"
#include "LifeComponent.h"
#include "AttackBoxComponent.h"
#include "ColDetectorComponent.h"

class BeatEmUpState;

class FireAttackComponent : public Component {
private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;

    float timeToSpawn;
    float delay = 1000;

	BeatEmUpState* state;
    const char* const enemyTypes[4] { "bat" ,"shroom" ,"goblin" ,"skeleton" };

public:
    FireAttackComponent(BeatEmUpState* STATE);
    ~FireAttackComponent();
    void initComponent();
    void update();
    
    void spawnEnemies(int n = 1);
};