#pragma once
#ifndef ATTACKBOXCOMPONENT_H_
#define ATTACKBOXCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../GameManager.h"


class Image;
class AttackBoxComponent : public Component {
private:
    Transform* playerTr = nullptr;
    SDL_Rect box;
    Image* im_;
    float width, height, boxTime, timerExecution;
    float angle = 0;
    bool boxCreated = false;
public:
    AttackBoxComponent();
    virtual ~AttackBoxComponent(){}
    void render();
    void update();
    void initComponent();

    void handleBoxes();
    void moveBox(Vector2D direction,float vel);
    void moveBoxCurve(Vector2D direction,Vector2D posCenter, float vel,float& angle);
    void GFY();



};
#endif