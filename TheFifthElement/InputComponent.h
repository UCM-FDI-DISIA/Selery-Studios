#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"

class InputComponent : public Component
{
public:
    InputComponent();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
private:

    MovementComponent* mov_ = nullptr;
   
};
#endif