#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../utils/Entity.h"

class ColliderComponent :
    public Component
{
private:

    Vector2D pos_;
    float h_, w_;
    SDL_Rect r;
    Transform* tr_;
    Vector2D offset_;

public:

    ColliderComponent(Vector2D offset, float h, float w) {
        offset_ = offset;
        h_ = h;
        w_ = w;
    }

    void initComponent() {
        tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
        pos_ = tr_->getPos();
        pos_ = pos_ + offset_;
        r.x = pos_.getX();
        r.y = pos_.getY();
        r.w = w_;
        r.h = h_;
    }

    SDL_Rect getColRect() { return r; }

    void render() {
        r.x -= ent_->mngr_->camRect_.x;
        r.y -= ent_->mngr_->camRect_.y;
        SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
        SDL_RenderDrawRect(sdlutils().renderer(), &r);
        //SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
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
        offset_ = offset;
    }

    void setCollider(Vector2D offset, float h, float w) {
        offset_ = offset;
        h_ = h;
        w_ = w;
    }
};

