#pragma once
#include "../utils/Component.h"
//#include "./src/components/ColliderComponent.h"
#include "ColliderComponent.h"
#include "../utils/Entity.h"
#include "../utils/Collision.h"
#include "../components/ColliderComponent.h"
#include "../components/LifeComponent.h"

class ColDetectorComponent: public Component
    
{
private:
    bool collider;
    Entity* obj1_ = nullptr;
    Entity* obj2_ = nullptr;
    ColliderComponent* col1_ = nullptr;
    ColliderComponent* col2_ = nullptr;
    SDL_Rect rect_; 
    float damage_ = 0.0f;
    float margin = 12.0f;
    bool enemy = false;

    LifeComponent* lifeC_ = nullptr;

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
        if (obj1_->hasComponent(LIFECOMPONENT_H))lifeC_ = obj1_->getComponent<LifeComponent>(LIFECOMPONENT_H);
        else lifeC_ = nullptr;
    }

    void update() {
        if (lifeC_ != nullptr) {
            if (collider) {
                if (Collision::collides(Vector2D(col1_->getColRect().x,
                    col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
                    Vector2D(col2_->getColRect().x, col2_->getColRect().y),
                    col2_->getColRect().w, col2_->getColRect().h) && sideCol())
                    lifeC_->setCollision(true);
            }
            else if (Collision::collides(Vector2D(col1_->getColRect().x,
                col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
                Vector2D(rect_.x, rect_.y), rect_.w, rect_.h))
            {
                lifeC_->Hit(damage_);
                //obj1_->Hit(damage_);

            }
        }
        else if(collider)
            obj1_->collision(Collision::collides(Vector2D(col1_->getColRect().x,
                col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
                Vector2D(col2_->getColRect().x, col2_->getColRect().y),
                col2_->getColRect().w, col2_->getColRect().h));
       
    }

    bool sideCol() {

        Transform* tr_ = obj1_->getComponent<Transform>(TRANSFORM_H);
        Transform* playerTr_ = obj2_->getComponent<Transform>(TRANSFORM_H);

        Vector2D offset_ = col2_->getOffset();// player offset
        float ch_ = col2_->getColHeight();// player collider height

        float playerFloor = playerTr_->getPos().getY() + offset_.getY() + ch_;// player pos Y (floor)

        offset_ = col1_->getOffset();// enemy offset
        ch_ = col1_->getColHeight();// enemy collider height

        float posY = tr_->getPos().getY();// enemy pos Y
        float targetY = playerFloor - offset_.getY() - ch_;// target point Y

        return ((targetY - margin <= posY) && (targetY + margin >= posY));
    }

};

