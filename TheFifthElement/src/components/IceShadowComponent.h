#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "ShadowComponent.h"
#include "../utils/Collision.h"
class IceShadowComponent :
    public Component
{
private:
    Entity* player_;

    ShadowComponent* sh_;
    int size_ = 48;// el src de la imagen del shadow de Ice es de 48x48
    Vector2D pos_;
    float s_;

    Texture* t = &SDLUtils::instance()->images().at("iceShadow");
    SDL_Rect dest, src;

public:
    IceShadowComponent(Vector2D position, float size, Entity* player) {
        
        pos_ = position;
        s_ = size;
        player_ = player;

        /*dest.x = position.getX();
        dest.y = position.getY();
        dest.w = size_ * ((WIN_WIDTH/900)*size);
        dest.h = size_ * ((WIN_HEIGHT / 600) * size);*/


    }

    void initComponent() {

        dest.x = pos_.getX();
        dest.y = pos_.getY();
        dest.w = size_ * ((WIN_WIDTH / 900) * s_);
        dest.h = size_ * ((WIN_HEIGHT / 600) * s_);

        src.x = 0;
        src.y = 0;
        src.w = size_;
        src.h = size_;

        sh_ = player_->getComponent<ShadowComponent>(SHADOWCOMPONENT_H);
    }

    void render() {
        t->render(src, dest, 0, nullptr);
    }

    bool collide(SDL_Rect r1) {
        //SDL_Rect r2 = dest;
        return (Collision::collides(Vector2D(r1.x,r1.y), r1.w, r1.h, Vector2D(dest.x, dest.y), dest.w, dest.h));
    }

    bool ShadowCollide() {
        SDL_Rect r1 = sh_->getRect();
        SDL_Rect r2 = dest;
        return (Collision::collides(Vector2D(r1.x, r1.y), r1.w, r1.h, Vector2D(r2.x, r2.y), r2.w, r2.h));
    }
};

