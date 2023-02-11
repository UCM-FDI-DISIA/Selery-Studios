#pragma once
#include "./utils/Component.h"
#include "SDLutils/Texture.h"
#include "Transform.h"

#include "utils/ecs.h"
class RenderComponent :
    public Component
{
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
       
    }

};

