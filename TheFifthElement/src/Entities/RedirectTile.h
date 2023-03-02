#pragma once

#include "../components/ColliderComponent.h"
#include "../components/ColDetectorComponent.h"
class RedirectTile :
    public Entity
{
private:
    
    Vector2D pos_;
    float h_ = 20, w_ = 20;
    Vector2D changeDir_;
    ColliderComponent* col_;
    Enemy* enemy_;
    MovementComponent* enemyM_;
public:

    RedirectTile(Vector2D dir, Vector2D pos, Enemy* enemy) {
        enemy_ = enemy;
        changeDir_ = dir;
        pos_ = pos;
        addComponent<Transform>(int(TRANSFORM_H), pos_, w_, h_, 0, 0, 0, false);

        //Vector2D pos, float w, float h, float r, float v, int frames, bool matrix
        col_ = addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(h_, w_), h_, w_);
        addComponent<ColDetectorComponent>(int(COLDETECTORCOMPONENT_H), this, enemy_);

    }

    void collision() {
        enemyM_ = enemy_->getComponent<MovementComponent>(int(MOVEMENTCOMPONENT_H));
        enemyM_->setDir(changeDir_);
    }

};

