#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../utils/Entity.h"

class ColliderComponent: public Component
{
private:

    Vector2D pos_;
    float h_, w_;
    SDL_Rect r;
    Transform* tr_;
    Vector2D offset_;
    bool collidedWithPlayer = false;

public:

    ColliderComponent(Vector2D offset, float h, float w) {
        offset_ = offset;
        h_ = h * WIN_HEIGHT/600;
        w_ = w * WIN_WIDTH/900;
    }

    void initComponent() {
        tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
        
        offset_ = Vector2D(offset_.getX(), offset_.getY());
        h_ *= tr_->getSize();
        w_ *= tr_->getSize();

        pos_ = tr_->getPos();
        pos_ = pos_ + offset_;
        r.x = pos_.getX();
        r.y = pos_.getY();
        r.w = w_;
        r.h = h_;
    }

    SDL_Rect getColRect() { return r; }

    void render() {
       
            r.x -= mngr_->camRect_.x;
            r.y -= mngr_->camRect_.y;
     if (DEBUG) {
            SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
            SDL_RenderDrawRect(sdlutils().renderer(), &r);
        }
    }

    void update() {
        pos_ = tr_->getPos();
        pos_ = pos_ + offset_;
        r.x = pos_.getX();
        r.y = pos_.getY();
        r.w = w_;
        r.h = h_;
    }

    void setOffset(Vector2D offset) {
        offset_ = Vector2D(offset.getX() * tr_->getSW(), offset.getY() * tr_->getSH());
    }

    void setCollider(Vector2D offset, float h, float w) {
        offset_ = Vector2D(offset.getX() * tr_->getSW(), offset.getY() * tr_->getSH());
        h_ = h * tr_->getSH();
        w_ = w * tr_->getSW();
    }

    int getColHeight() { return h_; }
    int getColWidth() { return w_; }
    Vector2D getOffset() { return offset_; }
    inline void setCollisionWithPlayer(bool col) { collidedWithPlayer = col; }
    inline bool getCollisionWithPlayer() { return collidedWithPlayer; }
};

