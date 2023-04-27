#pragma once
#include "../utils/Component.h"
#include "ColliderComponent.h"
#include "../utils/Entity.h"
#include "../utils/Collision.h"
#include "ColliderComponent.h"
#include "LifeComponent.h"
#include "AnimationEnemyBEUComponent.h"
#include "IceIAComponent.h"
#include "LifeLightBossComponent.h"

class ColDetectorComponent : public Component

{
private:
    bool collider;
    Entity* obj1_ = nullptr;
    Entity* obj2_ = nullptr;
    Entity* obj3_ = nullptr;
    ColliderComponent* col1_ = nullptr;
    ColliderComponent* col2_ = nullptr;
    ColliderComponent* col3_ = nullptr;
    BeatEmUpState* be;
    SDL_Rect rect_;
    float damage_ = 0.0f;
    float margin_ = 12.0f;
    bool enemy = false;

    LifeComponent* lifeC_ = nullptr;
    AnimationEnemyBEUComponent* anim_ = nullptr;

public:

    ColDetectorComponent(Entity* obj1, Entity* obj2);

    ColDetectorComponent(Entity* obj1, Entity* obj2, Entity* obj3); //este metodo est� para la flecha del lightboss que necesita comprobar a 2 posibles objetivos

    ColDetectorComponent(Entity* obj1, ColliderComponent* c2);

    ColDetectorComponent(Entity* obj1, SDL_Rect r, float damage);

    void initComponent();

    void update();

    bool sideCol();

};

