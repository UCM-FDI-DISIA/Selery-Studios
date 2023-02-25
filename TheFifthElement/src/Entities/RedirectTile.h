#pragma once

#include "../../ColliderComponent.h"
#include "../../ColDetectorComponent.h"
class RedirectTile :
    public Entity
{
private:
    Vector2D pos_;
    float h_ = 20, w_ = 20;
    Vector2D changeDir_;
    ColliderComponent* col_;
    Npc* npc_;
    MovementComponent* npcM_;

public:
    RedirectTile(Vector2D dir, Vector2D pos, Npc* npc) {
        npc_ = npc;
        changeDir_ = dir;
        pos_ = pos;
        addComponent<Transform>(int(TRANSFORM_H), pos_, w_, h_, 0, 0, 0, false);

        //Vector2D pos, float w, float h, float r, float v, int frames, bool matrix
        col_ = addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), pos_, h_, w_);
        addComponent<ColDetectorComponent>(int(COLDETECTORCOMPONENT_H), this, npc_);

    }

    void collision() {
        npcM_ = npc_->getComponent<MovementComponent>(int(MOVEMENTCOMPONENT_H));
        npcM_->setDir(changeDir_);
    }
};