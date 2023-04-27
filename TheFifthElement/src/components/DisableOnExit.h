#pragma once
#include "../utils/Component.h"
#include "Transform.h"
class DisableOnExit : public Component
{
private:
    Transform* tr_ = nullptr;
    int w = 0;

public:
    DisableOnExit() {}

    void initComponent() {
        tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
        w = tr_->getW() * tr_->getS();
    }

    void update() { // Si un objeto con este componente sale de los limites de la ventana se destruye
        int x = tr_->getPos().getX();
        
        if (x < 0 - w) {
            ent_->setAlive(false);
        }
    }
};

