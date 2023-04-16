#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "FramedImage.h"
#include "ColliderComponent.h"
#include "IceShadowComponent.h"
#include "LifeComponent.h"
#include "../utils/PropertiesManager.h"
#include "MovementComponent.h"

class IceIAComponent :
    public Component
{
private:
    Vector2D dir_;

    Entity* player_;

    FramedImage* im_;
    ColliderComponent* col_;
    IceShadowComponent* sh_;
    LifeComponent* lf_;
    MovementComponent* mv_;

    bool collision_;
    bool die_ = false;
public:
    IceIAComponent(Entity* player) {
        dir_ = Vector2D(0, 1);

        player_ = player;
    }

    void initComponent() {
        im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
        col_ = ent_->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
        mv_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
        sh_ = ent_->getComponent<IceShadowComponent>(ICESHADOWCOMPONENT_H);
        lf_ = player_->getComponent<LifeComponent>(LIFECOMPONENT_H);

        mv_->setDir(dir_);
    }

    void update() {
        if (!die_) {
           
           if (sh_->ShadowCollide() && collision_) {// colisión entre sombras y entidades
                string type = lf_->getType();
                if (type == "air") lf_->Hit(PropertiesManager::instance()->getStrength(0));
                else if (type == "fire") lf_->Hit(PropertiesManager::instance()->getStrength(1));
                else if (type == "water")lf_->Hit(PropertiesManager::instance()->getStrength(2));
                else if (type == "earth")lf_->Hit(PropertiesManager::instance()->getStrength(3));
                ent_->setAlive(false);
           }

           if (sh_->collide(col_->getColRect())) {// colisión con el suelo
               im_->setAnim("iceDestroy", 12, false);
               die_ = true;

               dir_ = Vector2D(0, 0);
               mv_->setDir(dir_);
           }

        }
        else if (!im_->isAnimPlaying()) ent_->setAlive(false);// muerte
    }

    void colPlayer(bool c) { collision_ = c; }
};

