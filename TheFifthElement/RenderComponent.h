#pragma once
#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_
#include "./utils/Component.h"
#include "SDLutils/Texture.h"
#include "Transform.h"
class RenderComponent : public Component{
protected:
    Texture* t;
    Transform* f;
    int nframes;
    int i = 0;
    int cont = 0;
public:
    RenderComponent(Texture* t_,Transform* x, int n):Component() {
        t = t_;
        f = x;
        nframes = n;
    }
    ~RenderComponent() {};
    void update() {
        if (cont > 5) {
            i++;
            i = i % nframes;
            cont = 0;
        }
        cont++;
    }
    void render() {
        SDL_Rect rect;
        rect.x = f->getPos().getX();
        rect.y = f->getPos().getY();
        rect.h = 120;
        rect.w = 68;
        SDL_Rect src;
        src.x = i*( f->getW()/ nframes);
        src.y = 0;
        src.h = f->getH();
        src.w = f->getW()/nframes;
        t->render(src, rect);
    }

};
#endif
