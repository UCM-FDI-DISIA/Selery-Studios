#pragma once
#ifndef ATTACKBOXCOMPONENT_H_
#define ATTACKBOXCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../GameManager.h"


class AttackBoxComponent : public Component {
private:
    Transform* playerTr = nullptr;
    SDL_Rect box;
    float width, height;
public:
    AttackBoxComponent();
    virtual ~AttackBoxComponent(){}
    void render();
    void update();
    void initComponent();
};
#endif