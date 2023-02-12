#pragma once
#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_
#include "./utils/Component.h"
#include "SDLutils/Texture.h"
#include "Transform.h"
<<<<<<< Updated upstream
class RenderComponent :  public Component{
protected:
Texture* t;
Transform* f;
public:
    RenderComponent(Texture* t_,Transform* x):Component() {
        t = t_;
        f = x;
     //   f = ent_->getComponent<Transform>(int(TRANSFORM_H_));
    };
    ~RenderComponent() {};
    void update() {
      
=======
class RenderComponent : public Component {
protected:
    Texture* t;
    Transform* f;
public:
    RenderComponent(Texture* t_, Transform* x) :Component() {
        t = t_;
        f = x;
        //   f = ent_->getComponent<Transform>(int(TRANSFORM_H_));
    };
    ~RenderComponent() {};
    void update() {

>>>>>>> Stashed changes
    }
    void render() {
        SDL_Rect rect;
        rect.x = f->getPos().getX();
        rect.y = f->getPos().getY();
        rect.h = f->getH();
        rect.w = f->getW();
        SDL_Rect src;
        rect.x = 0;
<<<<<<< Updated upstream
        rect.y =0;
=======
        rect.y = 0;
>>>>>>> Stashed changes
        rect.h = f->getH();
        rect.w = f->getW();
        t->render(rect);
    }

};
#endif
