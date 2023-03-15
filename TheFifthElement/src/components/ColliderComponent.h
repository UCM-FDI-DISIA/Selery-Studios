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
    float scale;

public:

    ColliderComponent(Vector2D offset, float h, float w) {
        scale = WIN_WIDTH / 900;
        offset_ = Vector2D(offset.getX()*scale, offset.getY()*WIN_HEIGHT/600);
        h_ = h*scale;
        w_ = w*scale;
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
        r.x -= mngr_->camRect_.x;
        r.y -= mngr_->camRect_.y;
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
        offset_ = Vector2D(offset.getX() * scale, offset.getY() * WIN_HEIGHT / 600);
    }

    void setCollider(Vector2D offset, float h, float w) {
        offset_ = Vector2D(offset.getX() * scale, offset.getY() * WIN_HEIGHT / 600);
        h_ = h*scale;
        w_ = w*scale;
    }

    int getColHeight() { return h_; }
    int getColWidth() { return w_; }
    Vector2D getOffset() { return offset_; }
};

