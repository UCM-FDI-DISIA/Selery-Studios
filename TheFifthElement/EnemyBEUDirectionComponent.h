#pragma once
#include "./utils/Component.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "./utils/Vector2D.h"
#include "PlayerBEU.h"

class EnemyBEUDirectionComponent :
    public Component
{
public:
    EnemyBEUDirectionComponent(PlayerBEU* p);
    void initComponent();
    void update();
    void changeDir(Vector2D d);
private:

    MovementComponent* mov_;
    Transform* tr_;
    Vector2D dir_;
    PlayerBEU* player_;
    Transform* playerTr_;
    int cont = 1000;
    bool izq = true;
    float distance_ = 100.0f;
};

