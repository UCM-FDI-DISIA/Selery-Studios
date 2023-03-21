#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "../utils/Manager.h"
#include "ColliderComponent.h"
#include "../utils/Collision.h"
#include "MovementComponent.h"
#include "Enemy_movementTD_component.h"
#include <vector>
class RedirectEnemy : public Component
{
private:
    Vector2D redVector;
    SDL_Rect redBox_;
    vector <Entity*> enemies_;
public:
    RedirectEnemy(Vector2D redirectVector, SDL_Rect redBox, vector<Entity*> v) {
        redVector = redirectVector;
        redBox_ = redBox;
        enemies_ = v;
    }

    void update() {
        for (auto it : enemies_) {
            if (it->hasComponent(CHECKCOLLISION_H)) {
                ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
                if (Collision::collides(Vector2D(redBox_.x, redBox_.y), redBox_.w, redBox_.h,
                    Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h)) {
                    MovementComponent* mv_ = it->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
                    Enemy_movementTD_component* eMv_ = it->getComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H);
                    eMv_->changeState(redVector);
                    mv_->setDir(redVector);
                }
            }
        }
    }

};









