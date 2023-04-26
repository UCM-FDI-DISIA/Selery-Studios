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
        h_ = h;
        w_ = w;
    }

    void initComponent() {
        tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
        
        offset_ = Vector2D(offset_.getX() *tr_->getS(), offset_.getY() * tr_->getS());
        h_ *= tr_->getS();
        w_ *= tr_->getS();

        pos_ = tr_->getPos();
        pos_ = pos_ + offset_;
        r.x = pos_.getX();
        r.y = pos_.getY();
        r.w = w_;
        r.h = h_;
    }

    SDL_Rect getColRect() { return r; }

    void render() {
       /* r.x -= mngr_->camRect_.x;
        r.y -= mngr_->camRect_.y;
        SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
        SDL_RenderDrawRect(sdlutils().renderer(), &r);*/
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
        offset_ = Vector2D(offset.getX() * tr_->getS(), offset.getY() * tr_->getS());
    }

    void setCollider(Vector2D offset, float h, float w) {
        offset_ = Vector2D(offset.getX() * tr_->getS(), offset.getY() * tr_->getS());
        h_ = h * tr_->getS();
        w_ = w * tr_->getS();
    }

    int getColHeight() { return h_; }
    int getColWidth() { return w_; }
    Vector2D getOffset() { return offset_; }
    inline void setCollisionWithPlayer(bool col) { collidedWithPlayer = col; }
    inline bool getCollisionWithPlayer() { return collidedWithPlayer; }
};

