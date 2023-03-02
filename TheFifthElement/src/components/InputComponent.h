#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "Image.h"
#include "SkinComponent.h"
#include "SDL_events.h"

class InputComponent : public Component {
private:
    bool npccol = false;
    double actionDelay;
    MovementComponent* mov_ = nullptr;
    SkinComponent* skin_ = nullptr;
    Image* im_ = nullptr;

public:
    InputComponent();
    void initComponent();
    void handleEvents(SDL_Event event);
    void update();
    void changebool(){ npccol = false; }
};
#endif