#pragma once
#include "./utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"

class InputComponentBEU : public Component
{
public:
    InputComponentBEU();
    void initComponent();
    void initComponentBEU();
    void update();
    void handleEvents(SDL_Event event);
private:

    MovementComponent* mov_ = nullptr;
};

