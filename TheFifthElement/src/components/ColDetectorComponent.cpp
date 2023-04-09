#include "ColDetectorComponent.h"
ColDetectorComponent::ColDetectorComponent(Entity* obj1, Entity* obj2) {
    //obj1 desde el que llamas
    obj1_ = obj1;
    obj2_ = obj2;
    collider = true;
}

ColDetectorComponent::ColDetectorComponent(Entity* obj1, ColliderComponent* c2) {
    //obj1 desde el que llamas
    obj1_ = obj1;
    col2_ = c2;
    collider = true;
}

ColDetectorComponent::ColDetectorComponent(Entity* obj1, SDL_Rect r, float damage) {
    //obj1 desde el que llamas
    obj1_ = obj1;
    rect_ = r;
    damage_ = damage;
    collider = false;
}

void ColDetectorComponent::initComponent() {
    col1_ = obj1_->getComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H));
    if (obj2_ != nullptr)col2_ = obj2_->getComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H));
    if (obj1_->hasComponent(LIFECOMPONENT_H))lifeC_ = obj1_->getComponent<LifeComponent>(LIFECOMPONENT_H);
    else lifeC_ = nullptr;
    if (obj1_->hasComponent(ANIMATIONENEMYBEUCOMPONENT_H))anim_ = ent_->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H);
    else anim_ = nullptr;
}

void ColDetectorComponent::update() {
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
            Vector2D(rect_.x, rect_.y), rect_.w, rect_.h)) lifeC_->Hit(damage_);
    }
    else { //OLA A PLAYER
        if (obj1_->hasComponent(DISABLEONEXIT_H)&&!obj1_->hasComponent(LIGHTBOSSELEMENT_H)) {// deberia cambiarse ya que los proyectiles del boss de luz cuentan con esto tambien
            if (Collision::collides(Vector2D(col1_->getColRect().x,
                col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
                Vector2D(col2_->getColRect().x, col2_->getColRect().y),
                col2_->getColRect().w, col2_->getColRect().h))
                obj2_->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(1.2);
        }

        else if (obj1_->hasComponent(LIGHTBOSSELEMENT_H))
        {
            if (Collision::collides(Vector2D(col1_->getColRect().x,
                col1_->getColRect().y), col1_->getColRect().w, col1_->getColRect().h,
                Vector2D(col2_->getColRect().x, col2_->getColRect().y),
                col2_->getColRect().w, col2_->getColRect().h))
            {
                obj2_->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(1.2);
                if (obj1_->hasComponent(DISABLEONEXIT_H)) { obj1_->setAlive(false); }
            }
        }
    }
}

bool ColDetectorComponent::sideCol() {
    Transform* tr_ = obj1_->getComponent<Transform>(TRANSFORM_H);
    Transform* playerTr_ = obj2_->getComponent<Transform>(TRANSFORM_H);

    Vector2D Poffset_ = col2_->getOffset();// player offset
    float Pch_ = col2_->getColHeight();// player collider height

    Vector2D offset_ = col1_->getOffset();// enemy offset
    float ch_ = col1_->getColHeight();// enemy collider height
    float targetY, posY;

    if (anim_->getEnemy() != "bat") {
        float playerFloor = playerTr_->getPos().getY() + Poffset_.getY() + Pch_;// player pos Y (floor)
        targetY = playerFloor - offset_.getY() - ch_;// target point Y
        posY = tr_->getPos().getY();// enemy pos Y

        margin_ = 12.0f * WIN_WIDTH / 900;
    }
    else {
        posY = tr_->getPos().getY() + offset_.getY();// enemy pos Y
        margin_ = 5.0f * WIN_WIDTH / 900;
        targetY = playerTr_->getPos().getY() + Poffset_.getY() - margin_;// target point Y
        margin_ = 10.0f * WIN_WIDTH / 900;
    }

    return ((targetY - margin_ <= posY) && (targetY + margin_ >= posY));
}