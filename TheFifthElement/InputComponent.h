#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "utils/Component.h"
#include "MovementComponent.h"
#include "SkinComponent.h"
#include "SDL_events.h"

class InputComponent : public Component
{
private:
    bool npccol = false;
    MovementComponent* mov_ = nullptr;
    SkinComponent* skin_ = nullptr;
public:
    InputComponent();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);

};
#endif