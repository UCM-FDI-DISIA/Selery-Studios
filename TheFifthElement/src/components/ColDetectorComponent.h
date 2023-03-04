#pragma once
#include "../utils/Component.h"
//#include "./src/components/ColliderComponent.h"
#include "ColliderComponent.h"
#include "../utils/Entity.h"
#include "../utils/Collision.h"
#include "../components/ColliderComponent.h"

class ColDetectorComponent :
    public Component
{
private:
    bool collider;
    Entity* obj1_ = nullptr;
    Entity* obj2_ = nullptr;
    ColliderComponent* col1_ = nullptr;
    ColliderComponent* col2_ = nullptr;
    SDL_Rect rect_; 
    float damage_;

public:

    ColDetectorComponent(Entity* obj1, Entity* obj2) {
        //obj1 desde el que llamas
        obj1_ = obj1;
        obj2_ = obj2;
        collider = true;
    }

    ColDetectorComponent(Entity* obj1, ColliderComponent* c2) {
        //obj1 desde el que llamas
        obj1_ = obj1;
        col2_ = c2;
        collider = true;
    }

    ColDetectorComponent(Entity* obj1, SDL_Rect r, float damage) {
        //obj1 desde el que llamas
        obj1_ = obj1;
        rect_ = r;
        damage_ = damage;
        collider = false;
    }

    void initComponent() {
        col1_ = obj1_->getComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H));
        if(obj2_ != nullptr)col2_ = obj2_->getComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H));
    }

    void update() {
        if (collider) {
            obj1_->collision(Collision::collides(Vector2D(col1_->getColRect().x,
                col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
                Vector2D(col2_->getColRect().x, col2_->getColRect().y),
                col2_->getColRect().w, col2_->getColRect().h));
        }
        else if(Collision::collides(Vector2D(col1_->getColRect().x,
            col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
            Vector2D(rect_.x, rect_.y), rect_.w, rect_.h))
        {
             obj1_->Hit(damage_);
           
        }
       
    }

};

