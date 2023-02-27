#pragma once
#include "../utils/Component.h"
//#include "./src/components/ColliderComponent.h"
#include "ColliderComponent.h"
#include "../utils/Entity.h"
#include "../utils/Collision.h"

class ColDetectorComponent :
    public Component
{
private:
    
    Entity* obj1_;
    Entity* obj2_;
    ColliderComponent* col1_;
    ColliderComponent* col2_;

public:

    ColDetectorComponent(Entity* obj1, Entity* obj2) {
        //obj1 desde el que llamas
        obj1_ = obj1;
        obj2_ = obj2;
    }

    void initComponent() {
        col1_ = obj1_->getComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H));
        col2_ = obj2_->getComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H));
    }

    void update() {
        if (Collision::collides(Vector2D(col1_->getColRect().x, col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
            Vector2D(col2_->getColRect().x, col2_->getColRect().y), col2_->getColRect().w, col2_->getColRect().h)) {
            obj1_->collision();
        }
        else obj1_->noCollision();
    }

};

