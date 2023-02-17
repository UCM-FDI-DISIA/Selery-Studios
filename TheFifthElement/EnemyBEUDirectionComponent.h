#pragma once
#include "./utils/Component.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "./utils/Vector2D.h"

class EnemyBEUDirectionComponent :
    public Component
{
public:
    EnemyBEUDirectionComponent();
    void initComponent();
    void update();
    void changeDir(Vector2D d);
private:

    MovementComponent* mov_;
    Transform* tr_;
    Vector2D dir_;
    int cont = 1000;
    bool izq = true;
};

